/*
 * Created by The Pious Authors on 26/09/2016.
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
#ifndef PIOUS_OBJECT_HPP
#define PIOUS_OBJECT_HPP

#include "memory.hpp"
#include "memory_setter.hpp"
#include "memory_dependent.hpp"

#include <cassert>
#include <cstdint>

#include <boost/type_traits/is_base_of.hpp>

namespace pious {

struct ArrayAllocation {
  size_t size;
  void *array;

  /*!
   * \brief Creates an instance with an `array` pointer to the address
   *        that immediately follows this instance.
   * \param size Size of array.
   */
  ArrayAllocation(size_t size);

  /*!
   * \brief Initializes and returns an instance at the address of `vptr`.
   *
   * \param vptr Pointer to
   * \param size Size of array.
   */
  static ArrayAllocation* InitFromPtr(void *vptr, size_t size);

  /*!
   * \brief Returns a pointer to the instance associated with the array.
   *    nullptr is returned if there is no associated instance.
   */
  static ArrayAllocation* FindFromArrayPtr(void *array);
};

/*! \brief  Provides methods to instantiate and delete objects with a supplied
 *          memory manager.
 *
 *  The Memory instance will be injected into objects descending from
 *  MemorySetter or MemoryDependent.
 */
template<typename T>
class Object{
 public:
  Object(Memory &memory) : mem_(&memory) {}

  /*!
   * Allocates and constructs a default instance of T, injecting a pointer
   * to memory if T derives from MemoryDependent or MemorySetter.
   */
  T* New() {
    assert(mem_);
    if(!mem_) return nullptr;

    void *vptr = mem_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = New(vptr);

    MemorySetter::Inject(*ptr, mem_);
    return ptr;
  }

  /*!
   * \brief Constructs a default instance of T at the given address.
   *
   * Injects pointer to memory if T derives from MemorySetter or MemoryDependent.
   */
  T *New(void *vptr) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    T *ptr = Construct(vptr, is_memory_dependent);
    MemorySetter::Inject(*ptr, mem_);
    return ptr;
  }

  /*!
   * \brief Allocates and copy constructs an instance of T.
   *
   * Injects a pointer to memory if T derives from MemorySetter or
   * MemoryDependent.
   */
  T* New(const T &other) {
    assert(mem_);
    if(!mem_) return nullptr;

    void *vptr = mem_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = Construct(vptr, other);
    MemorySetter::Inject(*ptr, mem_);
    return ptr;
  }

  /*!
   * Copy constructs an instance of T at the given address.
   *
   * Injects a pointer to memory of T derives from MemorySetter or
   * MemoryDepenent.
   */
  T *New(void *vptr, const T &other) {
    // It is useful to provide this method for New[].

    boost::is_base_of<MemoryDependent,T> is_os_dependent;
    T *ptr = Construct(vptr, other, is_os_dependent);
    return ptr;
  }

  void Delete(T *ptr) {
    assert(mem_);

    ptr->~T();
    mem_->Free(ptr);
  }


 private:
  Memory *mem_;

  T* Construct(void *vptr, boost::true_type) {
    return new(vptr)T(*mem_);
  }

  T* Construct(void *vptr, boost::false_type) {
    return new(vptr)T();
  }

  T* Construct(void *vptr, const T &other, boost::true_type) {
    return new(vptr)T(*mem_, other);
  }

  T* Construct(void *vptr, const T &other, boost::false_type) {
    return new(vptr)T(*mem_);
  }

};

template<typename T>
class Object<T[]> {
 public:

  Object(Memory &memory) : mem_(&memory) {}

  /*! \brief Deletes an array of `T`.
   */
  void Delete(T *array) {
    assert(mem_);

    ArrayAllocation *allocation =
        ArrayAllocation::FindFromArrayPtr(array);

    assert(allocation);
    assert(allocation->array == array);

    size_t size = allocation->size;

    for(size_t i = 0; i < size; ++i) {
      array[i].~T();
    }

    mem_->Free(allocation);
  }

 private:
  Memory *mem_;
};

/*! \brief  Creates array of type
 *  \example
 *  \code
 *      Foo *foo_array = Object<Foo[10]>(os).New();
 *  \endcode
 */
template<typename T, size_t N>
class Object <T[N]> {
 public:
  enum { kArraySize = sizeof(T[N]) };

  Object(Memory &memory) : mem_(&memory) {}

  /*!
   * \brief Allocates and copy constructs an array of T.
   *
   * A pointer to a `Memory` instance will be injected into the object if
   * it descends from MemoryDependent or MemorySetter.
   */
  T* New(const T &other) {
    ArrayAllocation *allocation = NewAllocation(other);
    if(allocation)
      return static_cast<T*>(allocation->array);

    return nullptr;
  }

  /*!
   * \brief Allocates and default constructs an array of T.
   *
   * A pointer to a `Memory` instance will be injected into the object if
   * it descends from MemoryDependent or MemorySetter.
   */
  T* New() {
    ArrayAllocation *allocation = NewAllocation();
    if(allocation)
      return static_cast<T*>(allocation->array);

    return nullptr;
  }

  /*!
   * Allocates and default constructs an array of T, returning the
   * ArrayAllocation pointer.
   *
   * \sa template<typename T,size_t N> Object::New(const T&other)
   */
  ArrayAllocation* NewAllocation(const T&other) {
    ArrayAllocation *allocation = AllocateArray();
    T *array = static_cast<T*>(allocation->array);

    for(size_t i = 0; i < N; ++i) {
      Object<T>(*mem_).New(&array[i], other);
    }

    return allocation;
  }

  /*!
   * Allocates and copy constructs an array of T, returning the
   * ArrayAllocation pointer.
   *
   * \sa template<typename T,size_t N> Object::New(const T&other)
   */
  ArrayAllocation* NewAllocation() {
    ArrayAllocation *allocation = AllocateArray();

    T *array = static_cast<T*>(allocation->array);

    for(size_t i = 0; i < N; ++i) {
      Object<T>(*mem_).New(&array[i]);
    }

    return allocation;
  }

  void Delete(T *array) {
    return Object<T[]>(*mem_).Delete(array);
  }

 private:
  Memory *mem_;

  ArrayAllocation* AllocateArray() {
    assert(mem_);

    size_t total_size = sizeof(ArrayAllocation) + kArraySize;
    void *ptr = mem_->Malloc(total_size);
    ArrayAllocation *allocation = ArrayAllocation::InitFromPtr(ptr, N);
    return allocation;
  }
};

}

#endif /*PIOUS_OS_OP_HPP*/
