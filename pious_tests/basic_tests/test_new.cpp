/*
 * Created by keldon on 30/09/16.
 */

#include <gtest/gtest.h>
#include <emcee/new.hpp>
#include <emcee/memory.hpp>
#include "count_calls.hpp"


TEST(New, CallCount) {
  /*
   * Note beforehand: this tests for the number of times object construction
   * and destruction (etc.) methods are called, but in real life this should
   * not really matter. It is really sanity checking behavior.
   */

  {
    CountCalls::ClearCount();
    emcee::DefaultMemory memory;
    CountCalls *ptr = emcee::New<CountCalls[5]>(memory).Create();
    emcee::Delete(ptr);
    ASSERT_EQ(5, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::destructor_calls());
  }

  {
    CountCalls::ClearCount();
    emcee::DefaultMemory memory;
    CountCalls *def = emcee::New<CountCalls>(memory).Create();
    CountCalls *array = emcee::New<CountCalls[5]>(memory).Create(*def);
    emcee::Delete(def);
    emcee::Delete(array);

    ASSERT_EQ(1, CountCalls::constructor_calls());
    ASSERT_EQ(5, CountCalls::copy_calls());
    ASSERT_EQ(6, CountCalls::destructor_calls());
  }
}