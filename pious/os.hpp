/*
 * Created by keldon on 17/08/16.
 */

#ifndef PIOUS_OS_H
#define PIOUS_OS_H

#include <cstddef>
#include <cstdarg>

namespace pious {

class Os {
 public:
  virtual ~Os(){}

  template<typename T> T* New(const T& t) {
    return new(Malloc(sizeof(t))) T(t);
  }

  virtual void* Malloc(size_t size) = 0;
  virtual void* Calloc(size_t num, size_t size) = 0;
  virtual void Free(void *ptr) = 0;
  virtual int Log(const char *format, va_list arg) = 0;
};

}

#endif //PIOUS_OS_H
