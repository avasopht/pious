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

  boost::movelib::unique_ptr<emcee::Platform>  platform_;
};

TEST_F(ObjectTest, CanInstantiateAnObject) {
  auto obj = emcee::Object(*platform_);
  auto inst = obj.Create<emcee::Object>();
  ASSERT_TRUE(inst);
}