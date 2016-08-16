#include "pious_allocator.h"

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

int main() {
  printf("done\n");
  return 0;
}