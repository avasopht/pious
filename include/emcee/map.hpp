/*
 * Created by The Pious Authors on 11/01/2017.
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

#ifndef PIOUS_MAP_HPP
#define PIOUS_MAP_HPP

#include "vector.hpp"
#include <utility>

namespace emcee {

class Memory;

template<typename Key, typename T>
class Map {
 public:
  typedef std::pair<Key,T> ValueType;
  Map(Memory *memory) : mappings_(memory) {}
  void SetMemory(Memory *memory) {
    mappings_.SetMemory(memory);
  }
  Memory *memory() const { return mappings_.memory(); }

  size_t Erase(const Key &k) {
    size_t erase_count = 0;
    for(int i = 0; i < (int)mappings_.size(); ++i) {
      if(mappings_.At((size_t)i).first == k) {
        mappings_.EraseAt(i);
        --i;
        ++erase_count;
      }
    }
    return erase_count;
  }

  T& operator[](const Key &k) {
    assert(memory());
    for(size_t i = 0; i < mappings_.size(); ++i) {
      ValueType &mapping = mappings_.At(i);
      if(mapping.first == k)
        return mapping.second;
    }
    mappings_.PushBack(std::pair<Key,T>(k, T()));
    return mappings_.Back().second;
  }

  bool ContainsKey(const Key &k) {
    if(!memory())
      return false;
    for(size_t i = 0; i < mappings_.size(); ++i) {
      if(mappings_.At(i).first == k)
        return true;
    }
    return false;
  }

 private:
  Vector<ValueType> mappings_;
};

}

#endif /* PIOUS_MAP_HPP */
