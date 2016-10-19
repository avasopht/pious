/*
 * Created by The Pious Authors on 20/10/16.
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <emcee/weak_count.hpp>
#include <emcee/shared_count.hpp>
#include <emcee/reference_counter.hpp>
#include <emcee/memory.hpp>
#include <emcee/new.hpp>
#include <emcee/deleter.hpp>

TEST(WeakCount,Basic) {
  class Tracker {
   public:
  };
  emcee::DefaultMemory mem;
  Tracker *ptr = emcee::New<Tracker>(mem).Create();
  emcee::Deleter *deleter = &emcee::New<emcee::TypedDeleter<Tracker>>(mem).Create()->Watch(ptr);
  emcee::ReferenceCounter *counter = emcee::New<emcee::ReferenceCounter>(mem).Create();
  {
    emcee::WeakCount outer_weak_count;
    {
      counter->SetDeleter(deleter);
      ASSERT_EQ(1, counter->use_count()) << "Setting a deleter should set use count to 1.";
      emcee::SharedCount shared_count(counter);
      outer_weak_count = shared_count;
      {
        {
          emcee::WeakCount weak_count(outer_weak_count);
          ASSERT_EQ(1, counter->use_count()) << "The weak count should not alter use count.";
          (void) weak_count;
        }
      }
    }
    ASSERT_EQ(0, counter->use_count());
    ASSERT_TRUE(counter->is_referenced()) << "Counter is still referenced by `outer_weak_count`.";
  }
  ASSERT_FALSE(counter->is_referenced()) << "There should be no references at this point.";
}