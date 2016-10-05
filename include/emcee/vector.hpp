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

#include "emcee/memory.hpp"
#include "emcee/memory_setter.hpp"
#include "shared_ptr.hpp"

#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

#include <cassert>
#include <cstddef> // size_t
#include <cstring>
#include <new>

namespace emcee {

class Memory;

template<typename T>
class Vector {
 public:
  Vector(Memory &memory, size_t n, const T &val = T())
      : memory_(&memory), array_(nullptr), capacity_(0), size_(n) {
    assert(&memory);

    capacity_ = CalcReserveSize(n);
    array_ = AllocateArray(capacity_);
    for(size_t i = 0; i < n; ++i) {
      InitAt(i, val);
    }
  }

  Vector(Memory &memory) :
      memory_(&memory),
      array_(nullptr),
      size_(0),
      capacity_(0)
  { }

  Vector(const Vector &rhs) :
      memory_(rhs.memory_),
      array_(nullptr),
      capacity_(0),
      size_(0) {

    assert(memory_);

    capacity_ = CalcReserveSize(rhs.size());
    array_ = AllocateArray(capacity_);
    size_ = rhs.size_;
    for(size_t i = 0; i < rhs.size(); ++i) {
      (*this)[i] = rhs[i];
    }
  }

  static size_t CalcReserveSize(size_t min_size) {
    size_t size = 1;
    while(size < min_size)
      size *= 2;

    return size;
  }

  ~Vector();

  void PushBack(const T &t);

  void EraseAt(size_t idx);

  void Reserve(size_t n) {
    if(n <= capacity())
      return;

    size_t old_capacity = capacity_;
    T *old_array = array_;
    capacity_ = CalcReserveSize(n);
    array_ = AllocateArray(capacity_);
    for(size_t i = 0; i < size(); ++i) {
      InitAt(i, old_array[i]);
    }
    DestroyArray(old_array, old_capacity);
    memory_->Free(old_array);
  }

  Vector& operator=(const Vector& rhs) {
    if(this == &rhs)
      return *this;

    Vector tmp(rhs);
    std::swap(memory_,tmp.memory_);
    std::swap(array_, tmp.array_);
    std::swap(capacity_, tmp.capacity_);
    std::swap(size_, tmp.size_);

    return *this;
  }

  const T &At(size_t idx) const {
    assert(idx < size_);
    return array_[idx];
  };

  T &At(size_t idx) {
    assert(idx < size_);
    return array_[idx];
  }

  const T &operator[](size_t idx) const { return array_[idx]; };
  T &operator[](size_t idx) { return array_[idx]; }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
 private:
  Memory *memory_;
  T* array_;
  size_t capacity_;
  size_t size_;

  void InitAt(size_t idx, const T &new_val) {
    boost::has_trivial_default_constructor<T> type;
    InitAt(type, idx, new_val);
  }

  void InitAt(boost::false_type, size_t idx, const T &new_val) {
    // Has non-trivial constructor.
    if(boost::is_base_of<MemoryDependent, T>::value) {
      new (&array_[idx]) T(*memory_, new_val);
    } else {
      new (&array_[idx]) T(new_val);
    }
    MemorySetter::Inject(array_[idx], memory_);
  }

  void InitAt(boost::true_type, size_t idx, const T &new_val) {
    // Has trivial constructor.
    array_[idx] = T(new_val);
  }

  void DestroyArray() {
    DestroyArray(array_, size_);
  }

  void DestroyArray(T *p, size_t size) {
    boost::has_trivial_destructor<T> has_trivial_destructor;
    DestroyArray(array_, size_, has_trivial_destructor);
  }

  void DestroyArray(T *p, size_t size, boost::true_type) {
    for(size_t i = 0; i < size; ++i) {
      array_[i].~T();
    }
  }

  void DestroyArray(T*, size_t, boost::false_type) {}

  T* AllocateArray(size_t size) {
    assert(memory_);

    void *ptr = memory_->Allocate(sizeof(T) * size);
    T *array = static_cast<T*>(ptr);
    return array;
  }

  void Destroy(boost::true_type) {
    // Has trivial destructor (do nothing).
  }
};


template<typename T>
void Vector<T>::PushBack(const T &t) {
  if(size() == capacity()) {
    Reserve(CalcReserveSize(size()+1));
  }

  memset(&array_[size_], 0, sizeof(T));
  InitAt(size_, t);
  ++size_;
}

template<typename T>
Vector<T>::~Vector() {
  DestroyArray();
  if(memory_ && array_) {
    memory_->Free(array_);
    array_ = nullptr;
    memory_ = nullptr;
  }
}

template<typename T>
void Vector<T>::EraseAt(size_t idx) {
  assert(idx < size_);
  for (size_t i = idx; i < size_ - 1; ++i) {
    array_[i] = array_[i + 1];
  }

  array_[size_ - 1].~T();
  memset(&array_[size() - 1], 0, sizeof(T));
  --size_;
}

}

#endif //PIOUS_VECTOR_H
