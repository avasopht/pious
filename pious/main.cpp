#include <cstdio>
#include "vector.hpp"
#include "os.hpp"
#include "os_setter.hpp"

class Foo : public pious::OsSetter {
 public:
  Foo() : os_(nullptr), val_(0) {}
  Foo(int val) : os_(nullptr), val_(val) {}
  Foo(const Foo &rhs) : os_(rhs.os_), val_(rhs.val_) {}

  virtual void SetOs(pious::Os *os) override {
    printf("Loaded OS motherfucker(%d).\n", val_);
    os_ = os;
  }
 private:
  pious::Os *os_;
  int val_;
};

int main() {
  pious::DefaultOs os;
  pious::Vector<Foo> foo(os, 15);
  foo.PushBack(Foo(10));

  return 0;
}