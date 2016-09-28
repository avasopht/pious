/*
 * Created by keldon on 28/09/16.
 */

#include "object.hpp"

#include <new>

namespace pious {

ArrayAllocation *ArrayAllocation::InitFromPtr(void *vptr,
                                                          size_t size) {
  (void)std::nothrow_t(); // Eliminate clion unused <new> warning.
  ArrayAllocation *allocation = new(vptr)ArrayAllocation(size);
  return allocation;
}

ArrayAllocation *ArrayAllocation::FindFromArrayPtr(void *array) {
  void *allocation_ptr =
      &static_cast<uint8_t*>(array)[-sizeof(ArrayAllocation)];
  ArrayAllocation *allocation =
      static_cast<ArrayAllocation*>(allocation_ptr);
  if(allocation->array != array)
    return nullptr;
  return allocation;
}
ArrayAllocation::ArrayAllocation(size_t size)
  : size(size)
{
  void *ptr = static_cast<void*>(this);
  void *array_ptr = &static_cast<uint8_t*>(ptr)[sizeof(ArrayAllocation)];
  this->array = array_ptr;
}

}

#pragma clang diagnostic pop