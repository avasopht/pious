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

  T* New() {
    assert(mem_);
    if(!mem_) return nullptr;

    void *vptr = mem_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = New(vptr);

    MemorySetter::InjectMemory(*ptr, mem_);
    return ptr;
  }

  T *New(void *vptr) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    T *ptr = New(vptr, is_memory_dependent);
    return ptr;
  }

  T* New(const T &other) {
    assert(mem_);
    if(!mem_) return nullptr;

    void *vptr = mem_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = New(vptr, other);
    MemorySetter::InjectMemory(*ptr, mem_);
    return ptr;
  }

  T *New(void *vptr, const T &other) {
    boost::is_base_of<MemoryDependent,T> is_os_dependent;
    T *ptr = New(vptr, other, is_os_dependent);
    return ptr;
  }

  void Delete(T *ptr) {
    assert(mem_);

    ptr->~T();
    mem_->Free(ptr);
  }


 private:
  Memory *mem_;

  T* New(void *vptr, boost::true_type) {
    return new(vptr)T(*mem_);
  }

  T* New(void *vptr, boost::false_type) {
    return new(vptr)T();
  }

  T* New(void *vptr, const T& other, boost::true_type) {
    return new(vptr)T(*mem_, other);
  }

  T* New(void *vptr, const T& other, boost::false_type) {
    return new(vptr)T(*mem_);
  }

};

template<typename T>
class Object<T[]> {
 public:

  Object(Memory &memory) : mem_(&memory) {}

  /*! \brief Deletes an array of `T`.
   *
   *
   */
  void Delete(void *ptr) {
    assert(mem_);


    T *array = static_cast<T*>(ptr);

    ArrayAllocation *allocation =
        ArrayAllocation::FindFromArrayPtr(array);

    assert(allocation);
    assert(allocation->array == array);

    size_t size = allocation->size;

    for(size_t i = 0; i < size; ++i) {
      array[i]->~T();
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
  Object(Memory &memory) : mem_(&memory) {}

  T* New(const T &other) {
    assert(mem_);
    if(!mem_) return nullptr;
  }

  T* New() {
    assert(mem_);
    if(!mem_)  return nullptr;

    void *vptr = mem_->Calloc(1, sizeof(ArrayAllocation) + sizeof(T[N]));
    if(!vptr) return nullptr;

    ArrayAllocation *allocation =
        ArrayAllocation::InitFromPtr(vptr, N);
    assert(allocation);

    T *array = allocation->array;

    for(size_t i = 0; i < N; ++i) {
      Object<T>(*mem_).New(&array[i]);
      MemorySetter::InjectMemory(array[i], mem_);
      MemorySetter::InjectMemory(array[i], mem_);
    }

    return array;
  }

  void Delete(void *ptr) {
    return Object<T[]>(*mem_).Delete(ptr);
  }

 private:
  Memory *mem_;
};

}

#endif /*PIOUS_OS_OP_HPP*/
