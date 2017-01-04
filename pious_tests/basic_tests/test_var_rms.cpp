/*
 * Created by The Pious Authors on 03/01/2017.
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
#include <pious_dsp_lib/var_rms.hpp>
#include <memory.hpp>

static float RoundFloat(float precision, float value) {
  float normalized = value / precision;
  float sign = value > 0 ? 1.f : -1.f;
  int64_t as_int = (int64_t)(normalized + 0.5f * sign);
  float rounded = as_int * precision;
  return rounded;
}

TEST(VarRms, Basic) {
  emcee::DefaultMemory mem;
  pious::VarRms rms(&mem);
  rms.SetCapacity(8);
  rms.Write(7);
  rms.Write(9);
  rms.Write(12);
  rms.Write(3);
  rms.Write(6);
  rms.Write(4);
  rms.Write(8);
  rms.Write(2);

  float precision = 0.001f;
  ASSERT_FLOAT_EQ(2.000, RoundFloat(precision, rms.CalcRms(1)));
  ASSERT_FLOAT_EQ(5.831, RoundFloat(precision, rms.CalcRms(2)));
  ASSERT_FLOAT_EQ(5.292, RoundFloat(precision, rms.CalcRms(3)));
  ASSERT_FLOAT_EQ(5.477, RoundFloat(precision, rms.CalcRms(4)));
  ASSERT_FLOAT_EQ(5.079, RoundFloat(precision, rms.CalcRms(5)));
  ASSERT_FLOAT_EQ(6.745, RoundFloat(precision, rms.CalcRms(6)));
  ASSERT_FLOAT_EQ(7.111, RoundFloat(precision, rms.CalcRms(7)));
  ASSERT_FLOAT_EQ(7.098, RoundFloat(precision, rms.CalcRms(8)));
}