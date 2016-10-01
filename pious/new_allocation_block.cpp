/*
 * Created by keldon on 30/09/16.
 */

#include "pious/new_allocation_block.hpp"
#include "pious/util.hpp"
#include "pious/new_allocation_block_calculation.hpp"
#include "pious/memory.hpp"

#include <new>

namespace pious {



NewAllocationBlock *NewAllocationBlock::FromDataPointer(void *data) {
  NewAllocationBlockCalculation<char> calculation;
  size_t offset = calculation.padded_block_size();
  NewAllocationBlock *block = Offset<NewAllocationBlock>(data).Calc(-offset);


  if(block->data() != data) {
    // If
    return nullptr;
  }


  return block;
}

NewAllocationBlock::NewAllocationBlock(Memory &memory,
                                       void *data,
                                       Destructor *destructor,
                                       size_t count,
                                       size_t allocation_size)
  : memory_(memory),
    data_(data),
    destructor_(destructor),
    count_(count),
    allocation_size_(allocation_size)
{ }

}