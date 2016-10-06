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

#include "emcee/string.hpp"

#include <cstring>

namespace emcee {

String::String(Memory &memory) : memory_(&memory), string_(memory), size_(0) { }

String::String(Memory &memory, const char *str)
  : memory_(&memory),
    string_(memory),
    size_(0)
{
  ConstructString(str, 0, strlen(str));
}

String::String(Memory &memory, const char *str, size_t begin)
  : memory_(&memory),
    string_(memory),
    size_(0)
{
  ConstructString(str, begin, strlen(str));
}

String::String(Memory &memory, const char *str, size_t begin, size_t end)
  : memory_(&memory),
    string_(memory),
    size_(0)
{
  ConstructString(str, begin, end);
}

String::String(const String &str, size_t begin)
  : memory_(str.memory_),
    string_(*str.memory_),
    size_(0)
{
  ConstructString(str.c_str(), begin, str.length());
}

String::String(const String &str, size_t begin, size_t end)
  : memory_(str.memory_),
    string_(*str.memory_),
    size_(0)
{
  ConstructString(str.c_str(), begin, end);
}

const char *String::c_str() const {
  return string_.get();
}

size_t String::length() const {
  return size_;
}

String String::Substring(size_t begin_idx) const {
  return String(*this, begin_idx);
}

String String::Substring(size_t begin_idx, size_t end_idx) const {
  return String(*this, begin_idx, end_idx);
}

const char &String::operator[](size_t idx) const {
  return string_[idx];
}

String String::operator+(const String &rhs) const {
  return String(*this, rhs);
}

void String::ConstructString(const char *cstr, size_t begin, size_t end) {
  string_.Reset();
  assert(end > begin);
  size_ = end - begin;

  if(size_ == 0)
    return;

  string_.Create(size_ + 1);
  for(size_t i = 0; i < size_; ++i) {
    string_[i] = cstr[begin + i];
  }
  string_[size_] = '\0';

}

String::String(const String &first, const String &second)
  : memory_(first.memory_),
    string_(*first.memory_),
    size_(0)
{
  size_ = first.length() + second.length();
  string_.Create(size_ + 1);
  for(size_t i = 0; i < first.length(); ++i) {
    string_[i] = first[i];
  }
  for(size_t i = 0; i < second.length(); ++i) {
    string_[first.length() + i] = second[i];
  }
  string_[size_] = '\0';
}

}