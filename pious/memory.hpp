/*
 * Created by The Pious Authors on 26/09/2016.
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

#ifndef PIOUS_MEMORY_HPP
#define PIOUS_MEMORY_HPP

#include <cstddef> // size_t

namespace pious {

class Memory {
 public:
  virtual ~Memory() {}

  /*! \brief Sets pointer to data used in a unique way by the implementation.
   *    \sa Data()
   *
   *  Implementations do not have to accept the pointer.
   */
  virtual void SetData(void *ptr) = 0;
  /*! \brief Returns pointer to data object associated with memory instance.
   *
   *    Use `data` to point to a singleton object to manage an application.
   */
  virtual void* Data() = 0;
  virtual void* Malloc(size_t size) = 0;
  virtual void* Calloc(size_t num, size_t size) = 0;
  virtual void Free(void *ptr) = 0;
};

class DefaultMemory : public Memory {
 public:
  DefaultMemory() : data_(nullptr){}

  virtual void SetData(void *ptr) override;
  virtual void* Data() override;
  virtual void *Malloc(size_t size) override;
  virtual void *Calloc(size_t num, size_t size) override;
  virtual void Free(void *ptr) override;
 private:
  void *data_;
};

}

#endif /*PIOUS_MEMORY_HPP*/
