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

#include "var_rms.hpp"
#include <emcee/masked_cell_vector.hpp>

namespace pious {

void VarRms::Write(float sample) {
  assert(buffer_levels() > 0);
  ++pos_;
  float sample_sq = sample * sample;
  buffers_[0].At(pos_) = sample_sq;
  SumMeanSquaredToEndOfCell();
}

void VarRms::SumMeanSquaredToEndOfCell() {
  // Write to buffers where current position is at the end of the cell.
  for(size_t level = 1; level < buffer_levels() && buffers_[level].IsCellEnd(pos_); ++level) {
    BufferVector &cur_buffer = buffers_[level];
    BufferVector &prev_level_buffer = buffers_[level-1];
    size_t prev_level_cell_size = prev_level_buffer.cell_size();
    float first = prev_level_buffer[pos_];
    float second = prev_level_buffer[pos_ - prev_level_cell_size];
    cur_buffer[pos_] = first + second;
  }
}

float VarRms::CalcRms(int rms_size) { return CalcRmsAt(rms_size, 0); }

size_t VarRms::buffer_levels() const { return buffers_.size(); }

size_t VarRms::capacity() const {
  if(buffer_levels() == 0)
    return 0;
  return buffers_[0].size();
}

VarRms::VarRms(emcee::Memory *memory)
  : buffers_(memory),
    pos_(0U-1)
{ }

void VarRms::SetCapacity(size_t min_capacity) {
  buffers_.Clear();

  pos_ = size_t(0) - 1;
  size_t capacity = (size_t) ToPow2(min_capacity);
  int levels = Log2(capacity);
  buffers_.Resize((size_t)levels);

  for(int cur_level = 0; cur_level < levels; ++cur_level) {
    size_t cell_size = 1U << cur_level;
    BufferVector &cur_buffer = buffers_[cur_level];
    cur_buffer.SetSize(cell_size, capacity);
  }
}

float VarRms::CalcRmsAt(int s_rms_size, int s_offset) {
  assert(s_offset >= 0);
  assert(s_rms_size >= 0);

  size_t rms_size = (size_t) s_rms_size;
  size_t offset = (size_t) s_offset;

  size_t rms_read = 0;
  size_t cur_pos = pos_ - offset;

  float mean_squared = 0.f;

  while(rms_read < rms_size) {
    size_t rms_remaining = rms_size - rms_read;
    SearchCell cell = FindLargestCellEndingAt(cur_pos, rms_remaining);

    mean_squared += cell.value;
    rms_read += cell.cell_size;
    cur_pos -= cell.cell_size;
  }
  return (float) sqrt(mean_squared / rms_size);
}

VarRms::SearchCell VarRms::FindLargestCellEndingAt(size_t position, size_t max_size) {
  SearchCell largest_cell;

  largest_cell.value = 0.f;
  largest_cell.cell_size = 0;

  for(int level = 0; level < buffer_levels() && buffers_[level].cell_size() <= max_size; ++ level) {
    size_t cell_size = buffers_[level].cell_size();
    largest_cell.cell_size = cell_size;
    largest_cell.value = buffers_[level].At(position);
  }

  return largest_cell;
}

VarRms::VarRms()
  : buffers_(nullptr),
    pos_(0) { }



} // namespace