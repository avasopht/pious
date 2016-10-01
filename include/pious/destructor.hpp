/*
 * Created by keldon on 29/09/16.
 */

#ifndef PIOUS_DESTRUCTOR_HPP
#define PIOUS_DESTRUCTOR_HPP

#include <cstddef>

namespace pious {

/*! \brief A Destructor is responsible for calling the destructor(s) for an
 * allocation of objects created by `New<T>`.
 */
class Destructor {
 public:
  virtual ~Destructor() {}

  /*! Calls destructor(s) for object(s) managed by this instance. */
  virtual void Destroy() = 0;
};


template<typename T> class TypedDestructor {
 private:
  TypedDestructor() = delete;
  TypedDestructor(const TypedDestructor&) = delete;
};


/*! \brief  Destructor for arrays and single items.
 *
 * For a single element, use TypedDestructor<T[1]>. It is heavy for a single
 * instance but makes deletion incredibly easy.
 */
template<typename T, size_t N>
class TypedDestructor <T[N]> : public Destructor {
 public:
  TypedDestructor(T *ptr) : array_(ptr) {}
  void Destroy() override {
    for(size_t i = 0; i < N; ++i) {
      array_[i].~T();
    }
  }

 private:
  T *array_;
};

}

#endif /* PIOUS_DESTRUCTOR_HPP */
