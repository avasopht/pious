/*
 * Created by keldon on 19/08/16.
 */

#ifndef PIOUS_SCOPED_PTR_HPP
#define PIOUS_SCOPED_PTR_HPP

#include "os.hpp"
#include "os_op.hpp"
#include "deleter.hpp"

#include <cassert>

namespace pious {

class Deleter;

/*!
 *  pious::UniquePtr is a smart pointer that retains sole ownership of an object through a pointer,
 *  destroying that object when the unique pointer goes out of scope or is assigned to a new pointer.
 */
template <typename T, typename DeleterType = TypedDeleter<T> >
class UniquePtr {
 public:

  UniquePtr(const UniquePtr &other) : os_(other.os_), pointer_(other.pointer_), deleter_(other.deleter_) {
    const_cast<UniquePtr*>(&other)->pointer_ = nullptr;
    const_cast<UniquePtr*>(&other)->deleter_ = nullptr;
  }

  UniquePtr(Os &os) : os_(&os), pointer_(nullptr){}

  UniquePtr() : os_(nullptr), pointer_(nullptr) {}
  UniquePtr(Os& os, T *ptr) : os_(&os), pointer_(ptr) {
    deleter_ = OsOp<T>(*os_).New(DeleterType(*os_, pointer_));
  }

  T* New() {
    if(!os_)
      return nullptr;

    T *ptr = OsOp<T>(*os_).New();
    assert(ptr);
    return ptr;
  }

  void Reset(T *ptr = nullptr) {
    assert(os_);
    Release();
    deleter_ = OsOp<T>(*os_).New(DeleterType(*os_, pointer_));
  }

  void Release() {
    if(pointer_) {
      assert(deleter_);

      deleter_->Delete();

      OsOp<DeleterType>(*os_).Delete(deleter_);
      pointer_ = nullptr;
    }
  }

  ~UniquePtr() {
    Release();
    if(os_) {
      OsOp<DeleterType>(*os_).Delete(deleter_);
    }
  }


  const T* get() const { return pointer_; }
  T* get() { return pointer_; }

  const T& operator*() const { return *get(); }
  T& operator*() { return *get(); }

  UniquePtr& operator=(const UniquePtr &rhs) {
    assert(rhs.os_ == os_);

    if(&rhs == this) return *this;

    Release();
    pointer_ = rhs.pointer_;
    deleter_ = rhs.deleter_;
    const_cast< UniquePtr* >(&rhs)->pointer_ = nullptr;
    const_cast< UniquePtr* >(&rhs)->deleter_ = nullptr;

    return *this;
  }

 private:
  Os *os_;
  T *pointer_;
  Deleter *deleter_;
};

}

#endif /* PIOUS_SCOPED_PTR_HPP */
