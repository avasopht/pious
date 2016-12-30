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

#include <emcee/vector.hpp>
#include <emcee/shared_ptr.hpp>

#include <api/pious_device.h>

namespace emcee {
class Memory;
}

namespace pious {

class Id;
class AddConnection;
class AddConnectionPort;
class AddConnectionPortDest;
class AddDevice;
class ConnectionSpec;
class PortSpec;
class ReferenceSpec;


/*! \brief  Maintains specifications for a Device.
 */
class DeviceSpec {
 public:
  DeviceSpec(emcee::Memory *memory);

  void SetId(const char *sid, uint32_t iid);
  void SetId(const char *sid);
  void SetId(uint32_t iid);

  void AddPort(Pious_IoType io_type, const char *id, uint32_t iid);
  void AddPort(Pious_IoType io_type, const char *id);
  void AddPort(Pious_IoType io_type, uint32_t iid);

  pious::AddDevice AddDevice(const char *id);
  pious::AddDevice AddDevice(uint32_t iid);
  size_t device_count() const;
  ReferenceSpec* DeviceAt(size_t idx);

  pious::AddConnection AddConnection(const char *device_sid);
  pious::AddConnection AddConnection(uint32_t device_iid);
  size_t connection_count() const;
  ConnectionSpec* ConnectionAt(size_t idx);

  void LoadPlugin(const Pious_UnitPlugin &plugin);
  Pious_UnitPlugin plugin() const;

 private:
  emcee::Memory *memory_;
  Pious_UnitPlugin plugin_;
  emcee::UniquePtr<Id> id_;
  emcee::Vector<ReferenceSpec> devices_;
  emcee::Vector<PortSpec> ports_;
  emcee::Vector<ConnectionSpec> connections_;
};

}

#endif /* PIOUS_DEVICE_SPEC_HPP */
