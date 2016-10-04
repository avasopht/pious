/*
 * Created by The Pious Authors on 20/08/2016.
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
