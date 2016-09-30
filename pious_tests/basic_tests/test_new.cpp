/*
 * Created by keldon on 30/09/16.
 */

#include "gtest/gtest.h"
#include "new.hpp"
#include "memory.hpp"

namespace {

class CountCalls {
 public:
  CountCalls() { ++constructor_calls(); }
  CountCalls(const CountCalls &) { ++copy_calls(); }
  CountCalls &operator=(const CountCalls &) { ++assignment_calls(); }
  ~CountCalls() { ++destructor_calls(); }

  static int &constructor_calls() {
    static int val = 0;
    return val;
  }
  static int &destructor_calls() {
    static int val = 0;
    return val;
  }
  static int &copy_calls() {
    static int val = 0;
    return val;
  }
  static int &assignment_calls() {
    static int val = 0;
    return val;
  }

  static void ClearCount() {
    constructor_calls() = 0;
    destructor_calls() = 0;
    copy_calls() = 0;
    assignment_calls() = 0;
  }
};

}

TEST(New, CallCount) {
  /*
   * Note beforehand: this tests for the number of times object construction
   * and destruction (etc.) methods are called, but in real life this should
   * not really matter. It is really sanity checking behavior.
   */

  {
    CountCalls::ClearCount();
    pious::DefaultMemory memory;
    CountCalls *ptr = pious::New<CountCalls[5]>(memory).Create();
    pious::Delete(ptr);
    ASSERT_EQ(5, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::destructor_calls());
  }

  {
    CountCalls::ClearCount();
    pious::DefaultMemory memory;
    CountCalls *def = pious::New<CountCalls>(memory).Create();
    CountCalls *array = pious::New<CountCalls[5]>(memory).Create(*def);
    pious::Delete(def);
    pious::Delete(array);

    ASSERT_EQ(1, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::copy_calls());
    ASSERT_EQ(6, CountCalls::destructor_calls());
  }
}