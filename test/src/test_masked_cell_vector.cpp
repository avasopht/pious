/*
 * Created by The Pious Authors on 02/01/2017.
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

#include <emcee/masked_cell_vector.hpp>

TEST(MaskedCellVector,Basic) {
  emcee::DefaultPlatform mem;
  emcee::MaskedCellVector<int> vec(&mem);
  vec.SetSize(2, 8);
  vec[0] = 1;
  ASSERT_EQ(1, vec[0]);
  ASSERT_EQ(1, vec[1]);
  vec[2] = 2;
  ASSERT_EQ(2, vec[2]);
  ASSERT_EQ(2, vec[3]);
  vec[4] = 3;
  ASSERT_EQ(3, vec[4]);
  ASSERT_EQ(3, vec[5]);
  vec[6] = 4;
  ASSERT_EQ(4, vec[6]);
  ASSERT_EQ(4, vec[7]);
  vec[8] = 5;
  ASSERT_EQ(5, vec[8]);
  ASSERT_EQ(5, vec[0]);
  ASSERT_EQ(5, vec[1]);
}