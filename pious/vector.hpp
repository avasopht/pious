//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_VECTOR_H
#define PIOUS_VECTOR_H

#include "memory.hpp"
#include "memory_setter.hpp"

#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>

#include <cassert>
#include <cstddef> // size_t
#include <cstring>
#include <new>

namespace pious {

class Memory;

template<typename T>
class Vector {
 public:
  Vector(Memory &memory, size_t capacity);
  ~Vector();

  void PushBack(const T &t);

  void EraseAt(size_t idx);

  const T &At(size_t idx) const {
    assert(idx < size_);
    return array_[idx];
  };
  T &At(size_t idx) {
    assert(idx < size_);
    return array_[idx];
  }

  const T &operator[](size_t idx) const { return array_[idx]; };
  T &operator[](size_t idx) { return array_[idx]; }

  size_t size() const { return size_; }
  size_t capacity() const { return capacity_; }
 private:
  Memory &memory_;
  size_t capacity_;
  size_t size_;
  T *array_;

  // No copy
  Vector(const Vector &rhs) = delete;
  Vector &operator=(const Vector &rhs) = delete;

  void InitAt(size_t idx, const T &new_val) {
    boost::has_trivial_default_constructor<T> type;
    InitAt(type, idx, new_val);
  }

  void InitAt(boost::false_type, size_t idx, const T &new_val) {
    // Has non-trivial constructor.
    new (&array_[idx]) T(new_val);
    MemorySetter::Inject(array_[idx], &memory_);
  }

  void InitAt(boost::true_type, size_t idx, const T &new_val) {
    // Has trivial constructor.
    array_[idx] = T();
  }

  void Destroy() {
    boost::has_trivial_destructor<T> type;
    Destroy(type);
  }

  void Destroy(boost::false_type) {
    // Has non-trivial destructor.
    for(size_t i = 0; i < size_; ++i) {
      array_[i].~T();
    }
  }

  void Destroy(boost::true_type) {
    // Has trivial destructor (do nothing).
  }
};

template<typename T>
Vector<T>::Vector(Memory &memory, size_t capacity)
    : memory_(memory), capacity_(capacity), size_(0) {
  array_ = static_cast<T *>(memory_.Allocate(capacity, sizeof(T)));
}

template<typename T>
void Vector<T>::PushBack(const T &t) {
  assert(size_ < capacity_);

  memset(&array_[size_], 0, sizeof(T));
  InitAt(size_, t);
  ++size_;
}

template<typename T>
Vector<T>::~Vector() {
  Destroy();
  memory_.Free(array_);
  array_ = 0;
}

template<typename T>
void Vector<T>::EraseAt(size_t idx) {
  assert(idx < size_);
  for (size_t i = idx; i < size_ - 1; ++i) {
    array_[i] = array_[i + 1];
  }

  array_[size_ - 1].~T();
  memset(&array_[size() - 1], 0, sizeof(T));
  --size_;
}

}

#endif //PIOUS_VECTOR_H
