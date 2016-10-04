/*
 * Created by The Pious Authors on 01/10/2016.
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

/*
 * The testing here is fairly minimal since most logic is really contained in
 * NewMemoryBlockCalculation<T>::SetDataPointer.
 */

#include <gtest/gtest.h>

#include <emcee/new_allocation_block_calculation.hpp>
#include <emcee/new_allocation_block.hpp>
#include <emcee/util.hpp>

TEST(NewMemoryBlockCalculation, from_new_address) {

  typedef uint8_t N_3Bytes[3];
  emcee::NewAllocationBlockCalculation<N_3Bytes> calculation;

  size_t block_address = 128;
  calculation.SetBlockPointer((void*) block_address);
  size_t block_size = sizeof(emcee::NewAllocationBlock);
  size_t min_data_address =block_address + block_size;
  ASSERT_LE((void*)min_data_address, calculation.data_pointer());

  size_t data_address = (size_t) calculation.data_pointer();
  size_t type_size = sizeof(N_3Bytes);
  size_t min_destructor_address = data_address + type_size;
  ASSERT_LE((void*)min_destructor_address, calculation.destructor_pointer());

}

TEST(NewMemoryBlockCalculation, from_data_address) {
  typedef uint8_t Type[5];
  emcee::NewAllocationBlockCalculation<Type> calculation;

  size_t data_address = 1024;
  calculation.SetDataPointer((void*)data_address);
  size_t max_block_address = data_address - sizeof(emcee::NewAllocationBlock);
  ASSERT_GE((void*)max_block_address, calculation.memory_block_pointer());

  size_t min_destructor_address = data_address + sizeof(Type);
  ASSERT_LE((void*)min_destructor_address, calculation.destructor_pointer());
}

TEST(NewMemoryBlockCalculation, is_aligned) {
  using emcee::IsAligned;
  emcee::NewAllocationBlockCalculation<uint8_t> calculation;
  calculation.SetBlockPointer((void*)1024);
  ASSERT_TRUE(IsAligned(calculation.memory_block_pointer()));
  ASSERT_TRUE(IsAligned(calculation.data_pointer()));
  ASSERT_TRUE(IsAligned(calculation.destructor_pointer()));
}