/*
 * Created by keldon on 30/09/16.
 */

#include "emcee/new.hpp"
#include "emcee/memory.hpp"

namespace emcee {


void Delete(void *ptr) {
  NewAllocationBlock *block = NewAllocationBlock::FromDataPointer(ptr);
  if(block) {
    Memory * mem = block->memory();
    assert(mem);
    block->destructor()->Destroy();
    mem->Free(block);
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