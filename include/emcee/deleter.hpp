/*
 * Created by The Pious Authors on 08/09/2016.
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

#ifndef PIOUS_DELETER_HPP
#define PIOUS_DELETER_HPP

#include "new.hpp"

#include <cassert>

namespace emcee {

/*! \brief Interface for a deleter.
 *
 *  A Deleter has the responsibility of deleting an object from an Os instance.
 *  Use TypedDeleter to create a Deleter instance
 */
class Deleter {
 public:
  virtual ~Deleter() {};
  virtual void Delete() = 0;
};

template<typename T>
class TypedDeleter : public Deleter {
 public:
  TypedDeleter() : mem_(nullptr), ptr_(nullptr) { }
  ~TypedDeleter() {
    mem_ = nullptr;
    ptr_ = nullptr;
  }

  void Init(Memory &mem) {
    mem_ = &mem;
  }

  TypedDeleter(Memory &mem) : mem_(&mem), ptr_(nullptr) {}

  TypedDeleter(Memory &mem, T* ptr) : mem_(&mem), ptr_(ptr) { assert(mem_); }

  TypedDeleter(const TypedDeleter &rhs) : mem_(rhs.mem_), ptr_(rhs.ptr_)  { }

  void Watch(T *ptr) {
    assert(mem_);
    ptr_ = ptr;
  }

  void Delete() override {
    if(ptr_) {
      emcee::Delete(ptr_);
      ptr_ = nullptr;
    }
  }

 private:
  Memory *mem_;
  T *ptr_;
};

}

#endif /*PIOUS_DELETER_HPP*/
