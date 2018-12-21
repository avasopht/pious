//
// Created by keldon on 20/12/18.
//

#include "unique_ptr.hpp"

#ifndef PIOUS_OBJECT_HPP
#define PIOUS_OBJECT_HPP
namespace emcee {

#include "memory_dependent.hpp"

class Platform;

/**! \brief Base class for objects in Emcee
 *
 *  The premise of Emcee is that you are in a restricted environment. Derive all non-trivial OO classes from Object
 *  to be able to instantiate objects and access "global" state.
 *
 */
class Object : public MemoryDependent {
 public:
  explicit Object(Platform &platform);

  template<typename T>
  UniquePtr<T> Create() {
    return MakeUnique<T>(*platform_);
  }

  template<typename T>
  static T *NewWithPlatform(void *address, Platform &p) {
    T *ptr = new(address)T;
    static_cast<Object *>(ptr)->platform_ = &p;
    return ptr;

  }

  void SetPlatform(Platform &p) {
    platform_ = &p;
  }

 protected:
  explicit Object();

 private:
  Platform *platform_;

  friend class New<Object[]>;
  friend class New<Object>;
  friend class UniquePtr<Object>;
};

}

#endif //PIOUS_OBJECT_HPP
