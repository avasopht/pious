//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_VECTOR_H
#define PIOUS_VECTOR_H

#include "pious_allocator.h"
#include "os.hpp"

#include <cassert>
#include <cstddef> // size_t
#include <cstring>
#include <new>

namespace pious {

class Os;

template<typename T>
class Vector {
 public:
  Vector(Os &os, size_t capacity);
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
  Os &os_;
  size_t capacity_;
  size_t size_;
  T *array_;

  // No copy
  Vector(const Vector &rhs);
  Vector &operator=(const Vector &rhs);
};

template<typename T>
Vector<T>::Vector(Os &os, size_t capacity)
    : os_(os), capacity_(capacity), size_(0) {
  array_ = static_cast<T *>(os_.Calloc(capacity, sizeof(T)));
}

template<typename T>
void Vector<T>::PushBack(const T &t) {
  assert(size_ < capacity_);

  memset(&array_[size_], 0, sizeof(T));
  new (&array_[size_]) T(t);
  ++size_;
}

template<typename T>
Vector<T>::~Vector() {
  os_.Free(array_);
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
