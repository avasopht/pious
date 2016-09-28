/*
 * Created by The Pious Authors on 27/09/2016.
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

#include "gtest/gtest.h"

#include "object.hpp"
#include "memory.hpp"

TEST(ArrayAllocation, creates_valid_instance) {
  using namespace pious;
  enum { kSize = 10 };
  void *ptr = malloc(sizeof(ArrayAllocation) + sizeof(int[kSize]));
  {
    void *array_ptr = &static_cast<uint8_t *>(ptr)[sizeof(ArrayAllocation)];

    ArrayAllocation *allocation = ArrayAllocation::InitFromPtr(ptr, kSize);

    ASSERT_EQ(ptr, allocation);
    ASSERT_EQ(kSize, allocation->size);
    ASSERT_EQ(array_ptr, allocation->array);
  }
  free(ptr);
}

TEST(ArrayAllocation, loads_allocation) {
  using namespace pious;

  typedef struct { int first, second; } Type;

  enum { kSize = 10 };
  void *ptr = malloc(sizeof(ArrayAllocation) + sizeof(Type[kSize]));
  {
    ArrayAllocation *allocation = ArrayAllocation::InitFromPtr(ptr, kSize);
    Type *array = static_cast<Type*>(allocation->array);
    ArrayAllocation *found_allocation = ArrayAllocation::FindFromArrayPtr(array);
    ASSERT_EQ(allocation, found_allocation);
    ASSERT_EQ(allocation->array, array);
  }
  free(ptr);
}

TEST(Array, default_constructs_and_deletes) {
  using pious::Memory;

  class InstanceCounter {
   public:
    InstanceCounter() : this_count (0) {
      this_count = constructor_count();
      ++constructor_count();
    }

    ~InstanceCounter() {
      ++destructor_count();
    }

    static int& constructor_count() {
      static int count = 0;
      return count;
    }

    static int& destructor_count() {
      static int destructor_count = 0;
      return destructor_count;
    }

    static void ClearCount() {
      constructor_count() = destructor_count() = 0;
    }

   private:
    int this_count;
  };

  Memory *memory = new pious::DefaultMemory();

  // Test new/delete
  {
    InstanceCounter *foo = pious::Object<InstanceCounter>(*memory).New();
    ASSERT_NE(nullptr, foo);
    ASSERT_EQ(foo->constructor_count(), 1);

    pious::Object<InstanceCounter>(*memory).Delete(foo);
    ASSERT_EQ(foo->destructor_count(), 1);
  }

  // Test new[]/delete[]
  {
    InstanceCounter::ClearCount(); // Yes I know, this is not the way to do it.
    InstanceCounter *default_array = pious::Object<InstanceCounter[10]>(*memory).New();
    ASSERT_EQ(InstanceCounter::constructor_count(), 10);
    pious::Object<InstanceCounter[]>(*memory).Delete(default_array);
    ASSERT_EQ(InstanceCounter::destructor_count(), 10);
  }

  delete memory;
}