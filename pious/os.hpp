/*
 * Created by keldon on 17/08/16.
 */

#ifndef PIOUS_OS_H
#define PIOUS_OS_H

#include <cstddef>
#include <cstdarg>
#include <cinttypes>
#include <cstdlib>
#include <cstdio>

namespace pious {

class OsMemory;

class Os {
 public:
  Os() : memory_(nullptr) {}
  Os(OsMemory &memory) : memory_(&memory) {}

  void SetMemory(OsMemory *memory) { memory_ = memory; }

  void* Malloc(size_t size);
  void* Calloc(size_t num, size_t size);
  void Free(void *ptr);

  int Log(const char *format, va_list arg);

  size_t GetArraySize(void *ptr) const {
    size_t size = *static_cast<size_t*>(ptr)-1;
    return size;
  }

 private:

  OsMemory *memory_;
};

}

#endif //PIOUS_OS_H
