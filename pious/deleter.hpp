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

#include <cassert>

namespace pious {

class Os;

/*! \brief Interface for a deleter.
 *
 *  A Deleter has the responsibility of deleting an object from an Os instance.
 *  Use TypedDeleter to create a Deleter instance
 */
class Deleter {
 public:
  virtual ~Deleter() = 0;
  virtual void Destroy() = 0;
};

template<typename T>
class TypedDeleter : public Deleter {
 public:
  TypedDeleter() : os_(nullptr), ptr_(nullptr) {}
  ~TypedDeleter() {
    Destroy();
    os_ = nullptr;
  }

  void Init(Os &os) {
    os_ = &os;
  }

  TypedDeleter(Os &os) : os_(&os), ptr_(nullptr) {}

  TypedDeleter(Os &os, T* ptr) : os_(&os), ptr_(ptr) { assert(os_); }

  TypedDeleter(const TypedDeleter &rhs) : os_(rhs.os_), ptr_(rhs.ptr_)  { }

  void Watch(T *ptr) {
    assert(os_);
    ptr_ = ptr;
  }

  void Destroy() override {
    if(ptr_) {
      os_->Delete(ptr_);
      ptr_ = nullptr;
    }
  }

 private:
  Os *os_;
  T *ptr_;
};

}

#endif /*PIOUS_DELETER_HPP*/
