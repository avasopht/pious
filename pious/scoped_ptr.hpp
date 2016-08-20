/*
 * Created by keldon on 19/08/16.
 */

#ifndef PIOUS_SCOPED_PTR_HPP
#define PIOUS_SCOPED_PTR_HPP

#include "os.hpp"

#include <cassert>

namespace pious {

template <typename T>
class ScopedPtr {
 public:
  ScopedPtr(const ScopedPtr &other) : os_(other.os_) {
    pointer_ = other.pointer_;
    const_cast<ScopedPtr*>(&other)->pointer_ = nullptr;
  }

  ScopedPtr() : os_(nullptr), pointer_(nullptr) {}
  ScopedPtr(Os& os, T *ptr) : os_(&os), pointer_(ptr) { }
  ~ScopedPtr() {
    DeletePointer();
  }

  const T* get() const { return pointer_; }
  T* get() { return pointer_; }

  const T& operator*() const { return *get(); }
  T& operator*() { return *get(); }

  ScopedPtr& operator=(const ScopedPtr &rhs) {
    assert(rhs.os_ == os_);

    if(&rhs == this) return *this;

    DeletePointer();
    pointer_ = rhs.pointer_;
    const_cast< ScopedPtr<T>* >(&rhs)->pointer_ = nullptr;

    return *this;
  }

 private:
  Os *os_;
  T *pointer_;

  void DeletePointer() {
    if(pointer_) {
      os_->Free(pointer_);
      pointer_ = nullptr;
    }
  }
};

}

#endif /* PIOUS_SCOPED_PTR_HPP */
