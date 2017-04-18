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

/*! \brief ReferenceCounter manages the lifetime of a shared resource.
 *
 * ReferenceCounter tracks two types of references - shared and weak. The
 * resource is deleted when all shared references have been released. The
 * ReferenceCounter instance can be deleted when there are no shared or
 * weak references (`is_unused()` will return true in this case).
 */
class ReferenceCounter {
 public:
  ReferenceCounter();

  /*! Constructs a instance with a use count of 1. */
  ReferenceCounter(Deleter * deleter);

  /*! Increments use count. */
  void AddUse();

  /*! Increments weak use count. */
  void WeakAddUse();

  /*! Releases a reference. The deleter will be invokved when use count is 0. */
  void Release();
  void WeakRelease();

  /*! \brief  Assigns deleter instance with a use count of 1.
   *
   * Calling this will invoke the deleter before assigning the new deleter.
   */
  void SetDeleter(Deleter * deleter);

  ReferenceCounter & WithDeleter(Deleter * deleter) {
    SetDeleter(deleter);
    return *this;
  }

  /*! Invokes deleter. */
  void Dispose();

  /*! Returns shared use count. */
  size_t use_count() const { return shared_count_; }

  /*! Returns whether this reference counter has any shared or weak references. */
  bool is_referenced() const { return weak_count_ > 0; }

 private:
  Deleter * deleter_;
  size_t shared_count_;
  size_t weak_count_; // weak_count + (shared_count_ != 0)

  ReferenceCounter(const ReferenceCounter &) = delete;
  ReferenceCounter & operator=(const ReferenceCounter &) = delete;
};

}

#endif /* PIOUS_REFERENCE_COUNTER_HPP */
