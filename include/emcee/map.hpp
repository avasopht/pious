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
// #include "memory_setter.hpp" // included from vector.hpp
#include <utility>

namespace emcee {

class Memory;

template<typename Key, typename T>
class Map : public virtual MemoryDependentWithCopy {
 public:

  struct Node : public virtual MemoryDependent {
    Vector<SharedPtr<Node>> next;
    T value;
    Key key;

    Node(Memory * memory) : next(memory), value(), key() {}

    Node & WithLevel(int level) {
      next.Resize(level);
      return *this;
    }

    Node & WithKey(const Key & new_key) {
      key = new_key;
      return *this;
    }
  };

  class Iterator {
   public:
    Iterator(SharedPtr<Node> & node) : current_(node) {}

    Iterator() {}

    T & operator*() const { return value(); }

    T & value() const {
      assert(current_);
      return current_->value;
    }

    Key & key() const {
      assert(current_);
      return current_->key;
    }

    bool operator!=(const Iterator & rhs) const {
      if (&rhs == this)
        return false;

      if (BothAreNull(*this, rhs))
        return false;

      if (OneIsNull(*this, rhs))
        return true;

      return current_->key != rhs.current_->key;
    }

    bool operator==(const Iterator & rhs) const {
      if (&rhs == this)
        return true;

      if (OneIsNull(*this, rhs))
        return false;

      if (BothAreNull(*this, rhs))
        return true;

      return current_->key == rhs.current_->key;
    }

    bool BothAreNull(const Iterator & lhs, const Iterator & rhs) const {
      return !lhs.current_ && !rhs.current_;
    }

    bool OneIsNull(const Iterator & lhs, const Iterator & rhs) const {
      return !lhs.current_ ^ !rhs.current_;
    }

    Iterator & operator++() {
      assert(current_ && current_->next.size() > 0);
      current_ = current_->next[0];
    }

   private:
    SharedPtr<Node> current_;
  };

  Iterator begin() {
    return Iterator(head_->next[0]);
  }

  Iterator end() { return Iterator(); }

  Map() : head_(), levels_(0), size_(0) {}

  Map(Memory * memory) : head_(memory), levels_(1), size_(0) {
    Init();
  }

  Map(Memory * memory, const Map & other) : head_(memory), levels_(1) {
    if (!head_.memory())
      head_.SetMemory(other.memory());
    Init();
    for (SharedPtr<Node> cur = other.head_->next[0]; cur; cur = cur->next[0]) {
      (*this)[cur->value] = cur->key;
    }
  }

  void SetMemory(Memory * mem) {
    if (mem == memory())
      return;

    head_.SetMemory(mem);
    levels_ = 1;
    size_ = 0;
    Init();
  }

  void Init() {
    assert(memory());
    if (!memory())
      return;

    head_.Create();
    size_ = 0;
    head_->WithLevel(33);
  }

  bool Empty() const { return size_ == 0; }

  T * Get(const Key & key) {
    if (ContainsKey(key))
      return &operator[](key);

    return nullptr;
  }

  T & operator[](const Key & key) {
    SharedPtr<Node> search = Find(key);
    if (search)
      return search->value;

    assert(memory());

    int level = 0;
    for (int r = rand(); (r & 1) == 1; r >>= 1) {
      ++level;
      if (level == levels_) {
        ++levels_;
        break;
      }
    }

    SharedPtr<Node> new_node(memory());
    new_node.Create()->WithLevel(level + 1).WithKey(key);
    const SharedPtr<Node> * cur = &head_;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; (*cur)->next[i]; cur = &(*cur)->next[i]) {
        if ((*cur)->next[i]->key > key)
          break;
      }
      if (i <= level) {
        new_node->next[i] = (*cur)->next[i];
        (*cur)->next[i] = new_node;
      }
    }
    ++size_;
    return new_node->value;
  }

  bool ContainsKey(const Key & key) {
    SharedPtr<Node> cur = head_;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i]; cur = cur->next[i]) {
        if (cur->next[i]->key > key)
          break;
        if (cur->next[i]->key == key)
          return true;
      }
    }
    return false;
  }

  bool Remove(const Key & key) {
    SharedPtr<Node> cur = head_;
    bool found = false;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i]; cur = cur->next[i]) {
        if (cur->next[i]->key == key) {
          found = true;
          cur->next[i] = cur->next[i]->next[i];
          break;
        }

        if (cur->next[i]->key > key)
          break;
      }
    }

    if (found)
      --size_;
    return found;
  }

  size_t size() const { return size_; }

  Memory * memory() const { return head_.memory(); }

 private:
  SharedPtr<Node> head_;
  int levels_;
  size_t size_;

  SharedPtr<Node> Find(const Key & key) {
    SharedPtr<Node> cur = head_;
    for (int i = levels_ - 1; i >= 0; --i) {
      for (; cur->next[i]; cur = cur->next[i]) {
        if (cur->next[i]->key > key)
          break;
        if (cur->next[i]->key == key)
          return cur->next[i];
      }
    }
    return SharedPtr<Node>();
  }
};

}

#endif /* PIOUS_MAP_HPP */
