/*
 * Created by keldon on 30/09/16.
 */

#include "gtest/gtest.h"
#include "unique_ptr.hpp"
#include "memory.hpp"
#include "count_calls.hpp"

TEST(UniquePtr, creates_and_destroys) {
  pious::DefaultMemory memory;
  CountCalls::ClearCount();
  pious::UniquePtr<CountCalls> ptr (memory);
  ptr.Reset(pious::New<CountCalls>(memory).Create());
  ASSERT_EQ(1, CountCalls::constructor_calls());
  ASSERT_EQ(0, CountCalls::destructor_calls());
  {
    pious::UniquePtr<CountCalls> thief = ptr;
    (void) thief;
  }
  ASSERT_EQ(1, CountCalls::destructor_calls());
}