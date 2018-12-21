//
// Created by keldon on 20/12/18.
//

#include "unique_ptr.hpp"

#ifndef PIOUS_OBJECT_HPP
#define PIOUS_OBJECT_HPP
namespace emcee {

#include "memory_dependent.hpp"

/**! Workaround for lack of template packing or lambdas, etc. for use in Object subclass methods. e.g.:
 *
 *  void method() {
 *      auto EMCEE_OBJECT_NEW(cat, AngryCat, traits, personality);
 *  }
 *
 *  Only use in single initialization statement.
 */
#define EMCEE_OBJECT_NEW(variable, T, ...) \
  (variable) = Create<T>(); \
  (variable)->Initialize(__VA_ARGS__)


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

  // This is used by emcee::New
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
  void SetPlatform(Platform &p) {
    platform_ = &p;
  }
#pragma clang diagnostic pop

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
