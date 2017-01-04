/*
 * Created by The Pious Authors on 12/08/2016.
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PIOUS_VECTOR_H
#define PIOUS_VECTOR_H

#include "memory.hpp"
#include "memory_setter.hpp"
#include "shared_ptr.hpp"

#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

#include <cassert>
#include <cstddef> // size_t
#include <cstring>
#include <new>

namespace emcee {

class Memory;

/*! \brief  The Vector class provides a growable array of objects.
 *
 *  Vector will inject a Memory reference to classes implementing
 *  `MemoryDependent` or `MemorySetter`.
 *
 *  When a Vector is resized, pointers to its old members are invalid.
 *
 */
template<typename T>
class Vector : public virtual MemoryDependent, public virtual MemorySetter {
 public:

  /*! \brief  Constructs a vector with n elements set to a default value.
   *
   * \param memory reference to Memory instance
   * \param n number of elements
   * \param val default value for elements
   */
  Vector(Memory *memory, size_t n, const T &val = T())
      : memory_(memory), array_(nullptr), capacity_(0), size_(n) {
    assert(memory);

    capacity_ = CalcReserveSize(n);
    array_ = AllocateArray(capacity_);
    for(size_t i = 0; i < n; ++i) {
      InitAt(i, val);
    }
  }

  /*! \brief Constructs an empty Vector of size 0. */
  Vector(Memory *memory) :
      memory_(memory),
      array_(nullptr),
      size_(0),
      capacity_(0)
  { }

  /*! \brief  Copy constructs a vector.
   *
   * This vector contains a copy of the elements, so if the elements of `rhs`
   * are later changed, elements in this instance are not altered.
   *
   * \param rhs
   * \return
   */
  Vector(const Vector &rhs) :
      memory_(nullptr),
      array_(nullptr),
      capacity_(0),
      size_(0) {

    InitWithCopy(rhs);
  }

  void Clear() {
    while (size() > 0) {
      EraseAt(size()-1);
    }
  }

  void SetMemory(Memory * memory) override {
    Clear();
    memory_ = memory;
  }

  /*! \brief  Calls destructor on array elements. */
  ~Vector() {
    DestroyArray();
    if(memory_ && array_) {
      memory_->Free(array_);
      array_ = nullptr;
      memory_ = nullptr;
    }
  }

  /*! \brief Calculates ideal minimum capacity to hold `min_size` elements.
   *
   *  Minimum capacity is 1.
   */
  static size_t CalcReserveSize(size_t min_size) {
    size_t size = 1;
    while(size < min_size) {
      size *= 2;
    }

    return size;
  }

  /*! \brief Adds new element to the end of the Vector.
   *
   *    Vector may be resized if the capacity has been reached.
   */
  void PushBack(const T &t) {
    if(size() == capacity()) {
      Reserve(CalcReserveSize(size()+1));
    }

    memset((void *) &array_[size_], 0, sizeof(T));
    InitAt(size_, t);
    ++size_;
  }

  /*! \brief  Erases element at the given index.
   *
   *    Calling this may result in a resize.
   *
   * \param index
   */
  void EraseAt(size_t index) {
    assert(array_);
    assert(index < size_);

    for (size_t i = index; i < size_ - 1; ++i) {
      array_[i] = array_[i + 1];
    }

    // Last element will no longer be needed.
    array_[size_ - 1].~T();
    memset(&array_[size() - 1], 0, sizeof(T));
    --size_;
  }

  void Resize(size_t new_size) {
    Resize(new_size, T());
  }

  void Resize(size_t new_size, const T& value) {
    while(new_size < size()) {
      EraseAt(size() - 1);
    }
    while(new_size > size()) {
      PushBack(value);
    }
  }

  /*! \brief Requests a change in capacity. */
  void Reserve(size_t new_capacity) {
    if(new_capacity <= capacity())
      return;

    assert(memory_);
    size_t old_capacity = capacity_;
    T *old_array = array_;
    capacity_ = CalcReserveSize(new_capacity);
    array_ = AllocateArray(capacity_);
    for(size_t i = 0; i < size(); ++i) {
      InitAt(i, old_array[i]);
    }
    DestroyArray(old_array, old_capacity);
    memory_->Free(old_array);
  }

