//
// Created by keldon on 15/08/16.
//

#include "device_spec.hpp"
#include "pious_allocator.h"

namespace pious {

DeviceSpec::Connection::Connection(uint64_t source_ref_id, uint64_t source_port_id,
                                   uint64_t dest_ref_id, uint64_t dest_port_id)
    : source_ref_id(source_ref_id), source_port_id(source_port_id),
      dest_ref_id(dest_ref_id), dest_port_id(dest_port_id) {}

bool DeviceSpec::Connection::operator==(const DeviceSpec::Connection &rhs) const {
  return rhs.source_port_id == source_port_id &&
      rhs.source_ref_id == source_ref_id &&
      rhs.dest_port_id == dest_port_id &&
      rhs.dest_ref_id == dest_ref_id;
}

DeviceSpec::DeviceSpec(struct Pious_Allocator &allocator)
    : allocator_(&allocator),
      devices_(allocator, kMaxDevices),
      io_ports_(allocator, kMaxPorts),
      connections_(allocator, kMaxConnections) {
}

void DeviceSpec::AddIo(enum Pious_UnitIoType io_type, uint64_t port_id) {
  io_ports_.PushBack(IoPort(io_type, port_id));
}
uint64_t DeviceSpec::PortIdAt(size_t index) const {
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
    if (PortIdAt(i) == port_id)
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
uint64_t DeviceSpec::DeviceAt(size_t idx) const {
  assert(idx < devices_.size());
  return devices_.At(idx).device_id;
}
bool DeviceSpec::HasRef(uint64_t id) {
  return FindDeviceRefIndex(id) == invalid_device_index();
}
uint64_t DeviceSpec::RefAt(size_t idx) const {
  assert(idx < devices_.size());
  return devices_.At(idx).device_ref;
}

size_t DeviceSpec::FindDeviceRefIndex(uint64_t ref_id) {
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
uint64_t DeviceSpec::ConnectionSourceRefIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).source_ref_id;
}
uint64_t DeviceSpec::ConnectionSourcePortIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).source_port_id;
}
uint64_t DeviceSpec::ConnectionDestRefIdAt(size_t idx) const {
  assert(idx < connections_.size());
  return connections_.At(idx).dest_ref_id;
}
uint64_t DeviceSpec::ConnectionDestPortIdAt(size_t idx) const {
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

DeviceSpec::Device::Device(uint64_t device_id, uint64_t device_ref) :
    device_id(device_id), device_ref(device_ref) {}
}