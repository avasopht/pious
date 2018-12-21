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
  //! Constructor for MemoryDependent
  explicit Object(Platform *platform);
  explicit Object(Platform &platform);

  template<typename T>
  UniquePtr<T> Create() {
    return MakeUnique<T>(*platform_);
  }

 protected:
  explicit Object();
 private:
  Platform *platform_;
};

}

#endif //PIOUS_OBJECT_HPP
