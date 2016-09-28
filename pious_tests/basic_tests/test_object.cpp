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

TEST(Array, default_constructs) {
  using pious::Memory;

  class Foo {
   public:
    Foo() : this_count (0) {
      this_count = total_count();
      ++total_count();
    }

    int& total_count() const {
      static int count = 0;
      return count;
    }

   private:
    int this_count;
  };

  Memory *memory = new pious::DefaultMemory();
  Foo *foo = pious::Object<Foo>(*memory).New();
  ASSERT_NE(nullptr, foo);
  ASSERT_EQ(foo->total_count(), 1);

  delete memory;
}