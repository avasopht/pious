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

#include <pious/signal_hold_channel.hpp>
#include <pious/signal_hold_event.hpp>
namespace pious {

SignalHoldChannel::SignalHoldChannel(emcee::Memory * memory, size_t event_count)
    : events_(memory) {
  events_.Reserve(event_count);
}

void SignalHoldChannel::AddEvent(size_t frame, float old_value, float new_value) {
  events_.PushBack(SignalHoldEvent(frame, old_value, new_value));
}

size_t SignalHoldChannel::WriteEvents(const struct SignalHoldEvent * signal_events, size_t event_count) {
  for (size_t i = 0; i < event_count; ++i) {
    SignalHoldEvent current_event(signal_events[i]);
    events_.PushBack(current_event);
  }
  return event_count;
}

void SignalHoldChannel::ClearEvents() {
  events_.Clear();
}

size_t SignalHoldChannel::ReadEvents(struct SignalHoldEvent * signal_events, size_t max_events) const {
  for (size_t i = 0; i < max_events && i < events_.size(); ++i) {
    SignalHoldEvent event = events_[i];
    signal_events[i] = {(uint32_t) event.frame(), event.old_value(), event.new_value()};
  }
  return std::min(max_events, events_.size());
}
}
