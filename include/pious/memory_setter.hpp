/*
 * Created by keldon on 28/09/16.
 */

#ifndef PIOUS_MEMORY_SETTER_HPP
#define PIOUS_MEMORY_SETTER_HPP

#include "boost/type_traits/is_base_of.hpp"

namespace pious {

class Memory;

class MemorySetter {
 public:
  virtual ~MemorySetter() = 0;
  virtual void SetMemory(Memory *ptr) = 0;

  /* Injects memory into object if object derives from MemorySetter. */
  template<typename T> static void Inject(T &ref, Memory *memory) {
    boost::is_base_of<MemorySetter,T> can_inject;
    InjectMemory(can_inject, ref, memory);
  }

 private:

  template<typename T> static void InjectMemory(boost::true_type, T &ref, Memory *memory) {
    ref.SetMemory(memory);
  }

  template<typename T> static void InjectMemory(boost::false_type, T&, Memory*) {}
};

}

#endif /* PIOUS_MEMORY_SETTER_HPP */
