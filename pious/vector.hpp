//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_VECTOR_H
#define PIOUS_VECTOR_H

#include "pious_allocator.h"

#include <cassert>
#include <cstddef> // size_t

namespace pious {

template<typename T>
class Vector {
 public:
  Vector(struct Pious_Allocator &allocator, size_t capacity);
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
  struct Pious_Allocator *alloc_;
  size_t capacity_;
  size_t size_;
  T *array_;

  // No copy
  Vector(const Vector &rhs);
  Vector &operator=(const Vector &rhs);
};

template<typename T>
Vector<T>::Vector(struct Pious_Allocator &allocator, size_t capacity)
    : alloc_(&allocator), capacity_(capacity), size_(0) {
  assert(alloc_);
  array_ = static_cast<T *>(alloc_->Calloc(alloc_->data, capacity, sizeof(T)));
}

template<typename T>
void Vector<T>::PushBack(const T &t) {
  assert(size_ < capacity_);
  array_[size_] = t;
  ++size_;
}

template<typename T>
Vector<T>::~Vector() {
  alloc_->Free(alloc_->data, array_);
  array_ = 0;
}

template<typename T>
void Vector<T>::EraseAt(size_t idx) {
  assert(idx < size_);
  for (size_t i = idx; i < size_ - 1; ++i) {
    array_[i] = array_[i + 1];
  }

  array_[size_ - 1] = {0};
  --size_;
}

}

#endif //PIOUS_VECTOR_H
