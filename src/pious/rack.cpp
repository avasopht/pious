/*
 * Created by The Pious Authors on 25/04/2017.
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

#include "rack.hpp"
#include "device.hpp"
#include "device_manager.hpp"
#include <pious/port.hpp>

namespace pious {

size_t Rack::child_count() const {
  return devices_.size();
}

void Rack::AddChild(Device * device) {
  assert(false);
}

void Rack::RemoveChild(Device * child) {
  RemoveDevice(child);
}

Device * Rack::ChildAt(size_t idx) {
  if(idx < child_count())
    return devices_.At(idx).get();

  return nullptr;
}

bool Rack::IsChild(Device * device) const {
  return device && device->parent() == this;
}

Rack::Rack(emcee::Platform * memory, DeviceManager * device_manager)
  : memory_(memory), devices_(memory), device_manager_(device_manager) { }

Device * Rack::CreateDevice() {
  assert(device_manager_);

  Device * device = device_manager_->CreateDevice();
  assert(device);
  devices_.PushBack(emcee::SharedPtr<Device>(memory_, device));

  return device;
}

Device * Rack::CreateChildDevice(Device * parent) {
  assert(device_manager_);
  assert(parent);

  Device * device = device_manager_->CreateDevice();
  parent->AddChild(device);
  return device;
}

void Rack::RemoveDevice(Device * device) {
  assert(device && device->parent() == this);

  for(size_t i = 0; i < device->port_count(); ++i) {
    Port * port = device->PortAt(i);
    assert(port);
    port->Disconnect();
  }

  for(size_t i = 0; i < device->child_count(); ++i) {
    Device * child = device->ChildAt(i);
    assert(child);
    device->RemoveChild(child);
  }

  size_t device_index = GetDeviceIndex(device);
  devices_.EraseAt(device_index);
  device_manager_->DeleteDevice(device);
}

size_t Rack::device_count() const {
  return child_count();
}

Device * Rack::DeviceAt(size_t idx) {
  return ChildAt(idx);
}

size_t Rack::GetDeviceIndex(Device * device) const {
  for(size_t i = 0; i < device_count(); ++i) {
    if(devices_.At(i).get() == device)
      return i;
  }
  assert(false);
}

} /* pious */
