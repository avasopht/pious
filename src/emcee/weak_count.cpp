/*
 * Created by The Pious Authors on 19/10/16.
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

#include "weak_count.hpp"
#include "shared_count.hpp"
#include "reference_counter.hpp"
#include "new.hpp"

namespace emcee {

WeakCount::WeakCount() : counter_(nullptr) { }


WeakCount::WeakCount(const WeakCount &rhs) : counter_(nullptr) {
  ImportCounter(rhs);
}


WeakCount::WeakCount(const SharedCount &shared_count) : counter_(nullptr){
  ImportCounter(shared_count);
}


WeakCount::~WeakCount() {
  Release();
}


WeakCount &WeakCount::operator=(const WeakCount &rhs) {
  if(this == &rhs) return *this;

  Release();
  ImportCounter(rhs);

  return *this;
}


WeakCount &WeakCount::operator=(const SharedCount &shared_count) {
  Release();
  ImportCounter(shared_count);
  return *this;
}


size_t WeakCount::use_count() const {
  if(!counter_) {
    return 0;
  }

  return counter_->use_count();
}


ReferenceCounter* WeakCount::counter() const { return counter_; }


void WeakCount::Release() {
  if(counter_) {
    counter_->WeakRelease();

    if(!counter_->is_referenced()) {
      emcee::Delete(counter_);
    }

    counter_ = nullptr;
  }
}


void WeakCount::AddUse() {
  if(counter_) {
    counter_->WeakAddUse();
  }
}


void WeakCount::ImportCounter(const SharedCount &count) {
  Release();
  counter_ = count.counter();
  AddUse();
}


void WeakCount::ImportCounter(const WeakCount &count) {
  Release();
  counter_ = count.counter();
  AddUse();
}

}