/*
 * Created by The Pious Authors on 28/04/2017.
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

#include <pious/device_path_search.hpp>
#include <pious/device.hpp>
#include <pious/port.hpp>

namespace pious {

DevicePathSearch::DevicePathSearch(emcee::Platform * memory, Device * device)
    : path_(memory), device_(device)
{
  iterator_ = path_.begin();
}

Device * DevicePathSearch::device() const {
  return device_;
}

bool DevicePathSearch::is_finished() const {
  return path_.Empty() ||
    !device() ||
    !DeviceHasOutwardConnections() ||
    LoopIsDetected();
}

bool DevicePathSearch::DeviceHasOutwardConnections() const {
  if(!device())
    return false;

  for(size_t i = 0; i < device_->port_count(); ++i) {
    if(Port::IsOutput(*device_->PortAt(i)) && device_->PortAt(i)->IsConnected())
      return true;
  }

  return false;
}

bool DevicePathSearch::LoopIsDetected() const {
  if(!device() || path_.Empty() || iterator_ == path_.cend())
    return false;

  return iterator_.value() == device_;
}

void DevicePathSearch::AddConnectedDeviceFromPortAt(size_t port_idx) {
  assert(device_);
  assert(device_->port_count() > port_idx);
  if(is_finished())
    return;

  Port * connected_port = device_->PortAt(port_idx);
  assert(connected_port);
  Device * connected_device = connected_port->device();
  assert(connected_device);

  path_.PushBack(connected_device);
  device_ = connected_device;

  bool is_even_device_index = path_.size() % 2 == 0;
  if(is_even_device_index && iterator_.value() != device_)
    ++iterator_;
}

} /* pious */
