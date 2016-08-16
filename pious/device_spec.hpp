//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_DEVICE_SPEC_H
#define PIOUS_DEVICE_SPEC_H

#include "pious_device.h"
#include "vector.hpp"

#include <cinttypes>
#include <cstddef>

struct Pious_Allocator;

namespace pious {

class DeviceSpec {
 public:
  enum {
    kMaxDevices = 1024,
    kMaxConnections = 4096,
    kMaxPorts = 1024,
    kMaxAliases = 512
  };

  DeviceSpec(struct Pious_Allocator &allocator);

  void AddIo(enum Pious_UnitIoType io_type, uint64_t port_id);
  size_t io_count() const;
  size_t io_capacity() const;
  uint64_t PortIdAt(size_t index) const;
  enum Pious_UnitIoType PortTypeAt(size_t index) const;
  size_t FindPortIndex(uint64_t port_id) const;
  bool HasIoWithPortId(uint64_t port_id) const;
  size_t invalid_io_index() const;

  void AddDevice(uint64_t device_id, uint64_t ref_id);
  size_t device_count() const;
  uint64_t DeviceAt(size_t idx) const;
  uint64_t RefAt(size_t idx) const;
  size_t FindDeviceRefIndex(uint64_t ref_id);
  size_t invalid_device_index() const;

  /*!
   * \brief Connects ports of two child devices.
   *
   * \sa Connect
   */
  void Connect(uint64_t source_ref_id, uint64_t source_port_id,
               uint64_t dest_ref_id, uint64_t dest_port_id);

  size_t connection_count() const;
  uint64_t ConnectionSourceRefIdAt(size_t idx) const;
  uint64_t ConnectionSourcePortIdAt(size_t idx) const;
  uint64_t ConnectionDestRefIdAt(size_t idx) const;
  uint64_t ConnectionDestPortIdAt(size_t idx) const;
 private:
  struct Connection {
    Connection(uint64_t source_ref_id, uint64_t source_port_id, uint64_t dest_ref_id, uint64_t dest_port_id);

    bool operator==(const Connection &rhs) const;

    uint64_t source_ref_id;
    uint64_t source_port_id;
    uint64_t dest_ref_id;
    uint64_t dest_port_id;
  };

  struct Device {
    Device(uint64_t device_id, uint64_t device_ref);
    uint64_t device_id;
    uint64_t device_ref;
  };

  struct IoPort {
    IoPort(enum Pious_UnitIoType io_type, uint64_t port_id) : io_type(io_type), port_id(port_id) {}
    enum Pious_UnitIoType io_type;
    uint64_t port_id;
  };

  Pious_Allocator *allocator_;
  pious::Vector<Device> devices_;
  pious::Vector<IoPort> io_ports_;
  pious::Vector<Connection> connections_;

  bool HasRef(uint64_t id);
};

}

#endif //PIOUS_DEVICE_SPEC_H
