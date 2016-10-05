/*
 * Created by keldon on 29/09/16.
 */

#ifndef PIOUS_DESTRUCTOR_HPP
#define PIOUS_DESTRUCTOR_HPP

#include <cstddef>

namespace emcee {

/*! \brief A Destructor is responsible for calling the destructor(s) for an
 * allocation of objects created by `New<T>`.
 */
class Destructor {
 public:
  virtual ~Destructor() {}

  /*! Calls destructor(s) for object(s) managed by this instance. */
  virtual void Destroy() = 0;
};


template<typename T> class TypedDestructor : public Destructor {
 public:
  TypedDestructor(T *ptr) : ptr_(ptr) {}

  void Destroy() override {
    ptr_->~T();
  }


 private:
  T *ptr_;
};

template<typename T> class TypedDestructor<T[]> : public Destructor {
 public:
  TypedDestructor(T *ptr, size_t count) : ptr_(ptr), count_(count) {}

  void Destroy() override {
    for(size_t i = 0; i < count_; ++i) {
      ptr_[i].~T();
    }
  }


 private:
  T *ptr_;
  size_t count_;
};


/*! \brief  Destructor for arrays and single items.
 *
 * For a single element, use TypedDestructor<T[1]>. It is heavy for a single
 * instance but makes deletion incredibly easy.
 */
template<typename T, size_t N>
class TypedDestructor <T[N]> : public Destructor {
 public:
  TypedDestructor(T *ptr) : array_(ptr), count_(N) {}
  void Destroy() override {
    for(size_t i = 0; i < count_; ++i) {
      array_[i].~T();
    }
  }

 private:
  T *array_;
  size_t count_;
};

}

#endif /* PIOUS_DESTRUCTOR_HPP */
