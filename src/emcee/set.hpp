/*
 * Created by The Pious Authors on 28/04/2017.
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

#ifndef PIOUS_SET_HPP
#define PIOUS_SET_HPP

#include "map.hpp"
#include "platform.hpp"

namespace emcee {

template<typename T>
class Set {
 public:
  class Iterator {
   public:
    explicit Iterator(const typename Map<T, int>::Iterator &map_iterator) : iterator_(map_iterator) {}

    Iterator &operator++() {
      ++iterator_;
      return *this;
    }

    Iterator operator++(int) {
      Iterator old = *this;
      ++iterator_;
      return old;
    }

    T &value() const {
      return iterator_.key();
    }

    size_t count() const {
      return iterator_.value();
    }

    bool operator==(const Iterator &rhs) const {
      if (&rhs == this)
        return true;

      return rhs.iterator_ == iterator_;
    }

    bool operator!=(const Iterator &rhs) const {
      if (&rhs == this)
        return false;

      return rhs.iterator_ != iterator_;
    }

   private:
    typename Map<T, int>::Iterator iterator_;
  };

  explicit Set(Platform *memory) : element_count_(memory) {}

  template<typename Y>
  bool Add(const Y &element) {
    ++element_count_[element];
    return true;
  }

  bool IsEmpty() const { return element_count_.IsEmpty(); }

  template<typename Y>
  bool Remove(const Y &element) {
    if (!element_count_.ContainsKey(element))
      return false;

    int &count = element_count_[element];
    --count;
    if (count == 0)
      element_count_.Remove(element);

    return true;
  }

  template<typename Y>
  bool Contains(const Y &element) {
    return element_count_.ContainsKey(element);
  }

  Iterator begin() { return Iterator(element_count_.begin()); }
  Iterator end() { return Iterator(element_count_.end()); }

 private:
  Map<T, int> element_count_;
};

}

#endif /* PIOUS_SET_HPP */
