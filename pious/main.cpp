#include "pious_allocator.h"
#include "scoped_ptr.hpp"
#include "vector.hpp"
#include "os.hpp"

#include <cstdlib>
#include <cstdio>

void *DefaultMalloc(void *data, size_t size) {
  (void) data;
  return malloc(size);
}

void *DefaultCalloc(void *data, size_t count, size_t size) {
  (void) data;
  return calloc(count, size);
}

void DefaultFree(void *data, void *ptr) {
  (void) data;
  free(ptr);
}

class DefaultOs : public pious::Os {
 public:
  virtual void *Malloc(size_t size) override {
    return malloc(size);
  }
  virtual void *Calloc(size_t num, size_t size) override {
    return calloc(num, size);
  }
  virtual void Free(void *ptr) override {
    free(ptr);
  }
  virtual int Log(const char *format, va_list arg) override {
    return 0;
  }
};

template<typename T>
T* New(pious::Os &os, const T& t) {
  T *ptr = static_cast<T*>(os.Malloc(sizeof(T)));
  *ptr = t;
  return ptr;
}

int main() {
  typedef pious::ScopedPtr<int> IntPtr;
  DefaultOs os;
  os.Free(os.Malloc(10));

  pious::Vector<IntPtr> ivec(os, 10);
  ivec.PushBack(IntPtr(os, os.New(10)));
  ivec.PushBack(IntPtr(os, os.New(7)));
  ivec.PushBack(IntPtr(os, os.New(11)));
  ivec.EraseAt(1);
  assert((*ivec[1]) == 11);

  return 0;
}