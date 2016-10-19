/*
 * Created by The Pious Authors on 04/10/16.
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

#include "new.hpp"
#include "shared_count.hpp"

namespace emcee {

SharedCount::SharedCount() : counter_(nullptr) {

}

SharedCount::SharedCount(const SharedCount &other) : counter_(nullptr) {
  ImportCounter(other);
}
void SharedCount::ImportCounter(const SharedCount &other) {
  counter_ = other.counter_;
  AddUse();
}

SharedCount::SharedCount(ReferenceCounter *counter) : counter_(counter) {
}

void SharedCount::AddUse() {
  if(counter_) {
    counter_->AddUse();
  }
}

SharedCount::~SharedCount() {
  Release();
}
void SharedCount::Release() {
  if(counter_) {

    counter_->Release();

    if(counter_->is_unused()) {
      emcee::Delete(counter_);
    }

    counter_ = nullptr;
  }
}

SharedCount &SharedCount::operator=(const SharedCount &rhs) {
  if(rhs.counter_ == counter_) return *this;

  Release();
  ImportCounter(rhs);

  return *this;
}
size_t SharedCount::use_count() const {
  if(counter_)
    return counter_->use_count();

  return 0;
}

}

