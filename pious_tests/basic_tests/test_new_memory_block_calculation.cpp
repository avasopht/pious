/*
 * The testing here is fairly minimal since most logic is really contained in
 * NewMemoryBlockCalculation<T>::SetDataPointer.
 */

#include <gtest/gtest.h>

#include <pious/new_allocation_block_calculation.hpp>
#include <pious/new_allocation_block.hpp>
#include <pious/util.hpp>

TEST(NewMemoryBlockCalculation, from_new_address) {

  typedef uint8_t N_3Bytes[3];
  pious::NewAllocationBlockCalculation<N_3Bytes> calculation;

  size_t block_address = 128;
  calculation.SetBlockPointer((void*) block_address);
  size_t block_size = sizeof(pious::NewAllocationBlock);
  size_t min_data_address =block_address + block_size;
  ASSERT_LE((void*)min_data_address, calculation.data_pointer());

  size_t data_address = (size_t) calculation.data_pointer();
  size_t type_size = sizeof(N_3Bytes);
  size_t min_destructor_address = data_address + type_size;
  ASSERT_LE((void*)min_destructor_address, calculation.destructor_pointer());

}

TEST(NewMemoryBlockCalculation, from_data_address) {
  typedef uint8_t Type[5];
  pious::NewAllocationBlockCalculation<Type> calculation;

  size_t data_address = 1024;
  calculation.SetDataPointer((void*)data_address);
  size_t max_block_address = data_address - sizeof(pious::NewAllocationBlock);
  ASSERT_GE((void*)max_block_address, calculation.memory_block_pointer());

  size_t min_destructor_address = data_address + sizeof(Type);
  ASSERT_LE((void*)min_destructor_address, calculation.destructor_pointer());
}

TEST(NewMemoryBlockCalculation, is_aligned) {
  using pious::IsAligned;
  pious::NewAllocationBlockCalculation<uint8_t> calculation;
  calculation.SetBlockPointer((void*)1024);
  ASSERT_TRUE(IsAligned(calculation.memory_block_pointer()));
  ASSERT_TRUE(IsAligned(calculation.data_pointer()));
  ASSERT_TRUE(IsAligned(calculation.destructor_pointer()));
}