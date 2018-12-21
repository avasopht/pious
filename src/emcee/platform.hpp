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
#include <api/pious_sys.h>

namespace emcee {

Pious_Mem PiousMem_CreateDefault();

class Library;
class String;
class Literal;

class Platform {
 public:
  virtual ~Platform() = default;

  virtual void *Allocate(size_t size) = 0;
  virtual void Free(void *ptr) = 0;
  virtual Library *LoadLibrary(const String &library_name) = 0;
  virtual Library *LoadLibrary(const Literal &library_name) = 0;
};

class DefaultPlatform : public Platform {
 public:
  void *Allocate(size_t size) override;
  void Free(void *ptr) override;
  Library *LoadLibrary(const Literal &library_name) override;
  Library *LoadLibrary(const String &library_name) override;
};

class StructPlatform : public Platform {
 public:
  Library *LoadLibrary(const String &library_name) override;
  Library *LoadLibrary(const Literal &library_name) override;
  explicit StructPlatform(Pious_Mem *mem) : mem_(*mem) {}

  void SetMemory(Pious_Mem *mem) { mem_ = *mem; }

  void *Allocate(size_t size) override;
  void Free(void *ptr) override;

  Pious_Mem *mem_struct() { return &mem_; }

 private:
  Pious_Mem mem_;
};

}

#endif /*PIOUS_MEMORY_HPP*/