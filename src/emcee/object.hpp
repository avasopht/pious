//
// Created by keldon on 20/12/18.
//

#ifndef PIOUS_OBJECT_HPP
#define PIOUS_OBJECT_HPP
namespace emcee {

class Platform;

/**! \brief Base class for objects in Emcee
 *
 *  The premise of Emcee is that you are in a restricted environment. Derive all non-trivial OO classes from Object
 *  to be able to instantiate objects and access "global" state.
 *
 */
class Object {
 public:
  Object(Platform &platform);
  virtual ~Object() = default;
 protected:
  explicit Object();
 private:
  Platform *platform_;
};

}

#endif //PIOUS_OBJECT_HPP
