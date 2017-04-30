/*
 * Created by The Pious Authors on 05/10/16.
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

#include <algorithm>
#include <gtest/gtest.h>
#include <emcee/vector.hpp>
using emcee::DefaultMemory;
using emcee::Vector;

TEST(Vector, CopyAndAssignment) {
  emcee::DefaultMemory mem;
  emcee::Vector<int> first(&mem);
  first.PushBack(1337);
  ASSERT_EQ(1337, first[0]);
  emcee::Vector<int> second(&mem);
  ASSERT_EQ(0, second.size());
  second = first;
  ASSERT_EQ(1337, second[0]);

  first[0] = 0;
  ASSERT_EQ(0, first[0]);
  ASSERT_EQ(1337, second[0]);


  std::swap(first, second);


  ASSERT_EQ(1337, first[0]);
  ASSERT_EQ(0, second[0]);

  emcee::Vector<int> with_default(&mem, 3, 11);
  ASSERT_EQ(3, with_default.size());
  ASSERT_EQ(11, with_default[0]);
  ASSERT_EQ(11, with_default[1]);
  ASSERT_EQ(11, with_default[2]);
}

TEST(Vector, Erase) {
  emcee::DefaultMemory mem;
  emcee::Vector<int> vec(&mem);
  vec.Reserve(128);
  for(int i = 0; i < static_cast<int>(vec.size()); ++i) {
    vec.PushBack(i);
  }

  for(size_t i = 0; i < static_cast<int>(vec.size()); i += 2) {
    vec.EraseAt(i);
  }

  for(size_t i = 0; i < vec.size(); ++i) {
    ASSERT_EQ(1, vec[i] % 2) << "all elements should be odd";
  }
}

TEST(Vector,Iterator) {
  DefaultMemory mem;
  Vector<int> vec(&mem);
  vec.PushBack(4);
  vec.PushBack(8);
  vec.PushBack(15);
  vec.PushBack(16);
  vec.PushBack(23);
  vec.PushBack(42);

  Vector<int>::Iterator iter = vec.begin();
  ASSERT_EQ(*iter, 4);
  ++iter;
  ASSERT_EQ(*iter, 8);
  --iter;
  ASSERT_EQ(*iter, 4);
  iter++;
  ASSERT_EQ(*iter, 8);
  ASSERT_EQ(*(iter--),8);
  const Vector<int>::ConstIterator const_iter = iter;
  ASSERT_EQ(*const_iter, 4);
}

class C {
 public:
  C() : array_{0,1,2,3,4,5,6,7,8,9} {}
  int & val() const {
    return const_cast<int&>(array_[0]);
  }
 private:
  int array_[10];
};

static const C c;

TEST(Vector,ConstModification) {
  c.val() = 9;
}