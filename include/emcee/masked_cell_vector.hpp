/*
 * Created by The Pious Authors on 31/12/2016.
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

#ifndef PIOUS_MASKED_CELL_VECTOR_HPP
#define PIOUS_MASKED_CELL_VECTOR_HPP

#include "vector.hpp"
#include "pow2.hpp"
#include "memory_setter.hpp"
#include "memory_dependent.hpp"

namespace emcee {

class Memory;

/*! A "cell vector" with a power of 2 size.
 *
 *  A cell vector is divided into cells that share the same value. For example
 *  you may have a vector that references 8 elements, but is really made of
 *  4 cell vectors.
 *
 *  In this scenario elements 0 and 1 share the same value.
 *
 *  The masking allows you to reference elements with an index greater than
 *  its size (which will be wrapped around). So with an 8 element vector,
 *  element 0 can be accessed by referencing element 8. This comes in handy
 *  when you want to create circular buffers.
 */
template<typename T>
class MaskedCellVector : public virtual MemorySetter, public virtual MemoryDependentWithCopy {
 public:
  MaskedCellVector() :
      vector_(nullptr),
      idx_mask_(0),
      cell_size_(0),
      cell_mask_(0),
      cell_shift_(0) {}

  MaskedCellVector(Memory * memory) :
      vector_(memory),
      idx_mask_(0),
      cell_size_(0),
      cell_mask_(0),
      cell_shift_(0) {}

  MaskedCellVector(Memory * memory, const MaskedCellVector & rhs) :
      vector_(rhs.vector_),
      idx_mask_(rhs.idx_mask_),
      cell_size_(rhs.cell_size_),
      cell_mask_(rhs.cell_mask_),
      cell_shift_(rhs.cell_shift_) {
    vector_.SetMemory(memory);
  }

  void SetMemory(Memory * ptr) override {
    vector_.SetMemory(ptr);
  }

  /*!
   * @param cell_size   size of cells (must be a power of 2).
   * @param size        size of the vector (must be a power of 2).
   */
  void SetSize(size_t cell_size, size_t size) {

    assert(IsPow2(cell_size));
    assert(IsPow2(size));
    assert(cell_shift_ >= 0);

    idx_mask_ = size / cell_size - 1;
    cell_size_ = cell_size;
    cell_mask_ = cell_size - 1;
    cell_shift_ = Log2(cell_size);

    size_t vector_size = size / cell_size;
    vector_.Resize(vector_size);
  }

  /*! Returns whether the index is at the start of a cell. */
  bool IsCellStart(size_t idx) const {
    bool is_cell_start = (cell_mask_ & idx) == 0;
    return is_cell_start;
  }

  /*! Returns whether the index is at the end of a cell. */
  bool IsCellEnd(size_t idx) const {
    return IsCellStart(idx + 1);
  }

  const T & At(size_t idx) const {
    return vector_[CalcIndex(idx)];
  }

  T & At(size_t idx) {
    return vector_[CalcIndex(idx)];
  }

  void Clear() {
    for (size_t i = 0; i < vector_.size(); ++i) {
      vector_[i] = T();
    }
  }

  const T & operator[](size_t idx) const { return At(idx); }

  T & operator[](size_t idx) { return At(idx); }

  size_t cell_size() const { return cell_size_; }

  size_t size() const { return vector_.size() * cell_size_; }

 private:
  Vector <T> vector_;
  size_t idx_mask_;
  size_t cell_size_;
  size_t cell_mask_;
  int cell_shift_;

  size_t CalcIndex(size_t idx) const { return (idx >> cell_shift_) & idx_mask_; }
};

}

#endif /* PIOUS_MASKED_CELL_VECTOR_HPP */
