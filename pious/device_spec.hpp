//
// Created by keldon on 12/08/16.
//

#ifndef PIOUS_DEVICE_SPEC_H
#define PIOUS_DEVICE_SPEC_H

#include "pious_device.h"
#include "vector.hpp"
#include "id.hpp"
#include "unique_ptr.hpp"

#include <cinttypes>
#include <cstddef>

struct Pious_Allocator;

namespace pious {

class Id;
class Os;

class DeviceSpec {
 public:
  enum {
    kMaxDevices = 1024,
    kMaxConnections = 4096,
    kMaxPorts = 1024,
    kMaxAliases = 512
  };

  DeviceSpec(Os &os);

  void LoadPlugin(Pious_UnitPlugin *plugin);

  void AddIo(enum Pious_UnitIoType io_type, uint64_t port_id);
  void AddIo(enum Pious_UnitIoType io_type, const Id &id);
  void AddIo(enum Pious_UnitIoType io_type, const char *port_id);
  size_t io_count() const;
  size_t io_capacity() const;
  Id PortIdAt(size_t index) const;
  enum Pious_UnitIoType PortTypeAt(size_t index) const;
  size_t FindPortIndex(uint64_t port_id) const;
  bool HasIoWithPortId(uint64_t port_id) const;
  size_t invalid_io_index() const;

  void SetDevicePolyphonic(uint64_t ref_id, bool is_polyphonic);
  void AddDevice(uint64_t device_id, uint64_t ref_id);
  size_t device_count() const;
  Id DeviceAt(size_t idx) const;
  Id RefAt(size_t idx) const;
  bool HasRef(uint64_t id) const;
  size_t FindDeviceRefIndex(uint64_t ref_id) const;
  size_t invalid_device_index() const;

  /*!
   * \brief Connects ports of two child devices.
   *
   * \sa Connect
   */
  void Connect(uint64_t source_ref_id, uint64_t source_port_id,
               uint64_t dest_ref_id, uint64_t dest_port_id);

  size_t connection_count() const;
  Id ConnectionSourceRefIdAt(size_t idx) const;
  Id ConnectionSourcePortIdAt(size_t idx) const;
  Id ConnectionDestRefIdAt(size_t idx) const;
  Id ConnectionDestPortIdAt(size_t idx) const;
 private:

  struct Connection {
    Connection(const Id &source_ref_id,
                   const Id &source_port_id,
                   const Id &dest_ref_id,
                   const Id &dest_port_id);

    bool operator==(const Connection &rhs) const;

    Id source_ref_id;
    Id source_port_id;
    Id dest_ref_id;
    Id dest_port_id;
  };

  struct Device {
    Device(const Id &device_id, const Id &device_ref);
    Id device_id;
    Id device_ref;
    bool is_polyphonic;
  };

  struct IoPort {
    IoPort(enum Pious_UnitIoType io_type, const Id &port_id) : io_type(io_type), port_id(port_id) {}
    enum Pious_UnitIoType io_type;
    Id port_id;
  };

  typedef ScopedPtr<Device> DevicePtr;
  typedef ScopedPtr<Connection> ConnectionPtr;
  typedef ScopedPtr<IoPort> IoPortPtr;

  Os &os_;
  pious::Vector<DevicePtr> devices_;
  pious::Vector<IoPortPtr> io_ports_;
  pious::Vector<ConnectionPtr> connections_;
  Pious_UnitPlugin *plugin_;
};

}

#endif //PIOUS_DEVICE_SPEC_H
