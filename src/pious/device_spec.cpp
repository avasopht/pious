/*
 * Created by The Pious Authors on 15/08/2016.
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

#include "pious/device_spec.hpp"

namespace pious {

DeviceSpec::Connection::Connection(const Id &source_ref_id,
                                   const Id &source_port_id,
                                   const Id &dest_ref_id,
                                   const Id &dest_port_id)
  : source_ref_id(source_ref_id),
    source_port_id(source_port_id),
    dest_ref_id(dest_ref_id),
    dest_port_id(dest_port_id) { }

bool DeviceSpec::Connection::operator==(const DeviceSpec::Connection &rhs) const {
  return rhs.source_port_id == source_port_id &&
      rhs.source_ref_id == source_ref_id &&
      rhs.dest_port_id == dest_port_id &&
      rhs.dest_ref_id == dest_ref_id;
}

DeviceSpec::DeviceSpec(Os &os)
    : os_(os),
      devices_(os, kMaxDevices),
      io_ports_(os, kMaxPorts),
      connections_(os, kMaxConnections) {
}

void DeviceSpec::AddIo(enum Pious_UnitIoType io_type, uint64_t port_id) {
  io_ports_.PushBack(IoPortPtr(os_, new IoPort(io_type, Id(port_id))));
}
Id DeviceSpec::PortIdAt(size_t index) const {
  assert(index < io_ports_.size());
  return io_ports_.At(index).port_id;
}
size_t DeviceSpec::io_count() const {
  return io_ports_.size();
}

enum Pious_UnitIoType DeviceSpec::PortTypeAt(size_t index) const {
  assert(index < io_ports_.size());
  return io_ports_.At(index).io_type;
}

size_t DeviceSpec::FindPortIndex(uint64_t port_id) const {
  for (size_t i = 0; i < io_ports_.size(); ++i) {
    if (PortIdAt(i).Matches(port_id))
      return i;
  }
  return invalid_io_index();
}
size_t DeviceSpec::io_capacity() const {
  return io_ports_.capacity();
}
void DeviceSpec::AddDevice(uint64_t device_id, uint64_t ref_id) {
  if (HasRef(ref_id))
    return;

  Device device (device_id, ref_id);
  devices_.PushBack(device);
}
size_t DeviceSpec::device_count() const {
  return devices_.size();
}
bool DeviceSpec::HasIoWithPortId(uint64_t port_id) const {
  return FindPortIndex(port_id) == invalid_io_index();
}
Id DeviceSpec::DeviceAt(size_t idx) const {
  assert(idx < devices_.size());
  return devices_.At(idx).device_id;
}
bool DeviceSpec::HasRef(uint64_t id) const {
  return FindDeviceRefIndex(id) == invalid_device_index();
}
Id DeviceSpec::RefAt(size_t idx) const {
  assert(idx < devices_.size());
  return devices_.At(idx).device_ref;
}

size_t DeviceSpec::FindDeviceRefIndex(uint64_t ref_id) const {
  for (size_t i = 0; i < devices_.size(); ++i) {
    if (devices_.At(i).device_ref == ref_id)
      return i;
  }

  return invalid_device_index();
}
size_t DeviceSpec::invalid_io_index() const {
  return io_ports_.capacity();
}
size_t DeviceSpec::invalid_device_index() const {
  return devices_.capacity();
}
size_t DeviceSpec::connection_count() const {
  return connections_.size();
}
Id DeviceSpec::ConnectionSourceRefIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).source_ref_id;
}
Id DeviceSpec::ConnectionSourcePortIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).source_port_id;
}
Id DeviceSpec::ConnectionDestRefIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).dest_ref_id;
}
Id DeviceSpec::ConnectionDestPortIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).dest_port_id;
}
void DeviceSpec::Connect(uint64_t source_ref_id, uint64_t source_port_id, uint64_t dest_ref_id, uint64_t dest_port_id) {
  Connection new_connection(source_ref_id, source_port_id, dest_ref_id, dest_port_id);

  // Return if connection already exists.
  for (size_t i = 0; i < connections_.size(); ++i) {
    if (connections_.At(i) == new_connection)
      return;
  }

  connections_.PushBack(new_connection);
}
void DeviceSpec::SetDevicePolyphonic(uint64_t ref_id, bool is_polyphonic) {
  for(size_t i = 0; i < devices_.size(); ++i) {
    if(devices_.At(i).device_ref == ref_id) {
      devices_.At(i).is_polyphonic = is_polyphonic;
      return;
    }
  }
}
void DeviceSpec::LoadPlugin(Pious_UnitPlugin *plugin) {
  plugin_ = plugin;
}
void DeviceSpec::AddIo(enum Pious_UnitIoType io_type, const Id &id) {

}

DeviceSpec::Device::Device(const Id &device_id, const Id &device_ref) :
    device_id(device_id), device_ref(device_ref), is_polyphonic(false) {}
}