/*
 * Created by The Pious Authors on 06/04/2017.
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

#include <pious/spec_to_devices.hpp>
#include <emcee/map.hpp>
#include <emcee/vector.hpp>
#include <pious/device_spec.hpp>
#include <pious/port_spec.hpp>
#include <pious/id.hpp>
#include <pious/reference_spec.hpp>
#include <pious/spec_finder.hpp>
#include <pious/connection_spec.hpp>
#include <pious/port.hpp>
#include <utility>
#include <pious/device.hpp>
#include <pious/instance_factory.hpp>
#include <cassert>

namespace pious {

Device * SpecToInstance::CreateInstance(SpecFinder * spec_finder,
                                                InstanceFactory * instance_factory,
                                                DeviceSpec * spec) {
  // CachedSpecFinder cached_spec_finder (spec_finder)

  Device * device = instance_factory->CreateDevice();

  CreatePorts(device, spec);
  emcee::Map<emcee::String, Device *> children;
  InstantiateChildren(&children, spec_finder, instance_factory, spec);
  emcee::Vector<ConnectionSpec *> connections;
  GetConnections(spec, &connections);
  ConnectChildren(&children, &connections);

  return device;
}

void SpecToInstance::ConnectChildren(emcee::Map<emcee::String, Device *> * devices,
                                     emcee::Vector<ConnectionSpec *> * connections) {
  for (size_t connection_idx = 0; connection_idx < connections->size(); ++connection_idx) {
    ConnectionSpec * connection_spec = connections->At(connection_idx);
    assert(connection_spec);

    Device * source_device = (*devices)[connection_spec->source_device().sid()];
    assert(source_device);
    Port * source_port = source_device->FindPort(connection_spec->source_port().sid());
    assert(source_port);

    Device * dest_device = (*devices)[connection_spec->dest_device().sid()];
    assert(dest_device);
    Port * dest_port = source_device->FindPort(connection_spec->dest_port().sid());
    assert(dest_port);

    source_port->Connect(dest_port);
  }
}

void SpecToInstance::InstantiateChildren(emcee::Map<emcee::String, Device *> * children,
                                         SpecFinder * spec_finder,
                                         InstanceFactory * instance_factory,
                                         DeviceSpec * spec) {
  for (size_t child_idx = 0; child_idx < spec->device_count(); ++child_idx) {
    ReferenceSpec * child_ref = spec->DeviceAt(child_idx);
    assert(child_ref);
    emcee::String ref_id = child_ref->id().sid();
    DeviceSpec * child_spec = spec_finder->FindSpec(child_ref->import_id().sid_cstr());
    assert(child_spec);
    Device * instance = instance_factory->CreateDevice();
    assert(instance);
    (*children)[ref_id] = instance;
  }
}

void SpecToInstance::CreatePorts(Device * instance, DeviceSpec * specs) {
  for (size_t port_idx = 0; port_idx < specs->port_count(); ++port_idx) {
    PortSpec * port_spec = specs->PortAt(port_idx);
    assert(port_spec);
    instance->CreatePort(port_spec->sid_cstr(), port_spec->io_type());
  }
}

void SpecToInstance::GetConnections(DeviceSpec * spec, emcee::Vector<ConnectionSpec *> * connections) {
  for (size_t i = 0; i < spec->connection_count(); ++i) {
    connections->PushBack(spec->ConnectionAt(i));
  }
}

} // pious