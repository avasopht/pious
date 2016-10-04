/*
 * Created by The Pious Authors on 04/10/16.
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

#ifndef PIOUS_REFERENCE_COUNTER_HPP
#define PIOUS_REFERENCE_COUNTER_HPP

#include <cstddef>
namespace emcee {

class Deleter;

class ReferenceCounter {
 public:
  ReferenceCounter();

  /*! Constructs a instance with a use count of 1. */
  ReferenceCounter(Deleter *deleter);

  void AddUse();
  void Release();

  /*! Assigns deleter instance with a use count of 1. */
  void SetDeleter(Deleter *deleter);

  void Dispose();

  size_t use_count() const { return count_ ; }

 private:
  Deleter *deleter_;
  size_t count_;

  ReferenceCounter(const ReferenceCounter &) = delete;
  ReferenceCounter& operator=(const ReferenceCounter &) = delete;
};

}

#endif /* PIOUS_REFERENCE_COUNTER_HPP */
