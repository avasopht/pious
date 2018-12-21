/*
 * Created by The Pious Authors on 31/12/2016.
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

#ifndef PIOUS_POW2_HPP
#define PIOUS_POW2_HPP

#include <cstdint>

static const uint64_t UINT64_MAX_POW2 = 1ULL << 63;
static const int64_t INT64_MAX_POW2 = 1LL << 62;
static const uint32_t UINT32_MAX_POW2 = 1U << 31;
static const int32_t INT32_MAX_POW2 = 1 << 30;
static const uint16_t UINT16_MAX_POW2 = 1 << 15;
static const int64_t INT16_MAX_POW2 = 1 << 14;
static const uint8_t UINT8_MAX_POW2 = 1 << 7;
static const int8_t INT8_MAX_POW2 = 1 << 6;

/* Returns the N in 2^N that equals val, or -1. */
int Log2(uint64_t val);

bool IsPow2(uint64_t val);

/* Returns the smallest power of 2 >= val, otherwise returns UINT64_MAX. */
uint64_t SmallestPow2Gte(uint64_t val);

#endif /* PIOUS_POW2_HPP */
