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

#include <algorithm>

#include "platform.hpp"
#include "deleter.hpp"
#include "reference_counter.hpp"
#include "shared_count.hpp"
#include "unique_ptr.hpp"

namespace emcee {

template<typename T>
class WeakPtr;

/*! \brief Implements a reference countered smart pointer.
 *
 * This class respects Memory injection on its object creation methods.
 */
template<typename T>
class SharedPtr : public virtual MemoryDependentWithCopy {
 public:
  typedef TypedDeleter<T> DefaultDeleterType;

  template<typename Y> friend
  class WeakPtr;

  SharedPtr() : memory_(nullptr), ptr_(nullptr) {}

  SharedPtr(Platform * memory, const SharedPtr<T> & other) : memory_(memory), ptr_(nullptr) {
    Reset(other);
  }

  explicit SharedPtr(Platform * memory) : memory_(memory), ptr_(nullptr) {}

  template<typename Y>
  SharedPtr(Platform * memory, Y * p)
      : memory_(memory),
        ptr_(nullptr) {
    Reset(p);
  }

  SharedPtr(const SharedPtr & other) : memory_(other.memory_) {
    Reset(other);
  }

  template<typename Y>
  explicit SharedPtr(UniquePtr<Y> & unique)
      : memory_(nullptr),
        ptr_(nullptr) {
    Reset(unique);
  }

  void SetMemory(Platform * m) {
    memory_ = m;
  }

  SharedPtr & Create() {
    if (!memory_)
      return *this;

    T * ptr = emcee::New<T>(memory_).Create();
    Reset(ptr);
    return *this;
  }

  SharedPtr & Create(const T & other) {
    if (!memory_)
      return *this;

    T * ptr = emcee::New<T>(memory_).Create(other);
    Reset(ptr);
    return *this;
  }

  Platform * memory() const { return memory_; }

  void Reset() {
    count_ = SharedCount();
    ptr_ = nullptr;
  }

  template<typename Y>
  void Reset(Y * p) {
    if (!memory_)
      return;

    if (!p) {
      Reset();
    } else {
      ptr_ = p;
      DefaultDeleterType * deleter = emcee::New<DefaultDeleterType>(memory_).Create();
      deleter->Watch(ptr_);

      ReferenceCounter * counter = emcee::New<ReferenceCounter>(memory_).Create();
      counter->SetDeleter(deleter);
      count_ = SharedCount(counter);
    }
  }

  template<typename Y>
  void Reset(UniquePtr<Y> & unique) {
    memory_ = unique.memory();
    Reset(unique.Release());
  }

  template<typename Y>
  void Reset(const SharedPtr<Y> & other) {
    if (&other == this || other.ptr_ == ptr_) {
      return;
    } else {
      memory_ = other.memory_;
      ptr_ = other.ptr_;
      count_ = SharedCount(other.count_);
    }
  }

  void Swap(SharedPtr & b) {
    std::swap(memory_, b.memory_);
    std::swap(ptr_, b.ptr_);
    std::swap(count_, b.count_);
  }

  size_t use_count() const { return count_.use_count(); }

  bool unique() const { return use_count() == 1; }

  T * get() const { return ptr_; }

  T & operator*() const { return *get(); }

  T * operator->() const { return get(); }

