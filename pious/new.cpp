/*
 * Created by keldon on 30/09/16.
 */

#include "new.hpp"
#include "memory.hpp"

namespace pious {


void Delete(void *ptr) {
  NewAllocationBlock *block = NewAllocationBlock::FromDataPointer(ptr);
  if(block) {
    block->destructor()->Destroy();
    block->memory()->Free(block);
  }
}
size_t ArraySize(void *ptr) {
  NewAllocationBlock *block = NewAllocationBlock::FromDataPointer(ptr);
  if(block) {
    return block->count();
  }

  return 0;
}

}