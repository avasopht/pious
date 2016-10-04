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

#ifndef PIOUS_NEW_ALLOCATION_BLOCK_CALCULATION_HPP
#define PIOUS_NEW_ALLOCATION_BLOCK_CALCULATION_HPP


#include "new_allocation_block.hpp"
#include "destructor.hpp"
#include "util.hpp"

#include <cstddef>
#include <cassert>
#include <cstdint>

namespace emcee {


/*! \brief Provides calculations for new memory block allocations.
 *
 * New memory blocks are arranged:
 * - NewAllocationBlock
 * - T[N]
 * - Destructor
 *
 * \sa class pious::New
 */
template<typename T>
class NewAllocationBlockCalculationBase {
 public:
  NewAllocationBlockCalculationBase() : ptr_(nullptr) {}

  NewAllocationBlockCalculationBase& SetDataPointer(void *data_pointer) {
    assert(IsAligned(data_pointer));

    size_t data_address = reinterpret_cast<size_t>(data_pointer);
    size_t block_address = data_address - padded_block_size();

    ptr_ = reinterpret_cast<void*>(block_address);

    return *this;
  }

  NewAllocationBlockCalculationBase& SetBlockPointer(void *block_pointer) {
    assert(IsAligned(block_pointer));

    ptr_ = block_pointer;

    return *this;
  }

  static size_t CalcPaddedSize(size_t size) {
    return emcee::CalcPaddedSize(size);
  }

  void* allocation_pointer() { return ptr_; }

  void* memory_block_pointer() { return ptr_; }

  void* void_data_pointer() {
    return &static_cast<uint8_t*>(ptr_)[padded_block_size()];
  }

  Destructor* destructor_pointer() {
    size_t destructor_offset = padded_block_size() + padded_data_size();
    void *ptr = &static_cast<uint8_t*>(ptr_)[destructor_offset];
    return static_cast<Destructor*>(ptr);
  }

  static size_t padded_block_size() {
    return CalcPaddedSize(sizeof(NewAllocationBlock));
  }

  static size_t padded_data_size() {
    return CalcPaddedSize(sizeof(T));
  }

  static size_t padded_destructor_size() {
    return CalcPaddedSize(sizeof(TypedDestructor<T>));
  }

  static size_t allocation_size() {
    return padded_block_size() + padded_data_size() + padded_destructor_size();
  }

  size_t count() {
    return TypeCount<T>().count();
  }
 private:
  void *ptr_;
};

template<typename T>
class NewAllocationBlockCalculation : public NewAllocationBlockCalculationBase<T> {
 public:
  T *data_pointer() { return static_cast<T*>(NewAllocationBlockCalculationBase<T>::void_data_pointer()); }
};

template<typename T, size_t N>
class NewAllocationBlockCalculation <T[N]> : public NewAllocationBlockCalculationBase<T[N]> {
 public:
  T *data_pointer() { return static_cast<T*>(NewAllocationBlockCalculationBase<T[N]>::void_data_pointer()); }
};

}

#endif /* PIOUS_NEW_ALLOCATION_BLOCK_CALCULATION_HPP */
