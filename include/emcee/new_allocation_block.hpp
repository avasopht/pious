/*
 * Created by The Pious Authors on 29/09/2016.
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

#ifndef PIOUS_NEW_ALLOCATION_BLOCK_HPP
#define PIOUS_NEW_ALLOCATION_BLOCK_HPP

#include <cstddef>
#include <new>
#include <cassert>
#include <cstdio>

namespace emcee {

class Destructor;
class Memory;

class NewAllocationBlock {
 public:

  static NewAllocationBlock* CreateDefault(
      Memory &memory, void *ptr, void *data, Destructor *destructor,
      size_t count, size_t allocation_size) {


    assert(&memory);

    NewAllocationBlock *block =
        new(ptr)NewAllocationBlock(memory, data, destructor, count, allocation_size);

    return block;
  }

  static NewAllocationBlock* FromDataPointer(void *data);

  Destructor* destructor() { return destructor_; }
  void* data() { return data_; }
  Memory* memory() { return &memory_; }
  size_t count() const { return count_; }
  size_t allocation_size() const { return allocation_size_; }

 private:
  Memory &memory_;
  void *data_;
  Destructor *destructor_;
  size_t count_;
  size_t allocation_size_;


  NewAllocationBlock(Memory &memory, void *data, Destructor *destructor,
                     size_t count, size_t allocation_size);
  NewAllocationBlock(const NewAllocationBlock &) = delete;
};

}

#endif /* PIOUS_NEW_ALLOCATION_HPP */
