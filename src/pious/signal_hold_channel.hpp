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

#ifndef PIOUS_HOLD_SIGNAL_CHANNEL_HPP
#define PIOUS_HOLD_SIGNAL_CHANNEL_HPP

#include <cstddef>
#include <emcee/vector.hpp>
#include <api/pious_device.h>

namespace pious {

class SignalHoldEvent;

class SignalHoldChannel {
 public:
  SignalHoldChannel(emcee::Platform * memory, size_t event_count);
  void AddEvent(size_t frame, float old_value, float new_value);
  size_t WriteEvents(const SignalHoldEvent * signal_events, size_t event_count);
  void ClearEvents();
  size_t ReadEvents(SignalHoldEvent * signal_events, size_t max_events) const;
 private:
  emcee::Vector<SignalHoldEvent> events_;
};

}

#endif /* PIOUS_HOLD_SIGNAL_CHANNEL_HPP */
