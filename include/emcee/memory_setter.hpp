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

#ifndef PIOUS_MEMORY_SETTER_HPP
#define PIOUS_MEMORY_SETTER_HPP

#include <boost/type_traits/is_base_of.hpp>

namespace emcee {

class Memory;

/*! \brief Interface for a class that accepts a Memory pointer.
 *
 * Subclass as pure virtual.
 */
class MemorySetter {
 public:
  virtual ~MemorySetter() {}
  virtual void SetMemory(Memory *ptr) = 0;

  /* Injects memory into object if object derives from MemorySetter. */
  template<typename T> static void Inject(T &ref, Memory *memory) {
    boost::is_base_of<MemorySetter,T> can_inject;
    InjectMemory(can_inject, ref, memory);
  }

 private:

  template<typename T> static void InjectMemory(boost::true_type, T &ref, Memory *memory) {
    ref.SetMemory(memory);
  }

  template<typename T> static void InjectMemory(boost::false_type, T&, Memory*) {}
};

}

#endif /* PIOUS_MEMORY_SETTER_HPP */
