/*
 * Created by The Pious Authors on 06/10/16.
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

#ifndef PIOUS_DEVICE_SPEC_HPP
#define PIOUS_DEVICE_SPEC_HPP

#include <emcee/memory.hpp>
#include <emcee/vector.hpp>
#include <emcee/shared_ptr.hpp>
#include <emcee/string.hpp>

#include <api/pious_device.h>

namespace pious {

class ReferenceSpec;
class PortSpec;
class ConnectionSpec;

class DeviceSpec {
 public:
  virtual ~DeviceSpec() {}

  virtual emcee::String name() const = 0;

  virtual size_t device_count() const = 0;
  virtual ReferenceSpec* DeviceAt(size_t idx) = 0;

  virtual size_t connection_count() const = 0;
  virtual ConnectionSpec* ConnectionAt(size_t idx) = 0;

  virtual size_t port_count() const = 0;
  virtual PortSpec* PortAt(size_t idx) = 0;

  virtual Pious_UnitPlugin plugin() const = 0;

};

/*! \brief  Maintains specifications for a Device.
 */
class DeviceSpecBuilder : public virtual DeviceSpec {
 public:
  DeviceSpecBuilder(emcee::Memory &memory);

  void SetDeviceName(const char *name);

  ReferenceSpec* AddDevice();
  ReferenceSpec* AddDevice(uint32_t id, uint32_t import_device_id,
                           const emcee::String &label, bool is_poly = false);
  void SetDeviceAt(size_t idx, const ReferenceSpec &ref);
  size_t device_count() const override;
  ReferenceSpec* DeviceAt(size_t idx) override;

  ConnectionSpec* AddConnection();
  ConnectionSpec* AddConnection(PortSpec *source, PortSpec *dest);
  void SetConnectionAt(size_t idx, const ConnectionSpec &conn);
  size_t connection_count() const override;
  ConnectionSpec* ConnectionAt(size_t idx) override;

  PortSpec* AddPort();
  PortSpec* AddPort(uint32_t id, Pious_IoType io_type, const emcee::String &name);
  void SetPortAt(size_t idx, const PortSpec &spec_port);
  size_t port_count() const override;
  PortSpec* PortAt(size_t idx) override;

  void SetPlugin(const Pious_UnitPlugin &plugin);
  Pious_UnitPlugin plugin() const override;

 private:
  emcee::Memory *memory_;
  emcee::Vector<ReferenceSpec> devices_;
  emcee::Vector<PortSpec> ports_;
  emcee::Vector<ConnectionSpec> connections_;
  Pious_UnitPlugin plugin_;
  emcee::String name_;
};

}

#endif /* PIOUS_DEVICE_SPEC_HPP */
