/*
 * Created by keldon on 29/09/16.
 */

#ifndef PIOUS_NEW_HPP
#define PIOUS_NEW_HPP

#include "destructor.hpp"
#include "new_allocation_block.hpp"
#include "new_allocation_block_calculation.hpp"
#include "memory_dependent.hpp"
#include "memory.hpp"

#include <cstddef>
#include <cassert>
#include <boost/type_traits/is_base_of.hpp>

namespace pious {


class Memory;

size_t ArraySize(void *ptr);
void Delete(void *ptr);

template<typename T>
class New {
 public:
  New(Memory &memory) : memory_(memory) {}

  T* Create() {
    return New<T[1]>(memory_).Create();
  }

  T* Create(const T &other) {
    return New<T[1]>(memory_).Create(other);
  }


 private:
  Memory &memory_;
};

template<typename T, size_t N>
class New<T[N]> {
 public:
  typedef T ArrayType[N];
  typedef TypedDestructor<ArrayType> DestructorType;

  New(Memory &memory) : memory_(memory) {};

  T* Create() {
    NewAllocationBlock *block = Allocate();
    T *ptr = static_cast<T*>(block->data());

    for(size_t i = 0; i < N; ++i) {
      Construct(&ptr[i]);
    }

    return ptr;
  }

  T* Create(const T&other) {
    NewAllocationBlock *block = Allocate();
    T *ptr = static_cast<T*>(block->data());

    for(size_t i = 0; i < N; ++i) {
      Construct(&ptr[i], other);
    }

    return ptr;
  }

  size_t count() const { return N; }

 private:
  Memory &memory_;

  void Construct(void *ptr) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    Construct(ptr, is_memory_dependent);
  }

  void Construct(void *ptr, const T &other) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    Construct(ptr, other, is_memory_dependent);
  }

  void Construct(void *ptr, boost::true_type) {
    new(ptr)T(memory_);
  }

  void Construct(void *ptr, boost::false_type) {
    new(ptr)T();
  }

  void Construct(void *ptr, const T &other, boost::true_type) {
    new(ptr)T(memory_, other);
  }

  void Construct(void *ptr, const T &other, boost::false_type) {
    new(ptr)T(other);
  }

  NewAllocationBlock* Allocate() {
    NewAllocationBlockCalculation<ArrayType> allocation;
    size_t allocation_size = allocation.allocation_size();

    void *ptr = memory_.Allocate(allocation_size);
    allocation.SetBlockPointer(ptr);
    Destructor *destructor_ptr = allocation.destructor_pointer();
    T *data = allocation.data_pointer();
    size_t count = allocation.count();
    Destructor *destructor = new(destructor_ptr)DestructorType();

    NewAllocationBlock *block = NewAllocationBlock::CreateDefault(
        memory_, ptr, data, destructor, count, allocation_size
    );

    return block;
  }
};

}

#endif /* PIOUS_NEW_HPP */
