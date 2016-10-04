/*
 * Created by The Pious Authors on 19/08/2016.
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

#ifndef PIOUS_SCOPED_PTR_HPP
#define PIOUS_SCOPED_PTR_HPP

#include "emcee/memory.hpp"
#include "emcee/new.hpp"
#include "emcee/deleter.hpp"

#include <cassert>

namespace emcee {

class Deleter;

/*!
 *  pious::UniquePtr is a smart pointer that retains sole ownership of an object through a pointer,
 *  destroying that object when the unique pointer goes out of scope or is assigned to a new pointer.
 */
template <typename T, typename DeleterType = TypedDeleter<T> >
class UniquePtr {
 public:

  UniquePtr(const UniquePtr &other) : memory_(other.memory_), pointer_(other.pointer_), deleter_(other.deleter_) {
    const_cast<UniquePtr*>(&other)->pointer_ = nullptr;
    const_cast<UniquePtr*>(&other)->deleter_ = nullptr;
  }

  UniquePtr(Memory &memory) : memory_(&memory), pointer_(nullptr){}

  UniquePtr() : memory_(nullptr), pointer_(nullptr) {}
  UniquePtr(Memory& os, T *ptr) : memory_(&os), pointer_(ptr) {
    deleter_ = emcee::New<DeleterType>(*memory_).Create(DeleterType(*memory_, ptr));
  }

  T* New() {
    if(!memory_)
      return nullptr;

    T *ptr = emcee::New<T>(*memory_).Create();
    assert(ptr);
    return ptr;
  }

  void Reset(T *ptr = nullptr) {
    assert(memory_);
    Release();
    pointer_ = ptr;
    deleter_ = emcee::New<DeleterType>(*memory_).Create(DeleterType(*memory_, pointer_));
  }

  void Release() {
    if(pointer_) {
      assert(deleter_);

      deleter_->Delete();
      emcee::Delete(deleter_);

      deleter_ = nullptr;
      pointer_ = nullptr;
    }
  }

  ~UniquePtr() {
    Release();
    if(memory_ && deleter_) {
      emcee::Delete(deleter_);
    }
  }


  const T* get() const { return pointer_; }
  T* get() { return pointer_; }

  const T& operator*() const { return *get(); }
  T& operator*() { return *get(); }

  UniquePtr& operator=(const UniquePtr &rhs) {
    assert(rhs.memory_ == memory_);

    if(&rhs == this) return *this;

    Release();
    pointer_ = rhs.pointer_;
    deleter_ = rhs.deleter_;
    const_cast< UniquePtr* >(&rhs)->pointer_ = nullptr;
    const_cast< UniquePtr* >(&rhs)->deleter_ = nullptr;

    return *this;
  }

 private:
  Memory *memory_;
  T *pointer_;
  Deleter *deleter_;
};

}

#endif /* PIOUS_SCOPED_PTR_HPP */
