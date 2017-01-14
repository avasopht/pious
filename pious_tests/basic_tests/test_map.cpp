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

TEST(Map,BasicTest) {
  emcee::DefaultMemory mem;
  emcee::Map<int,const char*> map(&mem);
  map[10] = "PRINT \"Hello World\"";
  map[20] = "GOSUB 100";
  map[100] = "PRINT \"Line 100 muthafuckers!\"";
  map[110] = "RETURN";
  ASSERT_STREQ("RETURN", map[110]);
  ASSERT_TRUE(map.ContainsKey(110));
  map.Erase(110);
  ASSERT_FALSE(map.ContainsKey(110));
}