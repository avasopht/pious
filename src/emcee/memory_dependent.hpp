/*
 * Created by The Pious Authors on 28/09/2016.
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

#ifndef PIOUS_MEMORY_DEPENDENT_HPP
#define PIOUS_MEMORY_DEPENDENT_HPP

#include <boost/type_traits.hpp>
#include "platform.hpp"

namespace emcee {
class Platform;

/*! \brief  Indicates at compile time that a class accepts a Memory pointer
 *  in construction.
 *
 *  Subclasses should implement `Subclass(Memory*)`.
 *
 *  Subclass with public virtual inheritance.
 */
class MemoryDependent {
 public:
  virtual ~MemoryDependent() = 0;

  /*! Calls constructor. Returns whether memory was injected. */
  template<typename T>
  static bool ConstructAt(T * t, Platform * memory) {
    boost::is_base_of<MemoryDependent, T> is_memory_dependent;
    ConstructAtWithMemory(is_memory_dependent, t, memory);
    bool memory_was_injected = is_memory_dependent;
    return memory_was_injected;
  }

  template<typename T>
  static void ConstructAtWithMemory(boost::true_type, T * t, Platform * memory) {
    new(t)T(memory);
  }

  template<typename T>
  static void ConstructAtMemory(boost::false_type, T * t, Platform *) {
    new(t)T();
  }
};

/*! \brief  Indicates at compile time that a class accepts a Memory pointer
 *  in construction and also supports a copy constructor with a Memory pointer.
 *
 *  Subclasses must implement `Subclass(Memory&)` and
 *  `Subclass(Memory*, const Subclass&)` for a copy constructor that injects
 *  a Memory pointer.
 *
 *  Subclass with public virtual inheritance.
 */
class MemoryDependentWithCopy : public virtual MemoryDependent {
 public:

  /*! Calls constructor passing constructor object. Returns whether memory was
   * injected. */
  template<typename T, typename Y>
  static bool ConstructAt(
      T * t, Platform * memory, const Y & other) {
    boost::is_base_of<MemoryDependentWithCopy, T> is_memory_dependent_with_copy;
    ConstructAtWithMemoryAndCopy(
        is_memory_dependent_with_copy, t, memory, other);
    bool memory_was_injected = is_memory_dependent_with_copy;
    return memory_was_injected;
  }

  template<typename T, typename Y>
  static void ConstructAtWithMemoryAndCopy(
      boost::true_type, T * t, Platform * memory, const Y & other) {
    new(t)T(memory, other);
  }

  template<typename T, typename Y>
  static void ConstructAtWithMemoryAndCopy(
      boost::false_type, T * t, Platform *, const Y & other) {
    new(t)T(other);
  }

};

} /* namespace emcee */

#endif /* PIOUS_MEMORY_DEPENDENT_HPP */
