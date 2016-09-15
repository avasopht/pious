/*
 * Created by keldon on 17/08/16.
 */

#ifndef PIOUS_OS_H
#define PIOUS_OS_H

#include <boost/type_traits/is_base_of.hpp>

#include <cstddef>
#include <cstdarg>
#include <cinttypes>
#include <cstdlib>
#include <cstdio>

namespace pious {

class Os {
 public:

  virtual ~Os(){}

  /*! Copy constructs new object of type T.
   *
   * The class must be able to be constructed with `T(Os&, const T&)`.
   *
   * @param t
   * @return
   */
  template<typename T> T* NewObject(const T& t) {
    void *ptr = Calloc(1, sizeof(t));
    return new (ptr) T(*this, t);
  }

  /*! @brief Creates a new object of type T.
   *
   * The class type must be able to be constructed with `Os &` as a parameter.
   *
   * @param t can be a null pointer as it is only used to capture the type.
   */
  template<typename T> T* NewDefaultObject(const T *t) {
    void *ptr = Calloc(1, sizeof(*t));
    return new (ptr) T(*this);
  }

  template<typename T> T* NewObjectArray(size_t count, const T& init_value) {
    void *ptr = AllocateArray(count, sizeof(T));

    size_t *count_ptr = static_cast<size_t*>(ptr);
    *count_ptr = count;
  }

  template<typename T> T* NewDefault(const T* t) {
    if(!t) {
      return new(Calloc(1, sizeof(*t))) T();
    }
  }

  template<typename T> T* New(const T& t) {
    return new(Calloc(1, sizeof(t))) T(t);
  }

  template<typename T> T* NewArray(size_t count) {
    void *ptr = AllocateArray(count, sizeof(T));

    size_t *count_ptr = static_cast<size_t*>(ptr);
    *count_ptr = count;

    T *array = static_cast<T*>(count_ptr + 1);

    for(size_t i = 0; i < count; ++i) {
      array[i].T();
    }
    return array;
  }

  template<typename T>
  void Delete(T *ptr) {
    typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
    (void) sizeof(type_must_be_complete);
    ptr->~T();
    Free(ptr);
  }

  template<typename T>
  void DeleteArray(T *array_ptr) {
    typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
    (void) sizeof(type_must_be_complete);

    void *ptr = static_cast<size_t*>(array_ptr) - 1;

    size_t count = GetArraySize(array_ptr);
    for(size_t i = 0; i < count; ++i) {
      array_ptr[i].~T();
    }

    Free(ptr);
  }

  virtual void* Malloc(size_t size) = 0;
  virtual void* Calloc(size_t num, size_t size) = 0;
  virtual void Free(void *ptr) = 0;
  virtual int Log(const char *format, va_list arg) = 0;

  size_t GetArraySize(void *ptr) const {
    size_t size = *static_cast<size_t*>(ptr)-1;
    return size;
  }

  template<typename T> T* GetStatic(const struct pious_handle *handle) { return nullptr; };
  void GetStaticHandle(struct pious_handle *handle, const char *handle_sid) {}
 private:

  void* AllocateArray(size_t count, size_t size) {
    size_t full_size = count * size + 1;
    void *ptr = Calloc(1, full_size);

    size_t *size_ptr = static_cast<size_t*>(ptr);
    *size_ptr = count;

    void *array_ptr= size_ptr + 1;

    return array_ptr;
  }
};

class DefaultOs : public Os {
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
    vprintf(format, arg);
  }
};

}

#endif //PIOUS_OS_H