  /*! \brief  Assigns content of this Vector to the elements in `rhs`.
   *
   *    Elements from `rhs` are copied into this Vector, while the capacity
   *    is adjusted if necessary.
   *
   *    Existing elements of this Vector will be destroyed.
   *
   * \param rhs
   * \return
   */
  Vector& operator=(const Vector& rhs) {
    if(this == &rhs) {
      return *this;
    }
    Vector tmp(rhs);
    std::swap(memory_,tmp.memory_);
    std::swap(array_, tmp.array_);
    std::swap(capacity_, tmp.capacity_);
    std::swap(size_, tmp.size_);
    return *this;
  }

  const T& Front() const { return At(0); }
  T& Front() { return At(0); }
  const T& Back() const { return At(size() - 1); }
  T& Back() { return At(size() - 1); }

  const T &At(size_t idx) const {
    assert(array_);
    assert(idx < size_);
    return array_[idx];
  };

  T &At(size_t idx) {
    assert(array_);
    assert(idx < size_);
    return array_[idx];
  }

  const T &operator[](size_t idx) const { return array_[idx]; };
  T &operator[](size_t idx) { return array_[idx]; }

  /*! Returns number of elements in this Vector. */
  size_t size() const { return size_; }
  /*! Returns capacity of the Vector. */
  size_t capacity() const { return capacity_; }


 private:
  Memory *memory_;
  T* array_;
  size_t capacity_;
  size_t size_;

  /*
   * Initializes this Vector by copying elements from rhs.
   *
   * Only call in constructor as it does not destroy existing elements.
   */
  void InitWithCopy(const Vector &rhs) {
    assert(!array_);
    assert(size_ == 0);
    if(rhs.memory_) {
      memory_ = rhs.memory_;
      capacity_ = CalcReserveSize(rhs.size());
      array_ = AllocateArray(capacity_);
      size_ = rhs.size_;
      for(size_t i = 0; i < rhs.size(); ++i) {
        (*this)[i] = rhs[i];
      }
    }
  }

  /*
   * Initializes element at given index with provided value.
   */
  void InitAt(size_t idx, const T &new_val) {
    boost::has_trivial_default_constructor<T> has_trivial_constructor;
    if(has_trivial_constructor) {
      InitAtTrivial(idx, new_val);
    } else {
      InitAtNonTrivial(idx, new_val);
    }
  }

  /*
   * Initializes non-trivial element at given index with provided value,
   * injecting Memory reference into compatible classes.
   */
  void InitAtNonTrivial(size_t idx, const T &new_val) {
    boost::is_base_of<MemoryDependentWithCopy,T> is_memory_dependent;
    MemoryDependentWithCopy::ConstructAt(&array_[idx], memory_, new_val);
    MemorySetter::Inject(array_[idx], memory_);
  }

  /*
   * Initializes trivial element at given index with provided value.
   */
  void InitAtTrivial(size_t idx, const T &new_val) {
    array_[idx] = T(new_val);
  }

  /*
   * Calls destructor for elements of this Vector.
   */
  void DestroyArray() {
    DestroyArray(array_, size_);
  }

  /*
   * Calls destructor for elements in the array.
   */
  static void DestroyArray(T *p, size_t num_elements) {
    boost::has_trivial_destructor<T> has_trivial_destructor;
    if(!has_trivial_destructor) {
      DestroyArrayNonTrivial(p, num_elements);
    }
  }

  /*
   * Calls destructor for non-trivial elements in the array.
   */
  static void DestroyArrayNonTrivial(T *p, size_t size) {
    for(size_t i = 0; i < size; ++i) {
      p[i].~T();
    }
  }

  T* AllocateArray(size_t size) {
    assert(memory_);

    void *ptr = memory_->Allocate(sizeof(T) * size);
    T *array = static_cast<T*>(ptr);
    return array;
  }
};

}

#endif //PIOUS_VECTOR_H
