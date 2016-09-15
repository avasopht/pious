/*
 * Created by keldon on 20/08/16.
 */

#ifndef PIOUS_DEVICE_HPP
#define PIOUS_DEVICE_HPP

#include <cstdlib>
#include <pious_device.h>

namespace pious {

class Port;
class Id;
class DeviceSpec;
class Os;

class Device {
 public:
  Device(Os &os);

  void AddPort(Port *port);
  Port* GetInput(const Id &port_id);
  Port* GetOutput(const Id &port_id);
  size_t port_count() const;
  const Port* PortAt(size_t idx) const;
  Port* PortAt(size_t idx);

  // void AddChild()
  const Device* ChildAt(size_t idx) const;
  Device* ChildAt(size_t idx);
  const Device* FindChild(const Id &child_id) const;
  Device* FindChild(const Id &child_id);

  void SetPolyphonic(bool is_polyphonic);
  bool is_polyphonic() const;
};

}

#endif /* PIOUS_DEVICE_HPP */
