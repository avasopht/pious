/*
 * Created by keldon on 30/09/16.
 */

#include <gtest/gtest.h>
#include <pious/new.hpp>
#include <pious/memory.hpp>
#include "count_calls.hpp"


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