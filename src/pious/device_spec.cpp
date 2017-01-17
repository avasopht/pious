/*
 * Created by The Pious Authors on 10/10/16.
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

#include "device_spec.hpp"

#include "add_device.hpp"
#include "add_connection.hpp"
#include "id.hpp"
#include "port_spec.hpp"
#include "reference_spec.hpp"
#include "connection_spec.hpp"

namespace pious {

DeviceSpec::DeviceSpec(emcee::Memory *memory)
    : memory_(memory), plugin_(), id_(memory), devices_(memory), ports_(memory), connections_(memory) {
  if(memory)
    id_.New();
  plugin_.Init = nullptr;
  plugin_.Render = nullptr;
}

void DeviceSpec::AddPort(Pious_IoType io_type, const char *id, uint32_t iid) {
  PortSpec port(memory_);
  port.SetIoType(io_type);
  port.SetSid(id);
  port.SetIid(iid);
  ports_.PushBack(port);
}

void DeviceSpec::AddPort(Pious_IoType io_type, const char *id) {
  PortSpec port(memory_);
  port.SetIoType(io_type);
  port.SetSid(id);
  ports_.PushBack(port);
}

void DeviceSpec::AddPort(Pious_IoType io_type, uint32_t iid) {
  PortSpec port(memory_);
  port.SetIoType(io_type);
  port.SetIid(iid);
  ports_.PushBack(port);
}

pious::AddDevice DeviceSpec::AddDevice(const char *id) {
  ReferenceSpec device(memory_);
  device.SetSid(id);
  devices_.PushBack(device);
  return pious::AddDevice(&devices_.Back());
}

pious::AddDevice DeviceSpec::AddDevice(uint32_t iid) {
  ReferenceSpec device(memory_);
  device.SetIid(iid);
  devices_.PushBack(device);
  return pious::AddDevice(&devices_.Back());
}

pious::AddConnection DeviceSpec::AddConnection(const char *device_sid) {
  ConnectionSpec connection(memory_);
  connection.AddSourceDevice(device_sid);
  connections_.PushBack(connection);
  return pious::AddConnection(&connections_.Back());
}

pious::AddConnection DeviceSpec::AddConnection(uint32_t device_iid) {
  ConnectionSpec connection(memory_);
  connection.AddSourceDevice(device_iid);
  connections_.PushBack(connection);
  return pious::AddConnection(&connections_.Back());
}

size_t DeviceSpec::device_count() const {
  return devices_.size();
}

ReferenceSpec *DeviceSpec::DeviceAt(size_t idx) {
  assert(idx < devices_.size());
  if(idx < devices_.size()) {
    return &devices_.At(idx);
  }

  return nullptr;
}

size_t DeviceSpec::connection_count() const {
  return connections_.size();
}

ConnectionSpec *DeviceSpec::ConnectionAt(size_t idx) {
  assert(idx < connections_.size());

  if(idx < connections_.size()) {
    return &connections_.At(idx);
  }

  return nullptr;
}

void DeviceSpec::SetId(const char *sid, uint32_t iid) {
  SetId(sid);
  SetId(iid);
}

void DeviceSpec::SetId(const char *sid) {
  assert(id_);
  id_->SetSid(sid);
}

void DeviceSpec::SetId(uint32_t iid) {
  assert(id_);
  id_->SetIid(iid);
}

Pious_UnitPlugin DeviceSpec::plugin() const { return plugin_; }

void DeviceSpec::LoadPlugin(const Pious_UnitPlugin &plugin) { plugin_ = plugin; }

}
