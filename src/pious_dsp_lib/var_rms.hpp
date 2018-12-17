/*
 * Created by The Pious Authors on 02/01/2017.
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

#ifndef PIOUS_VAR_RMS_HPP
#define PIOUS_VAR_RMS_HPP

#include <cstdlib>

#include <emcee/vector.hpp>
#include <emcee/memory_dependent.hpp>
#include <emcee/masked_cell_vector.hpp>

namespace emcee {
class Memory;
template<typename T> class MaskedCellVector;
}

namespace pious {

/*! Allows you to calculate the Rms for an arbitrary length at O(log N), where N is the maximum Rms size.
 */
class VarRms : public virtual emcee::MemoryDependent {
 public:
  VarRms();
  explicit VarRms(emcee::Memory *memory);

  float CalcRms(int rms_size);
  float CalcRmsAt(int rms_size, int offset);

  void Write(float sample);

  void SetCapacity(size_t min_capacity);
  void Clear();

  size_t capacity() const;

 private:

  struct SearchCell {
    float value;
    size_t cell_size;
  };

  /* sample[i-1] is the previous sample to sample[i].
   */
  emcee::Vector<emcee::MaskedCellVector<float> > buffers_;
  size_t pos_;


  size_t buffer_levels() const;

  void CalcSumMeanSquaredAndWriteToEndOfCell();
  SearchCell FindLargestCellEndingAt(size_t position, size_t max_size);
};

}

#endif /* PIOUS_VAR_RMS_HPP */
