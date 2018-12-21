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

#ifndef PIOUS_COUNT_CALLS_HPP
#define PIOUS_COUNT_CALLS_HPP


class CountCalls {
 public:
  CountCalls() { ++constructor_calls(); }
  CountCalls(const CountCalls &) { ++copy_calls(); }
  CountCalls &operator=(const CountCalls &) { ++assignment_calls(); return *this; }
  ~CountCalls() { ++destructor_calls(); }

  static int &constructor_calls() {
    static int val = 0;
    return val;
  }
  static int &destructor_calls() {
    static int val = 0;
    return val;
  }
  static int &copy_calls() {
    static int val = 0;
    return val;
  }
  static int &assignment_calls() {
    static int val = 0;
    return val;
  }

  static void ClearCount() {
    constructor_calls() = 0;
    destructor_calls() = 0;
    copy_calls() = 0;
    assignment_calls() = 0;
  }
};

#endif /* PIOUS_COUNT_CALLS_HPP */
