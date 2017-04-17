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

#ifndef PIOUS_DEVICE_INSTANCE_HPP
#define PIOUS_DEVICE_INSTANCE_HPP

#include <cstddef>

namespace emcee {
class String;
}

namespace pious {

class PortInstance;

class DeviceInstance {
 public:
  virtual ~DeviceInstance(){};

  virtual bool has_dsp() const = 0;

  /*! Returns inner device that connects to its children. */
  virtual DeviceInstance * GetInnerDevice() = 0;

  virtual void SetLabel(const char * name) = 0;
  virtual const char * label() const = 0;

  virtual void AddChild(DeviceInstance * child) = 0;
  virtual void RemoveChild(DeviceInstance * child) = 0;
  virtual DeviceInstance * ChildAt(size_t index) = 0;
  virtual size_t child_count() const = 0;
  virtual PortInstance * CreatePort(const char * id, Pious_IoType io_type) = 0;
  virtual PortInstance * PortAt(size_t index) = 0;
  virtual size_t port_count() const = 0;
  virtual PortInstance * FindPort(const char * id) = 0;
  virtual PortInstance * FindPort(const emcee::String & id) = 0;
};

}

#endif /* PIOUS_DEVICE_INSTANCE_HPP */
