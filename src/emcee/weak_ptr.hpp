/*
 * Created by The Pious Authors on 20/10/16.
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

#ifndef PIOUS_WEAK_PTR_HPP
#define PIOUS_WEAK_PTR_HPP

#include "platform.hpp"
#include "memory_dependent.hpp"
#include "deleter.hpp"
#include "weak_count.hpp"
#include "shared_ptr.hpp"

namespace emcee {

template<typename T>
class WeakPtr {
 public:
  typedef TypedDeleter<T> DefaultDeleterType;

  WeakPtr() : ptr_(nullptr) {}

  WeakPtr(const WeakPtr & other) : ptr_(nullptr) {
    Reset(other);
  }

  template<typename Y>
  explicit WeakPtr(SharedPtr<Y> & shared) : ptr_(nullptr) {
    Reset(shared);
  }

  void Reset() {
    count_ = WeakCount();
    ptr_ = nullptr;
  }

  template<typename Y>
  void Reset(SharedPtr<Y> & other) {
    ptr_ = other.get();
    count_ = WeakCount(other.count_);
  }

  template<typename Y>
  void Reset(const WeakPtr<Y> & other) {
    if (this == &other || ptr_ == other.ptr_)
      return;

    ptr_ = other.ptr_;
    count_ = other.count_;
  }

  void Swap(WeakPtr & b) {
    std::swap(count_, b.count_);
    T * tmp = ptr_;
    ptr_ = b.ptr_;
    b.ptr_ = tmp;
  }

  T * get() const { return count_.use_count() > 0 ? ptr_ : nullptr; }

  T & operator*() const { return *get(); }

  T * operator->() const { return get(); }

  explicit operator bool() const { return ptr_ != nullptr; }

  WeakPtr & operator=(const WeakPtr & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  WeakPtr & operator=(WeakPtr<Y> & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  WeakPtr & operator=(SharedPtr<Y> & shared) {
    Reset(shared);
    return *this;
  }

 private:
  T * ptr_;
  WeakCount count_;
};

template<typename T>
class WeakPtr<T[]> {
 public:
  typedef TypedDeleter<T> DefaultDeleterType;

  WeakPtr(const WeakPtr & other) : ptr_(nullptr) {
    Reset(other);
  }

  template<typename Y>
  explicit WeakPtr(SharedPtr<Y> & shared) : ptr_(nullptr) {
    Reset(shared);
  }

  void Reset() {
    count_ = WeakCount();
    ptr_ = nullptr;
  }

  template<typename Y>
  void Reset(SharedPtr<Y> & other) {
    ptr_ = other.get();
    count_ = WeakCount(other.count_);
  }

  template<typename Y>
  void Reset(const WeakPtr<Y> & other) {
    if (this == &other || ptr_ == other.ptr_)
      return;

    ptr_ = other.ptr_;
    count_ = other.count_;
  }

  void Swap(WeakPtr & b) {
    std::swap(count_, b.count_);
    T * tmp = ptr_;
    ptr_ = b.ptr_;
    b.ptr_ = tmp;
  }

  T & operator[](size_t idx) const {
    return ptr_[idx];
  }

  T * get() const { return count_.use_count() > 0 ? ptr_ : nullptr; }

  T & operator*() const { return *get(); }

  T * operator->() const { return get(); }

  WeakPtr & operator=(const WeakPtr & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  WeakPtr & operator=(WeakPtr<Y> & rhs) {
    Reset(rhs);
    return *this;
  }

  template<typename Y>
  WeakPtr & operator=(SharedPtr<Y> & shared) {
    Reset(shared);
    return *this;
  }

 private:
  T * ptr_;
  WeakCount count_;
};

}

#endif //PIOUS_WEAK_PTR_HPP
