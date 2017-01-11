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

#include "util.hpp"
#include <cassert>
#include <cmath>

namespace emcee {

size_t CalcPaddedSize(size_t size) {
  bool is_aligned = size % sizeof(size_t) == 0;
  if(is_aligned)
    return size;

  size_t padding = sizeof(size_t) - (size % sizeof(size_t));
  assert(padding > 0); // because it's not aligned.

  return size + padding;
}

bool IsAligned(void *ptr) {
  return reinterpret_cast<size_t>(ptr) % sizeof(size_t) == 0;
}

void *NextAligned(void *ptr) {
  size_t address = reinterpret_cast<size_t>(ptr);
  size_t aligned = CalcPaddedSize(address);
  return reinterpret_cast<void*>(aligned);
}

void *CalcOffset(void *ptr, ptrdiff_t offset) {
  return Offset<char>(ptr).Calc(offset);
}

bool NearEq(float first, float second, float error) {
  return fabs(first-second) <= error;
}

}