  SharedPtr & operator=(const SharedPtr & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  SharedPtr & operator=(const SharedPtr<Y> & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  SharedPtr & operator=(UniquePtr<Y> & unique) {
    Reset(unique);
    return *this;
  }

  template<typename Y> bool operator==(const SharedPtr<Y> & rhs) const { return ptr_ == rhs.ptr_; }
  template<typename Y> bool operator<(const SharedPtr<Y> & rhs) const { return ptr_ < rhs.ptr_; }
  template<typename Y> bool operator>(const SharedPtr<Y> & rhs) const { return rhs < *this; }
  template<typename Y> bool operator!=(const SharedPtr<Y> & rhs) const { return !(*this == rhs);}
  template<typename Y> bool operator<=(const SharedPtr<Y> & rhs) const { return !(rhs < *this); }
  template<typename Y> bool operator>=(const SharedPtr<Y> & rhs) const { return !(*this < rhs); }

  explicit operator bool() const { return ptr_ != nullptr; }

 private:
  Platform * memory_;
  T * ptr_;
  SharedCount count_;

};

template<typename T>
class SharedPtr<T[]> : public virtual MemoryDependentWithCopy {
 public:
  typedef TypedDeleter<T> DefaultDeleterType;

  template<typename Y> friend
  class WeakPtr;

  SharedPtr() : memory_(nullptr), ptr_(nullptr) {}

  explicit SharedPtr(Platform * mem) : memory_(mem), ptr_(nullptr) {}

  template<typename Y>
  SharedPtr(Platform * memory, Y * p)
      : memory_(memory),
        ptr_(nullptr) {
    Reset(p);
  }

  SharedPtr(Platform * memory, const SharedPtr & other) : memory_(memory), ptr_(nullptr) {
    Reset(other);
  }

  SharedPtr(const SharedPtr & other) {
    Reset(other);
  }

  template<typename Y>
  explicit SharedPtr(UniquePtr<Y> & unique)
      : memory_(nullptr),
        ptr_(nullptr) {
    Reset(unique);
  }

  SharedPtr & Create(size_t count) {
    if (!memory_)
      return *this;

    T * ptr = emcee::New<T[]>(memory_, count).Create();
    Reset(ptr);
    return *this;
  }

  void SetMemory(Platform * memory) { memory_ = memory; }

  SharedPtr & Create(size_t count, const T & other) {
    if (!memory_)
      return *this;

    T * ptr = emcee::New<T[]>(memory_, count).Create(other);
    Reset(ptr);
    return *this;
  }

  void Reset() {
    count_ = SharedCount();
  }

  Platform * memory() const { return memory_; }

  template<typename Y>
  void Reset(Y * p) {
    if (!memory_)
      return;

    if (!p) {
      Reset();
    } else {
      ptr_ = p;
      DefaultDeleterType * deleter = emcee::New<DefaultDeleterType>(memory_).Create();
      deleter->Watch(ptr_);

      ReferenceCounter * counter = emcee::New<ReferenceCounter>(memory_).Create();
      counter->SetDeleter(deleter);
      count_ = SharedCount(counter);
    }
  }

  template<typename Y>
  void Reset(UniquePtr<Y> & unique) {
    memory_ = unique.memory();
    Reset(unique.Release());
  }

  template<typename Y>
  void Reset(const SharedPtr<Y> & other) {
    if (&other == this || other.ptr_ == ptr_) {
      return;
    }

    // We only want to adopt other's memory ptr if we don't have one or other has
    // a valid pointer.
    if (other || !memory_) {
      memory_ = other.memory_;
      ptr_ = other.ptr_;
      count_ = SharedCount(other.count_);
    }
  }

  void Swap(SharedPtr & b) {
    std::swap(memory_, b.memory_);
    T * tmp = ptr_;
    ptr_ = b.ptr_;
    b.ptr_ = tmp;
    std::swap(count_, b.count_);
  }

  size_t use_count() const { return count_.use_count(); }

  bool unique() const { return use_count() == 1; }

  T & operator[](size_t idx) const {
    return ptr_[idx];
  }

  explicit operator bool() const { return ptr_ != nullptr; }

  T * get() const { return ptr_; }

  T & operator*() const { return *get(); }

  T * operator->() const { return get(); }

  template<typename Y> bool operator==(const SharedPtr<Y> & rhs) const { return ptr_ == rhs.ptr_; }
  template<typename Y> bool operator<(const SharedPtr<Y> & rhs) const { return ptr_ < rhs.ptr_; }
  template<typename Y> bool operator>(const SharedPtr<Y> & rhs) const { return rhs < *this; }
  template<typename Y> bool operator!=(const SharedPtr<Y> & rhs) const { return !(*this == rhs);}
  template<typename Y> bool operator<=(const SharedPtr<Y> & rhs) const { return !(rhs < *this); }
  
  SharedPtr & operator=(const SharedPtr & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  SharedPtr & operator=(const SharedPtr<Y> & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  SharedPtr & operator=(UniquePtr<Y> & unique) {
    Reset(unique);
    return *this;
  }

 private:
  Platform * memory_;
  T * ptr_;
  SharedCount count_;
};

}

#endif /* PIOUS_SHARED_PTR_HPP */
