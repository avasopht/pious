/*
 * Created by keldon on 19/08/16.
 */

#ifndef PIOUS_SCOPED_PTR_HPP
#define PIOUS_SCOPED_PTR_HPP

#include "memory.hpp"
#include "object.hpp"
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

  UniquePtr(const UniquePtr &other) : memory_(other.memory_), pointer_(other.pointer_), deleter_(other.deleter_) {
    const_cast<UniquePtr*>(&other)->pointer_ = nullptr;
    const_cast<UniquePtr*>(&other)->deleter_ = nullptr;
  }

  UniquePtr(Memory &memory) : memory_(&memory), pointer_(nullptr){}

  UniquePtr() : memory_(nullptr), pointer_(nullptr) {}
  UniquePtr(Memory& os, T *ptr) : memory_(&os), pointer_(ptr) {
    deleter_ = Object<T>(*memory_).New(DeleterType(*memory_, pointer_));
  }

  T* New() {
    if(!memory_)
      return nullptr;

    T *ptr = Object<T>(*memory_).New();
    assert(ptr);
    return ptr;
  }

  void Reset(T *ptr = nullptr) {
    assert(memory_);
    Release();
    deleter_ = Object<T>(*memory_).New(DeleterType(*memory_, pointer_));
  }

  void Release() {
    if(pointer_) {
      assert(deleter_);

      deleter_->Delete();

      Object<DeleterType>(*memory_).Delete(deleter_);
      pointer_ = nullptr;
    }
  }

  ~UniquePtr() {
    Release();
    if(memory_) {
      Object<DeleterType>(*memory_).Delete(deleter_);
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
