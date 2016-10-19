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

#include "reference_counter.hpp"
#include "deleter.hpp"

namespace emcee {

ReferenceCounter::ReferenceCounter(Deleter *deleter) {
  SetDeleter(deleter);
}

ReferenceCounter::ReferenceCounter() : deleter_(nullptr), shared_count_(0), weak_count_(0) { }

void ReferenceCounter::AddUse() {
  // If count is 0, there should be no object.
  assert(shared_count_ > 0);
  // If there is no deleter, there is nothing to reference count.
  assert(deleter_);

  ++shared_count_;
}

void ReferenceCounter::Release() {
  assert(shared_count_ > 0);

  --shared_count_;
  if(shared_count_ == 0) {
    Dispose();
    WeakRelease();
  }

}

void ReferenceCounter::Dispose() {
  if(!deleter_)
    return;

  deleter_->Delete();
  deleter_ = nullptr;
}

void ReferenceCounter::SetDeleter(Deleter *deleter) {
  Dispose();

  deleter_ = deleter;
  if(deleter) {
    shared_count_ = 1;
    weak_count_ = 1;
  }
}
void ReferenceCounter::WeakAddUse() {
  assert(weak_count_ > 0);
  ++weak_count_;
}
void ReferenceCounter::WeakRelease() {
  assert(weak_count_ > 0);
  --weak_count_;
}

}