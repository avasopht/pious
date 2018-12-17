/*
 * Created by The Pious Authors on 14/01/2017.
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
#include <emcee/map.hpp>
#include <emcee/string.hpp>
#include <emcee/vector.hpp>
using emcee::Map;
using emcee::DefaultMemory;
using emcee::Memory;
using emcee::Vector;

TEST(Map,BasicTest) {
  emcee::DefaultMemory mem;
  emcee::Map<int, emcee::String> map(&mem);
  ASSERT_TRUE(map.IsEmpty());
  map[10] = emcee::String(&mem, "Helvetica");
  ASSERT_FALSE(map.IsEmpty());
  ASSERT_TRUE(map.ContainsKey(10));
  ASSERT_STREQ("Helvetica", map[10].c_str());
  ASSERT_FALSE(map.Remove(11));
  ASSERT_TRUE(map.Remove(10));
  ASSERT_TRUE(map.IsEmpty());
  ASSERT_FALSE(map.ContainsKey(10));
}

TEST(Map,SharedPtrInMap) {
  emcee::DefaultMemory mem;
  typedef emcee::SharedPtr<char[]> SharedCPtr;
  emcee::Map<SharedCPtr,SharedCPtr> map(&mem);
  emcee::SharedPtr<char[]> a(&mem,emcee::New<char[]>(&mem,2).Create());
  emcee::SharedPtr<char[]> b(&mem,emcee::New<char[]>(&mem,2).Create());
  emcee::SharedPtr<char[]> c(&mem,emcee::New<char[]>(&mem,2).Create());
  emcee::SharedPtr<char[]> d(&mem,emcee::New<char[]>(&mem,2).Create());
  strcpy(a.get(), "a");
  strcpy(b.get(), "b");
  strcpy(c.get(), "c");
  strcpy(d.get(), "d");
  map[a] = a;
  map[b] = b;
  map[c] = c;
  map[d] = d;
  ASSERT_EQ(map[a],a);
  ASSERT_EQ(map[b],b);
  ASSERT_EQ(map[c],c);
  ASSERT_EQ(map[d],d);
}

TEST(Map,ToVectorOfVectors) {
  DefaultMemory mem;
  Map<int,Vector<Vector<int>>> map(&mem);
  map[10] = Vector<Vector<int>>(&mem);
  map[10].PushBack(Vector<int>(&mem));
  map[10][0].PushBack(110);
  ASSERT_EQ(map[10][0][0], 110);
}