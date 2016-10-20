/*
 * Created by The Pious Authors on 20/10/16.
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
#include <emcee/emcee.hpp>

TEST(WeakPtr,FromShared) {
  emcee::DefaultMemory mem;
  typedef int Type;
  typedef emcee::SharedPtr<Type> SharedType;
  typedef emcee::WeakPtr<Type> WeakType;

  SharedType shared(mem);
  shared.Create();
  (*shared) = 10;

  WeakType weak(shared);
  ASSERT_EQ(10, *weak);

  shared.Reset();
  ASSERT_EQ(nullptr, weak.get());
}

TEST(WeakPtr,FromSharedArray) {
  emcee::DefaultMemory mem;
  typedef int Type;
  typedef emcee::SharedPtr<Type[]> SharedType;
  typedef emcee::WeakPtr<Type[]> WeakType;

  SharedType shared(mem);
  shared.Create(10);
  for(size_t i = 0; i < 10; ++i) {
    shared[i] = (int) i;
  }

  WeakType weak(shared);
  ASSERT_EQ(0, weak[0]);
  ASSERT_EQ(1, weak[1]);
  ASSERT_EQ(2, weak[2]);
  ASSERT_EQ(3, weak[3]);
  ASSERT_EQ(4, weak[4]);
  ASSERT_EQ(5, weak[5]);
  ASSERT_EQ(6, weak[6]);
  ASSERT_EQ(7, weak[7]);
  ASSERT_EQ(8, weak[8]);
  ASSERT_EQ(9, weak[9]);

  shared.Reset();
  ASSERT_EQ(nullptr, weak.get());
}