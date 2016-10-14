/*
 * Created by The Pious Authors on 11/10/16.
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

#include <pious/id.hpp>
#include <emcee/memory.hpp>
#include <emcee/string.hpp>

TEST(Id, Compare) {
  emcee::DefaultMemory mem;
  pious::Id first(mem);
  pious::Id second(mem);

  first.SetSid("pig");
  second.SetSid("pig");
  ASSERT_TRUE(first.Compare(second) == 0) << "Id's with same name should be equal.";

  first.SetIid(10);
  second.SetIid(11);
  ASSERT_TRUE(first.Compare(second) < 0) << "First's iid is lower, should be evaluated as less than the second.";

  second.SetSid("pif");
  ASSERT_TRUE(first.Compare(second) > 0) << "String id comparison takes precedence.";
}