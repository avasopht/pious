/*
 * Created by The Pious Authors on 30/09/2016.
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

#include "emcee/new_allocation_block.hpp"
#include "emcee/util.hpp"
#include "emcee/new_allocation_block_calculation.hpp"
#include "emcee/memory.hpp"

#include <new>

namespace emcee {



NewAllocationBlock *NewAllocationBlock::FromDataPointer(void *data) {
  NewAllocationBlockCalculation<char> calculation;
  size_t offset = calculation.padded_block_size();
  NewAllocationBlock *block = Offset<NewAllocationBlock>(data).Calc(-offset);


  if(block->data() != data) {
    // If
    return nullptr;
  }


  return block;
}

NewAllocationBlock::NewAllocationBlock(Memory &memory,
                                       void *data,
                                       Destructor *destructor,
                                       size_t count,
                                       size_t allocation_size)
  : memory_(memory),
    data_(data),
    destructor_(destructor),
    count_(count),
    allocation_size_(allocation_size)
{ }

}