//
// Created by keldon on 20/12/18.
//

#include <gtest/gtest.h>
#include <emcee/object.hpp>
#include <emcee/platform.hpp>
#include <boost/move/make_unique.hpp>
#include <boost/move/unique_ptr.hpp>

class ObjectTest : public ::testing::Test {
 protected:

  virtual void SetUp() {
    platform_ = boost::movelib::make_unique<emcee::DefaultPlatform>();
  }

  virtual void TearDown() {

  }

  boost::movelib::unique_ptr<emcee::Platform> platform_;
};

TEST_F(ObjectTest, CanInstantiateAnObject) {
  auto obj = emcee::Object(*platform_);
  auto inst = obj.Create<emcee::Object>();
  ASSERT_TRUE(inst);
}


class SmallInt : public emcee::Object {
 public:
  SmallInt() : val_(0){}

  void Initialize(int value) {
    val_ = value;
  }

  emcee::UniquePtr<SmallInt> operator+(const SmallInt &rhs) {
    auto ptr = Create<SmallInt>();
    ptr->Initialize(val_ + rhs.val_);
    return ptr;
  }

  int IntValue() const { return val_; }

 private:
  int val_;
};

TEST_F(ObjectTest, CanInstiateASubclass) {
  auto obj = emcee::Object(*platform_);
  auto number = obj.Create<SmallInt>();
  number->Initialize(7);
  ASSERT_EQ(7, number->IntValue());
  auto sum = *number + *number;
  ASSERT_EQ(14, sum->IntValue());
}