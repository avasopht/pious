/*
 * Created by The Pious Authors on 30/09/2016.
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef PIOUS_UTIL_HPP
#define PIOUS_UTIL_HPP

#include <cstddef>
#include <cstdint>
namespace emcee {

/*! Returns an object size that is aligned with memory. */
size_t CalcPaddedSize(size_t size);

/*! Returns whether pointer is memory aligned. */
bool IsAligned(void *ptr);

/*! Returns the next aligned pointer */
void* NextAligned(void *ptr);

//! \sa class Offset
void* CalcOffset(void *ptr, ptrdiff_t offset);

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
