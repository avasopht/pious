/*
 * Created by The Pious Authors on 28/04/2017.
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
#include <emcee/set.hpp>
using emcee::Set;
using emcee::Platform;
using emcee::DefaultPlatform;

TEST(Set,BasicTest) {
  DefaultPlatform mem;
  Set<int> set(&mem);
  set.Add(11);
  ASSERT_TRUE(set.Contains(11));
  set.Add(11);
  ASSERT_TRUE(set.Contains(11));
  set.Remove(11);
  ASSERT_TRUE(set.Contains(11));
  set.Remove(11);
  ASSERT_FALSE(set.Contains(11));
}

TEST(Set,Iterator) {
  DefaultPlatform mem;
  Set<int> set(&mem);
  set.Add(7);
  set.Add(8);
  set.Add(1);

  Set<int>::Iterator iter = set.begin();
  ASSERT_EQ(iter.value(), 1);
  ++iter;
  ASSERT_EQ(iter.value(), 7);
  ++iter;
  ASSERT_EQ(iter.value(), 8);
  ++iter;
  ASSERT_EQ(iter, set.end());
}
