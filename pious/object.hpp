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

#include "os.hpp"
#include "os_setter.hpp"
#include "os_dependent.hpp"

#include <boost/type_traits/is_base_of.hpp>

#include <cassert>

namespace pious {

/*! \brief  Provides methods to instantiate and delete objects with a supplied
 *          memory manager.
 *
 *  The Os instance will be injected into objects descending from OsSetter or
 *  OsDependent.
 */
template<typename T>
class Object{
 public:
  Object(Os &os) : os_(&os) {}

  T* New() {
    assert(os_);
    if(!os_) return nullptr;

    void *vptr = os_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = New(vptr);

    OsSetter::InjectOs(*ptr, os_);
    return ptr;
  }

  T *New(void *vptr) {
    boost::is_base_of<OsDependent,T> is_os_dependent;
    T *ptr = New(vptr, is_os_dependent);
    return ptr;
  }

  T* New(const T &other) {
    assert(os_);
    if(!os_) return nullptr;

    void *vptr = os_->Calloc(1, sizeof(T));
    if(!vptr) return nullptr;

    T *ptr = New(vptr, other);
    OsSetter::InjectOs(*ptr, os_);
    return ptr;
  }

  T *New(void *vptr, const T &other) {
    boost::is_base_of<OsDependent,T> is_os_dependent;
    T *ptr = New(vptr, other, is_os_dependent);
    return ptr;
  }

  void Delete(T *ptr) {
    assert(os_);

    ptr->~T();
    os_->Free(ptr);
  }


 private:
  Os *os_;

  T* New(void *vptr, boost::true_type) {
    return new(vptr)T(*os_);
  }

  T* New(void *vptr, boost::false_type) {
    return new(vptr)T();
  }

  T* New(void *vptr, const T& other, boost::true_type) {
    return new(vptr)T(*os_, other);
  }

  T* New(void *vptr, const T& other, boost::false_type) {
    return new(vptr)T(*os_);
  }

};

template<typename T>
class Object<T[]> {
 public:

  Object(Os &os) : os_(&os) {}

  void Delete(void *ptr) {
    assert(os_);

    size_t size = static_cast<size_t*>(ptr)[-1];

    T *array = static_cast<T*>(ptr);

    for(size_t i = 0; i < size; ++i) {
      array[i]->~T();
    }

    os_->Free(ptr);
  }

 private:
  Os *os_;
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
  Object(Os &os) : os_(&os) {}

  T* New() {
    assert(os_);
    if(!os_)  return nullptr;

    void *vptr = os_->Calloc(1, sizeof(size_t) + sizeof(T));
    if(!vptr) return nullptr;

    static_cast<size_t*>(vptr)[0] = N;

    void *array_vptr = &static_cast<size_t*>(vptr)[1];
    T *array = static_cast<T*>(array_vptr);

    for(size_t i = 0; i < N; ++i) {
      Object<T>(*os_).New(&array[i]);
      OsSetter::InjectOs(array[i], os_);
    }

    return array;
  }

  void Delete(void *ptr) {
    assert(os_);

    size_t size = static_cast<size_t*>(ptr)[-1];

    T *array = static_cast<T*>(ptr);

    for(size_t i = 0; i < size; ++i) {
      array[i]->~T();
    }

    os_->Free(ptr);
  }

 private:
  Os *os_;
};

}

#endif /*PIOUS_OS_OP_HPP*/
