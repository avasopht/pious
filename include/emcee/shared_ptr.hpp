/*
 * Created by The Pious Authors on 04/10/2016.
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

#ifndef PIOUS_SHARED_PTR_HPP
#define PIOUS_SHARED_PTR_HPP

#include "emcee/memory.hpp"
#include "emcee/deleter.hpp"
#include "emcee/reference_counter.hpp"
#include "emcee/shared_count.hpp"
#include "unique_ptr.hpp"

namespace emcee {

template<typename T>
class SharedPtr : public MemoryDependent {
 public:
  typedef TypedDeleter<T> DefaultDeleterType;


  SharedPtr(Memory &memory) : memory_(&memory), ptr_(nullptr) {}


  template<typename Y> SharedPtr(Memory &memory, Y *p)
      : memory_(&memory),
        ptr_(nullptr) {
    Reset(p);
  }

  SharedPtr(const SharedPtr &other) {
    Reset(other);
  }

  template<typename Y> SharedPtr(UniquePtr<Y> &unique)
    : memory_(nullptr),
      ptr_(nullptr) {
    Reset(unique);
  }

  SharedPtr& Create() {
    if(!memory_)
      return *this;

    T* ptr = emcee::New<T>(*memory_).Create();
    Reset(ptr);
    return *this;
  }

  SharedPtr& Create(const T &other) {
    if(!memory_)
      return *this;

    T* ptr = emcee::New<T>(*memory_).Create(other);
    Reset(ptr);
    return *this;
  }

  void Reset() {
    count_ = SharedCount();
  }

  template<typename Y> void Reset(Y *p) {
    if(!memory_)
      return;

    if(!p) {
      Reset();
    } else {
      ptr_ = p;
      DefaultDeleterType *deleter = emcee::New<DefaultDeleterType>(*memory_).Create();
      deleter->Watch(ptr_);

      ReferenceCounter *counter = emcee::New<ReferenceCounter>(*memory_).Create();
      counter->SetDeleter(deleter);
      count_ = SharedCount(counter);
    }
  }

  template<typename Y> void Reset(UniquePtr<Y> &unique) {
    memory_ = unique.memory();
    Reset(unique.Release());
  }

  template<typename Y> void Reset(const SharedPtr<Y> &other) {
    if(&other == this || other.ptr_ == ptr_) {
      return;
    } else {
      memory_ = other.memory_;
      ptr_ = other.ptr_;
      count_ = SharedCount(other.count_);
    }
  }

  void Swap(SharedPtr &b) {
    std::swap(memory_, b.memory_);
    std::swap(ptr_, b.ptr_);
    std::swap(count_, b.count_);
  }

  size_t use_count() const { return count_.use_count(); }
  bool unique() const { return use_count() == 1; }

  T* get() const { return ptr_; }
  T& operator*() const { return *get(); }
  T* operator->() const { return get(); }


  SharedPtr& operator=(const SharedPtr &rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y> SharedPtr& operator=(const SharedPtr<Y> &rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>SharedPtr& operator=(UniquePtr<Y> &unique) {
    Reset(unique);
    return *this;
  }

 private:
  Memory *memory_;
  T *ptr_;
  SharedCount count_;

};

}

#endif /* PIOUS_SHARED_PTR_HPP */
