/*
 * Created by keldon on 30/09/16.
 */

#ifndef PIOUS_UTIL_HPP
#define PIOUS_UTIL_HPP

#include <cstddef>
#include <cstdint>
namespace emcee {

size_t CalcPaddedSize(size_t size);
bool IsAligned(void *ptr);

void* NextAligned(void *ptr);

//! \sa class Offset
void* CalcOffset(void *ptr, ptrdiff_t offset);


/*! \brief Gets the element count of a typename. */
template<typename T> class TypeCount {
  /*! Returns 1 for types that are not arrays. */
  public: size_t count() { return 1; }
};

template<typename T, size_t N> class TypeCount <T[N]> {
  public: size_t count() { return N; }
};

/*! \brief Returns a type T pointer to an address at an offset from a pointer
 *
 * Using this class can make it cleaner to
 */
template<typename T>
class Offset {
 public:
  Offset(void *ptr) : ptr_(ptr) {}

  const T* Calc(ptrdiff_t offset) const {
    return reinterpret_cast<T*>(&reinterpret_cast<uint8_t*>(ptr_)[offset]);
  }

  T* Calc(ptrdiff_t offset) {
    return const_cast<T*>(static_cast<const Offset<T>*>(this)->Calc(offset));
  }

 private:
  void *ptr_;
};

}

#endif /* PIOUS_UTIL_HPP */
