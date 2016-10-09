/*
 * Created by The Pious Authors on 09/10/16.
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

#ifndef PIOUS_DEVICE_HPP
#define PIOUS_DEVICE_HPP

#include <emcee/vector.hpp>
#include <emcee/shared_ptr.hpp>
#include <emcee/memory_dependent.hpp>

#include <cstddef>

namespace pious {

class DeviceSpec;
class Port;
class Scope;

class Device : public virtual emcee::MemoryDependent {
 public:
  Device(emcee::Memory &memory);
  Device(emcee::Memory &memory, const Device &other);

  DeviceSpec* device_spec();

  void Process(Scope *scope);

  Port* PortAt(size_t idx);
  size_t port_count() const;


 private:
  DeviceSpec *device_spec_;
  emcee::Vector<emcee::SharedPtr<Port>> ports_;
};

}

#endif /* PIOUS_DEVICE_HPP */
