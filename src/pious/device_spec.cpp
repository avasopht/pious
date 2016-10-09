/*
 * Created by The Pious Authors on 07/10/16.
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
#include "port_spec.hpp"
#include "reference_spec.hpp"
#include "connection_spec.hpp"

namespace pious {

DeviceSpecBuilder::DeviceSpecBuilder(emcee::Memory &memory)
  : memory_(&memory),
    devices_(memory),
    ports_(memory),
    connections_(memory),
    name_(memory)
{
  plugin_.Init = nullptr;
  plugin_.Render = nullptr;

}

void DeviceSpecBuilder::SetDeviceName(const char *name) {
  name_ = emcee::String(*memory_, name);
}

void DeviceSpecBuilder::SetDeviceAt(size_t idx, const ReferenceSpec &ref) {
  devices_.At(idx) = ref;
}

size_t DeviceSpecBuilder::device_count() const {
  return devices_.size();
}
void DeviceSpecBuilder::SetConnectionAt(size_t idx,
                                        const ConnectionSpec &conn) {
  connections_.At(idx) = conn;
}
size_t DeviceSpecBuilder::connection_count() const {
  return connections_.size();
}
void DeviceSpecBuilder::SetPortAt(size_t idx, const PortSpec &spec_port) {
  ports_.At(idx) = spec_port;
}
size_t DeviceSpecBuilder::port_count() const {
  return ports_.size();
}
void DeviceSpecBuilder::SetPlugin(const Pious_UnitPlugin &plugin) {
  plugin_ = plugin;
}
Pious_UnitPlugin DeviceSpecBuilder::plugin() const {
  return plugin_;
}

ReferenceSpec *DeviceSpecBuilder::AddDevice() {
  assert(memory_);
  ReferenceSpec *reference = emcee::New<ReferenceSpec>(*memory_).Create();
  return reference;
}

ReferenceSpec *DeviceSpecBuilder::AddDevice(uint32_t id,
                                            uint32_t import_device_id,
                                            const emcee::String &label,
                                            bool is_poly) {
  ReferenceSpec *reference = emcee::New<ReferenceSpec>(*memory_).Create();
  reference->SetId(id);
  reference->SetImportDeviceId(import_device_id);
  reference->SetLabel(label);
  reference->SetPolyDevice(is_poly);
  return reference;
}

ReferenceSpec *DeviceSpecBuilder::DeviceAt(size_t idx) {
  return &devices_.At(idx);
}

ConnectionSpec *DeviceSpecBuilder::AddConnection() {
  ConnectionSpec *connection = emcee::New<ConnectionSpec>(*memory_).Create();
  return connection;
}

ConnectionSpec *DeviceSpecBuilder::AddConnection(PortSpec *source,
                                                 PortSpec *dest) {
  ConnectionSpec *connection = emcee::New<ConnectionSpec>(*memory_).Create();
  connection->source = source;
  connection->dest = dest;
  return connection;
}

ConnectionSpec *DeviceSpecBuilder::ConnectionAt(size_t idx) {
  return &connections_.At(idx);
}

PortSpec *DeviceSpecBuilder::AddPort() {
  PortSpec *port = emcee::New<PortSpec>(*memory_).Create();
  return port;
}

PortSpec *DeviceSpecBuilder::AddPort(uint32_t id,
                                     Pious_IoType io_type,
                                     const emcee::String &name) {
  PortSpec *port = emcee::New<PortSpec>(*memory_).Create();
  port->SetId(id);
  port->SetIoType(io_type);
  port->SetName(name);
  return port;
}

PortSpec *DeviceSpecBuilder::PortAt(size_t idx) {
  return &ports_.At(idx);
}

}