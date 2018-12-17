/*
 * Created by The Pious Authors on 15/04/2017.
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

#ifndef PIOUS_HOLD_SIGNAL_EVENT_HPP
#define PIOUS_HOLD_SIGNAL_EVENT_HPP

#include <cstddef>
#include <api/pious_device.h>
namespace pious {
class SignalHoldEvent {
 public:
  SignalHoldEvent() : frame_ (), old_value_(), new_value_() {}
  explicit SignalHoldEvent(const Pious_HoldSignalEvent &event)
      : frame_(event.offset)
      , old_value_(event.old_value)
      , new_value_(event.new_value) {}
  SignalHoldEvent(size_t frame, float old_value, float new_value)
      : frame_(frame), old_value_(old_value), new_value_(new_value) {}
  void SetFrame(size_t frame) { frame_ = frame; }
  void SetOldValue(float old_value) { old_value_ = old_value; }
  void SetNewValue(float new_value) { new_value_ = new_value; }
  size_t frame() const { return frame_; }
  float old_value() const { return old_value_; }
  float new_value() const { return new_value_; }
 private:
  size_t frame_;
  float old_value_;
  float new_value_;
};
}

#endif /* PIOUS_HOLD_SIGNAL_EVENT_HPP */
