/*
 * Created by keldon on 30/09/16.
 */

#include <cassert>
#include "util.hpp"

namespace pious {

size_t CalcPaddedSize(size_t size) {
  bool is_aligned = size % sizeof(size_t) == 0;
  if(is_aligned)
    return size;

  size_t padding = sizeof(size_t) - (size % sizeof(size_t));
  assert(padding > 0); // because it's not aligned.

  return size + padding;
}

bool IsAligned(void *ptr) {
  return reinterpret_cast<size_t>(ptr) % sizeof(size_t) == 0;
}

void *NextAligned(void *ptr) {
  size_t address = reinterpret_cast<size_t>(ptr);
  size_t aligned = CalcPaddedSize(address);
  return reinterpret_cast<void*>(aligned);
}

void *CalcOffset(void *ptr, ptrdiff_t offset) {
  return Offset<char>(ptr).Calc(offset);
}

}
