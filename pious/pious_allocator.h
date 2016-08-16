//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_PIOUS_ALLOCATOR_H
#define PIOUS_PIOUS_ALLOCATOR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*Pious_Malloc)(void *private_data, size_t size);
typedef void *(*Pious_Calloc)(void *private_data, size_t count, size_t size);
typedef void (*Pious_Free)(void *private_data, void *ptr);

struct Pious_Allocator {
  Pious_Malloc Malloc;
  Pious_Calloc Calloc;
  Pious_Free Free;
  void *data;
};

#ifdef __cplusplus
}
#endif

#endif //PIOUS_PIOUS_ALLOCATOR_H
