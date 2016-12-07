/*
 * Created by The Pious Authors on 04/10/16.
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

#include <gtest/gtest.h>
#include <emcee/shared_ptr.hpp>

TEST(SharedPtr,BasicTest) {
  emcee::DefaultMemory mem;
  emcee::SharedPtr<int> first(&mem);

  ASSERT_EQ(0, first.use_count());
  first.Create();
  ASSERT_EQ(1, first.use_count());
  ASSERT_TRUE(first.unique());

  emcee::SharedPtr<int> second(first);
  ASSERT_EQ(2, first.use_count());

  first.Reset();
  ASSERT_EQ(1, second.use_count());
  ASSERT_EQ(0, first.use_count());

}

TEST(SharedPtr,FromUnique) {
  emcee::DefaultMemory mem;
  int *iptr = emcee::New<int>(&mem).Create(1337);
  emcee::UniquePtr<int> unique(&mem, iptr);

  ASSERT_EQ(iptr, unique.get());

  emcee::SharedPtr<int> shared = unique;
  ASSERT_NE(iptr, unique.get());
  ASSERT_TRUE(shared.unique());
  ASSERT_EQ(iptr, shared.get());
}

TEST(SharedPtr, Swap) {
  emcee::DefaultMemory mem;
  int *first_ptr = emcee::New<int>(&mem).Create(1);
  int *second_ptr = emcee::New<int>(&mem).Create(2);
  emcee::SharedPtr<int> first(&mem, first_ptr);
  emcee::SharedPtr<int> second(&mem, second_ptr);

  first.Swap(second);

  ASSERT_EQ(*first, *second_ptr);
  ASSERT_EQ(*second, *first_ptr);
}

TEST(SharedPtr, Array) {
  emcee::DefaultMemory mem;
  int *array = emcee::New<int[]>(&mem, 10).Create();
  emcee::SharedPtr<int[]> smart_array(&mem, array);
  array[0] = 1337;
  ASSERT_EQ(smart_array[0], array[0]);

  emcee::SharedPtr<int[]> second(&mem);
  second.Create(10);
  ASSERT_EQ(second[0], 0);

  smart_array.Swap(second);
  ASSERT_EQ(second[0], array[0]);
}