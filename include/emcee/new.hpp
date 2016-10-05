/*
 * Created by The Pious Authors on 29/09/2016.
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

#ifndef PIOUS_NEW_HPP
#define PIOUS_NEW_HPP

#include "emcee/destructor.hpp"
#include "emcee/new_allocation_block.hpp"
#include "emcee/memory_dependent.hpp"
#include "emcee/memory.hpp"
#include "emcee/util.hpp"

#include <cstddef>
#include <cassert>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

namespace emcee {


class Memory;

size_t ArraySize(void *ptr);
void Delete(void *ptr);

template<typename T>
class New {
 public:
  New(Memory &memory) : memory_(memory), arena_(0) {}

  T* Create() {
    return New<T[]>(memory_, 1).WithArena(arena_).Create();
  }

  T* Create(const T &other) {
    return New<T[]>(memory_, 1).WithArena(arena_).Create(other);
  }


 private:
  Memory &memory_;
  size_t arena_;
};

struct ObjectBlock {
  NewAllocationBlock *allocation_block;
  size_t data[1];

  void* data_ptr() { return data; }

  static ObjectBlock* FromDataPtr(void *data) {
    ObjectBlock *block = emcee::Offset<ObjectBlock>(data).Calc(-sizeof(size_t));
    if(!block->allocation_block)
      return nullptr;

    if(block->allocation_block->data() != data)
      return nullptr;

    return block;
  }
};

template<typename T>
class New<T[]> {
 public:

  typedef TypedDestructor<T[]> DestructorType;

  New(Memory &memory, size_t count) : memory_(memory), count_(count), arena_(0) {};

  New& WithArena(size_t arena) { arena_ = arena; return *this; }

  /*! Allocates and constructs a new T to be managed by this instance. */
  T* Create() {
    NewAllocationBlock *block = Allocate();
    T *ptr = static_cast<T*>(block->data());

    for(size_t i = 0; i < count_; ++i) {
      Construct(&ptr[i]);
    }

    return ptr;
  }

  /*! Allocates and constructs a new T to be managed by this instance. */
  T* Create(const T&other) {
    NewAllocationBlock *block = Allocate();
    T *ptr = static_cast<T*>(block->data());

    for(size_t i = 0; i < count(); ++i) {
      Construct(&ptr[i], other);
    }

    return ptr;
  }

  size_t count() const { return count_; }

 private:
  Memory &memory_;
  size_t count_;
  size_t arena_;

  void Construct(void *ptr) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    Construct(ptr, is_memory_dependent);
  }

  void Construct(void *ptr, const T &other) {
    boost::is_base_of<MemoryDependent,T> is_memory_dependent;
    Construct(ptr, other, is_memory_dependent);
  }

  void Construct(void *ptr, boost::true_type /*is memory dependent */) {
    new(ptr)T(memory_);
  }

  void Construct(void *ptr, boost::false_type /*not memory dependent */) {
    boost::has_trivial_constructor<T> has_trivial_constructor;
    new(ptr)T();
  }

  void Construct(void *ptr, const T &other, boost::true_type) {
    /* Is memory dependent */
    new(ptr)T(memory_, other);
  }

  void Construct(void *ptr, const T &other, boost::false_type) {
    /* Is not memory dependent */
    new(ptr)T(other);
  }

  NewAllocationBlock* NewBlock() {
    NewAllocationBlock* block =
        static_cast<NewAllocationBlock*>(
            memory_.Allocate(sizeof(NewAllocationBlock)));
    new(block)NewAllocationBlock(memory_);
    block->WithCount(count());
    return block;
  }

  ObjectBlock* AllocateObject() {
    size_t object_alloc_size = sizeof(T) * count_ + sizeof(size_t);
    void *allocation = memory_.Allocate(object_alloc_size);
    ObjectBlock *object_block = static_cast<ObjectBlock*>(allocation);
    T *ptr = static_cast<T*>(object_block->data_ptr());

    return object_block;
  }

  Destructor* NewDestructor(void *vdata) {
    void *destructor_ptr = memory_.Allocate(sizeof(DestructorType));
    T *data = static_cast<T*>(vdata);
    DestructorType *destructor = new(destructor_ptr)DestructorType(data, count());
    return destructor;
  }

  NewAllocationBlock* Allocate() {

    NewAllocationBlock *allocation_block = NewBlock();

    ObjectBlock *object_block = AllocateObject();
    object_block->allocation_block = allocation_block;
    allocation_block->WithData(object_block->data);

    Destructor *destructor = NewDestructor(object_block->data);
    allocation_block->WithDestructor(destructor);

  }
};

}

#endif /* PIOUS_NEW_HPP */
