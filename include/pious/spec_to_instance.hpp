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

#ifndef PIOUS_SPEC_TO_INSTANCE_HPP
#define PIOUS_SPEC_TO_INSTANCE_HPP

#include <pious/spec_to_instance.hpp>
#include <pious/device_spec.hpp>
#include <emcee/shared_ptr.hpp>
#include <emcee/vector.hpp>
#include <emcee/map.hpp>

namespace emcee {
class String;
}

namespace pious {

class DeviceSpec;
class SpecFinder;
class InstanceFactory;
class DeviceInstance;
class ConnectionSpec;

class SpecToInstance {
 public:
  static void Convert(SpecFinder * spec_finder, InstanceFactory * instance_factory, DeviceSpec * spec);
  static void CreatePorts(DeviceInstance * instance, DeviceSpec * specs);
  static void InstantiateChildren(emcee::Map<emcee::String,DeviceInstance*> children, SpecFinder * spec_finder,
                                                                       InstanceFactory * instance_factory,
                                                                       DeviceSpec * spec);
  static void ConnectChildren(emcee::Map<emcee::String,DeviceInstance*>,emcee::Vector<ConnectionSpec*> connections);
};

}

#endif /* PIOUS_SPEC_TO_INSTANCE_HPP */
