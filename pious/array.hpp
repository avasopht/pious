/*
 * Created by The Pious Authors on 12/09/2016.
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

#ifndef PIOUS_ARRAY_HPP
#define PIOUS_ARRAY_HPP

#include "os.hpp"
#include "os_setter.hpp"

#include <cstddef> // size_t
#include <cassert>

namespace pious {

class Os;

template<typename T, size_t N>
class Array {
 public:
  Array(Os &os) : size_(N) {
    InitArray(os);
  }

  const T& At(size_t idx) const { assert(idx < size_); return array_[idx]; }
  T& At(size_t idx) { assert(idx < size_); return array_[idx]; }

  const T& operator[](size_t idx) const { return array_[idx]; }
  T& operator[](size_t idx) { return array_[idx]; }

  size_t size() const { return size_; }

 private:
  size_t size_;
  T array_[N];

  void InitArray(Os &os) {
    for(size_t i = 0; i < N; ++i) {
      OsSetter::InjectOs(array_[i], &os);
    }
  }
};

}

#endif /*PIOUS_ARRAY_HPP*/
