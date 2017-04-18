/*
 * Created by The Pious Authors on 19/10/16.
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

#ifndef PIOUS_WEAK_COUNT_HPP_H
#define PIOUS_WEAK_COUNT_HPP_H

#include <cstddef>

namespace emcee {

class ReferenceCounter;

class SharedCount;

class WeakCount {
 public:
  WeakCount();
  WeakCount(const WeakCount & rhs);
  WeakCount(const SharedCount & shared_count);

  ~WeakCount();

  WeakCount & operator=(const WeakCount & rhs);
  WeakCount & operator=(const SharedCount & shared_count);

  size_t use_count() const;
  ReferenceCounter * counter() const;

  void ImportCounter(const SharedCount & count);
  void ImportCounter(const WeakCount & count);

 private:
  ReferenceCounter * counter_;

  void Release();
  void AddUse();
};

}

#endif //PIOUS_WEAK_COUNT_HPP_H
