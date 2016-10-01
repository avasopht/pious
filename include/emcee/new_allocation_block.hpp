/*
 * Created by keldon on 29/09/16.
 */

#ifndef PIOUS_NEW_ALLOCATION_BLOCK_HPP
#define PIOUS_NEW_ALLOCATION_BLOCK_HPP

#include <cstddef>
#include <new>
#include <cassert>
#include <cstdio>

namespace emcee {

class Destructor;
class Memory;

class NewAllocationBlock {
 public:

  static NewAllocationBlock* CreateDefault(
      Memory &memory, void *ptr, void *data, Destructor *destructor,
      size_t count, size_t allocation_size) {


    assert(&memory);

    NewAllocationBlock *block =
        new(ptr)NewAllocationBlock(memory, data, destructor, count, allocation_size);

    return block;
  }

  static NewAllocationBlock* FromDataPointer(void *data);

  Destructor* destructor() { return destructor_; }
  void* data() { return data_; }
  Memory* memory() { return &memory_; }
  size_t count() const { return count_; }
  size_t allocation_size() const { return allocation_size_; }

 private:
  Memory &memory_;
  void *data_;
  Destructor *destructor_;
  size_t count_;
  size_t allocation_size_;


  NewAllocationBlock(Memory &memory, void *data, Destructor *destructor,
                     size_t count, size_t allocation_size);
  NewAllocationBlock(const NewAllocationBlock &) = delete;
};

}

#endif /* PIOUS_NEW_ALLOCATION_HPP */
