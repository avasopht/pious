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

#include "emcee/memory.hpp"
#include "emcee/memory_setter.hpp"
#include "emcee/memory_dependent.hpp"

#include <cstddef> // size_t
#include <cassert>
#include <cstdint>

namespace emcee {

template<typename T, size_t N>
class Array {
 public:
  explicit Array(Memory & memory) : size_(N) {
    InitArray(memory);
  }

  const T & At(size_t idx) const {
    assert(idx < size_);
    return array()[idx];
  }

  T & At(size_t idx) {
    assert(idx < size_);
    return array()[idx];
  }

  const T & operator[](size_t idx) const { return array()[idx]; }

  T & operator[](size_t idx) { return array()[idx]; }

  size_t size() const { return size_; }

 private:
  size_t size_;
  uint8_t data_[sizeof(T[N])];

  const T * array() const { return reinterpret_cast<const T *>(data_); }

  T * array() { return reinterpret_cast<T *>(data_); }

  void Construct(Memory & memory, T & obj) {
    boost::is_base_of<MemoryDependent, T> is_memory_dependent;
    Construct(memory, obj, is_memory_dependent);
  }

  void Construct(Memory & memory, T & obj, boost::true_type) {
    new(&obj)T(memory);
  }

  void Construct(Memory & memory, T & obj, boost::false_type) {
    new(&obj)T();
  }

  void InitArray(Memory & memory) {
    for (size_t i = 0; i < N; ++i) {
      Construct(memory, operator[](i));
      MemorySetter::Inject(&operator[](i), &memory);
    }
  }
};

}

#endif /*PIOUS_ARRAY_HPP*/
