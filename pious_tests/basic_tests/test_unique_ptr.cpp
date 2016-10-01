/*
 * Created by keldon on 30/09/16.
 */

#include <gtest/gtest.h>
#include <emcee/unique_ptr.hpp>
#include <emcee/memory.hpp>
#include "count_calls.hpp"

TEST(UniquePtr, creates_and_destroys) {
  emcee::DefaultMemory memory;
  CountCalls::ClearCount();
  emcee::UniquePtr<CountCalls> ptr (memory);
  ptr.Reset(emcee::New<CountCalls>(memory).Create());
  ASSERT_EQ(1, CountCalls::constructor_calls());
  ASSERT_EQ(0, CountCalls::destructor_calls());
  {
    emcee::UniquePtr<CountCalls> thief = ptr;
    (void) thief;
  }
  ASSERT_EQ(1, CountCalls::destructor_calls());
}