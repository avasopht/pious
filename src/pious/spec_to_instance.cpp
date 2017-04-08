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

#include <pious/spec_to_instance.hpp>
#include <emcee/map.hpp>
#include <emcee/vector.hpp>
#include <pious/id.hpp>
#include <pious/reference_spec.hpp>
#include <pious/spec_finder.hpp>
#include <pious/connection_spec.hpp>
#include <pious/port_instance.hpp>
#include <utility>
#include <pious/device_instance.hpp>
#include <pious/instance_factory.hpp>
#include <cassert>

namespace pious {

void SpecToInstance::Convert(SpecFinder * spec_finder, InstanceFactory * instance_factory, DeviceSpec * spec) {
  // CachedSpecFinder cached_spec_finder (spec_finder)

  emcee::Vector<DeviceInstance*> devices;
  emcee::Vector<std::pair<DeviceInstance*,DeviceSpec*>> open_list;

  devices.PushBack(instance_factory->CreateDevice());
  open_list.PushBack(std::pair<DeviceInstance*,DeviceSpec*>(devices.Front(), spec));

  while(!open_list.Empty()) {
    DeviceInstance * device = open_list.Front().first;
    DeviceSpec * spec = open_list.Front().second;

    CreatePorts(device, spec);
    for(size_t child_idx = 0; child_idx < spec->device_count(); ++child_idx) {
      ReferenceSpec * current_child = spec->DeviceAt(child_idx);
      Id id = current_child->import_id();
      DeviceSpec * child_spec = spec_finder->FindSpec(id.sid_cstr());
      assert(child_spec);
    }
  }
}
void SpecToInstance::ConnectChildren(emcee::Map<emcee::String, DeviceInstance *> devices,
                                     emcee::Vector<ConnectionSpec *> connections) {
  for(size_t connection_idx = 0; connection_idx < connections.size(); ++connection_idx) {
    ConnectionSpec * connection_spec = connections.At(connection_idx);
    assert(connection_spec);

    DeviceInstance * source_device = devices[connection_spec->source_device().sid()];
    assert(source_device);
    PortInstance * source_port = source_device->FindPort(connection_spec->source_port().sid_cstr());
    assert(source_port);

    DeviceInstance * dest_device = devices[connection_spec->dest_device().sid()];
    assert(dest_device);
    PortInstance * dest_port = source_device->FindPort(connection_spec->dest_port().sid_cstr());
    assert(dest_port);

    source_port->Connect(dest_port);
  }
}
void SpecToInstance::InstantiateChildren(emcee::Map<emcee::String, DeviceInstance *> children,
                                         SpecFinder * spec_finder,
                                         InstanceFactory * instance_factory,
                                         DeviceSpec * spec) {
  for(size_t child_idx = 0; child_idx < spec->device_count(); ++child_idx) {
    ReferenceSpec * child_ref = spec->DeviceAt(child_idx);
    assert(child_ref);
    emcee::String ref_id = child_ref->id().sid();
    DeviceSpec * spec = spec_finder->FindSpec(child_ref->import_id().sid_cstr());
    assert(spec);
    DeviceInstance * instance = instance_factory->CreateDevice();
    assert(instance);
    children[ref_id] = instance;
  }
}

void SpecToInstance::CreatePorts(DeviceInstance *instance, DeviceSpec *specs) {
  (void) instance;
  (void) specs;
  assert(false);
}

}