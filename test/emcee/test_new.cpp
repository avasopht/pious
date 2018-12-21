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

#include <gtest/gtest.h>
#include <emcee/new.hpp>
#include "../pious/count_calls.hpp"


TEST(New, BasicTypesCompilesAndRuns) {
  emcee::DefaultPlatform mem;
  int *first = emcee::New<int>(&mem).Create();
  emcee::Delete(first);

  int *array = emcee::New<int[]>(&mem, 10).Create();
  emcee::Delete(array);
}

TEST(New, CallCount) {
  /*
   * Note beforehand: this tests for the number of times object construction
   * and destruction (etc.) methods are called, but in real life this should
   * not really matter. It is really sanity checking behavior.
   */

  {
    CountCalls::ClearCount();
    emcee::DefaultPlatform memory;
    CountCalls *ptr = emcee::New<CountCalls[]>(&memory, 5).Create();
    emcee::Delete(ptr);
    ASSERT_EQ(5, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::destructor_calls());
  }

  {
    CountCalls::ClearCount();
    emcee::DefaultPlatform memory;
    CountCalls *def = emcee::New<CountCalls>(&memory).Create();
    CountCalls *array = emcee::New<CountCalls[]>(&memory, 5).Create(*def);
    emcee::Delete(def);
    emcee::Delete(array);

    ASSERT_EQ(1, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::copy_calls());
    ASSERT_EQ(6, CountCalls::destructor_calls());
  }
}