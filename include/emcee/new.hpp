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

#include "destructor.hpp"
#include "new_allocation_block.hpp"
#include "memory_dependent.hpp"
#include "memory.hpp"
#include "util.hpp"

#include <cstddef>
#include <cassert>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

namespace emcee {


class Memory;

/*! \brief Returns size of an array providing it was created with New<>.
 *
 *  Returns 1 if the object is not an array but a single element created with
 *  New<>.
 */
size_t ArraySize(void *ptr);

/*! Deletes object created with New<>. */
void Delete(void *ptr);

/*! \brief  An ObjectBlock is created with each New instantiation, holding
 * a pointer to the NewAllocationBlock.
 */
struct ObjectBlock {
  NewAllocationBlock *allocation_block;

  /*! Variable length data for allocation. */
  size_t var_length_data[1];

  /*! Returns pointer to ObjectBlock data. */
  void* data_ptr() { return var_length_data; }

  /*! \brief Returns a pointer to an ObjectBlock based on a data pointer.
   *
   * \param data pointer to data.
   * \return Returns null if data was not created by New.
   */
  static ObjectBlock* FromDataPtr(void *data) {
    ptrdiff_t word_size = (ptrdiff_t)sizeof(size_t);
    ObjectBlock *block = emcee::Offset<ObjectBlock>(data).Calc(-word_size);
    if(block->allocation_block && block->allocation_block->data() == data)
      return block;
    return nullptr;
  }
};


/*! \brief Implements non-trivial object and array allocation and construction.
 *
 *  An object or array created with New<> can be deleted with emcee::Delete()
 *  and have its size queried.
 *
 *  Minor support for memory arenas has been provided.
 *
 *  This class also respects Memory injection semantics.
 */
template<typename T>
class New {
 public:
  New(Memory *memory) : memory_(memory), arena_(0) {}

  /*! Allocates and constructs a default instance of T. */
  T* Create() {
    return New<T[]>(memory_, 1).WithArena(arena_).Create();
  }

  /*! Allocates and copy-constructs instance of T from `other`. */
  T* Create(const T &other) {
    return New<T[]>(memory_, 1).WithArena(arena_).Create(other);
  }

  /*! Sets arena of allocation when `Create()` is called */
  New& WithArena(size_t arena) { arena_ = arena; return *this; }


 private:
  Memory *memory_;
  size_t arena_;
};

template<typename T>
class New<T[]> {
 public:

  typedef TypedDestructor<T[]> DestructorType;

  New(Memory *memory, size_t count) : memory_(memory), count_(count), arena_(0) {};

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
  Memory *memory_;
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
            memory_->Allocate(sizeof(NewAllocationBlock)));
    new(block)NewAllocationBlock(memory_);
    block->WithCount(count());
    return block;
  }

  ObjectBlock* AllocateObject() {
    size_t object_alloc_size = sizeof(T) * count_ + sizeof(size_t);
    void *allocation = memory_->Allocate(object_alloc_size);
    ObjectBlock *object_block = static_cast<ObjectBlock*>(allocation);

    return object_block;
  }

  Destructor* NewDestructor(void *vdata) {
    void *destructor_ptr = memory_->Allocate(sizeof(DestructorType));
    T *data = static_cast<T*>(vdata);
    DestructorType *destructor = new(destructor_ptr)DestructorType(data, count());
    return destructor;
  }

  NewAllocationBlock* Allocate() {

    NewAllocationBlock *allocation_block = NewBlock();

    ObjectBlock *object_block = AllocateObject();
    object_block->allocation_block = allocation_block;
    allocation_block->WithData(object_block->var_length_data);

    Destructor *destructor = NewDestructor(object_block->var_length_data);
    allocation_block->WithDestructor(destructor);

    return allocation_block;

  }
};

}

#endif /* PIOUS_NEW_HPP */
