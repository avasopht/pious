/*
 * Created by The Pious Authors on 06/10/16.
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

#include <emcee/platform.hpp>
#include <emcee/string.hpp>

#include <emcee/literal.hpp>

TEST(String, BasicTest) {
  emcee::DefaultPlatform mem;
  emcee::String bleach(&mem, "Bleach");
  ASSERT_EQ(6, bleach.length());
  ASSERT_EQ('B', bleach[0]);
  ASSERT_EQ('l', bleach[1]);
  ASSERT_EQ('e', bleach[2]);
  ASSERT_EQ('a', bleach[3]);
  ASSERT_EQ('c', bleach[4]);
  ASSERT_EQ('h', bleach[5]);

  emcee::String ble = bleach.Substring(0, 3);
  ASSERT_EQ(3, ble.length());
  ASSERT_EQ('B', ble[0]);
  ASSERT_EQ('l', ble[1]);
  ASSERT_EQ('e', ble[2]);

  emcee::String ach = bleach.Substring(3);
  ASSERT_EQ(3, ach.length());
  ASSERT_EQ('a', ach[0]);
  ASSERT_EQ('c', ach[1]);
  ASSERT_EQ('h', ach[2]);

  emcee::String bleach_2 = ble + ach;
  ASSERT_EQ(6, bleach_2.length());
  ASSERT_EQ('B', bleach_2[0]);
  ASSERT_EQ('l', bleach_2[1]);
  ASSERT_EQ('e', bleach_2[2]);
  ASSERT_EQ('a', bleach_2[3]);
  ASSERT_EQ('c', bleach_2[4]);
  ASSERT_EQ('h', bleach_2[5]);

  ble = ble.ToLower();
  ASSERT_EQ('b', ble[0]);

  ASSERT_EQ(0, bleach.Compare(bleach_2));
  ASSERT_TRUE(ach < ble);
  ASSERT_TRUE(ble > ach);
  ASSERT_TRUE(ble < "da");
  ASSERT_TRUE(ble >= emcee::String(ble));

}