/*
 * Created by The Pious Authors on 14/04/2017.
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
#include <pious/signal_channel.hpp>
#include <algorithm>

namespace pious {

SignalChannel::SignalChannel(emcee::Memory * memory, size_t size)
  : buffer_(memory)
{
  assert(size >= 0);
  if(size > 0)
    buffer_.Resize((size_t) size);
}

size_t SignalChannel::ReadSignal(float * dest, size_t max_samples) const {
  for(size_t i = 0; i < max_samples && i < buffer_.size(); ++i) {
    dest[i] = buffer_[i];
  }
  return std::min(buffer_.size(), max_samples);
}

size_t SignalChannel::WriteSignal(const float * signal, size_t frame_count) {
  for(size_t i = 0; i < frame_count && i < buffer_.size(); ++i)
    buffer_[i] = signal[i];
  return std::min(buffer_.size(), frame_count);
}

} // pious
