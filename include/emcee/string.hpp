/*
 * Created by The Pious Authors on 05/10/16.
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

#ifndef PIOUS_STRING_HPP
#define PIOUS_STRING_HPP

#include "memory_dependent.hpp"
#include "shared_ptr.hpp"

namespace emcee {

class Memory;

class String : public virtual MemoryDependent {
 public:
  // Note: default copy and assignment operators are fine.

  String();
  String(Memory &memory);
  String(Memory &memory, const char *str);
  String(Memory &memory, const char *str, size_t begin);
  String(Memory &memory, const char *str, size_t begin, size_t end);
  String(const String &str, size_t begin);
  String(const String &str, size_t begin, size_t end);
  String(const String &first, const String &second);

  const char *c_str() const;
  size_t length() const;
  Memory* memory() const { return memory_; }

  String Substring(size_t begin_idx) const;
  String Substring(size_t begin_idx, size_t end_idx) const;

  String ToLower() const;

  int Compare(const String &rhs) const;

  const char& operator[](size_t idx) const;
  String operator+(const String &rhs) const;

 private:
  Memory *memory_;
  SharedPtr<char[]> string_;
  size_t size_;

  void ConstructString(const char *cstr, size_t begin, size_t end);
};

bool operator==(const String &lhs, const String &rhs);
bool operator==(const char *lhs, const String &rhs);
bool operator==(const String &lhs, const char *rhs);

bool operator!=(const String &lhs, const String &rhs);
bool operator!=(const char *lhs, const String &rhs);
bool operator!=(const String &lhs, const char *rhs);

bool operator<(const String &lhs, const String &rhs);
bool operator<(const char *lhs, const String &rhs);
bool operator<(const String &lhs, const char *rhs);

bool operator<=(const String &lhs, const String &rhs);
bool operator<=(const char *lhs, const String &rhs);
bool operator<=(const String &lhs, const char *rhs);

bool operator>(const String &lhs, const String &rhs);
bool operator>(const char *lhs, const String &rhs);
bool operator>(const String &lhs, const char *rhs);

bool operator>=(const String &lhs, const String &rhs);
bool operator>=(const char *lhs, const String &rhs);
bool operator>=(const String &lhs, const char *rhs);

}

#endif /* PIOUS_STRING_HPP */
