/*
 * Created by The Pious Authors on 23/04/2017.
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

#ifndef PIOUS_DEVICE_CONTAINER_HPP
#define PIOUS_DEVICE_CONTAINER_HPP

#include <cstddef>
namespace pious {

class Device;

class DeviceContainer {
 public:
  virtual ~DeviceContainer() {}

  virtual size_t child_count() const = 0;
  virtual void AddChild(Device * device) = 0;
  virtual void RemoveChild(Device * child) = 0;
  virtual Device * ChildAt(size_t idx) = 0;
  virtual bool IsChild(Device * device) const = 0;
};
}

#endif /* PIOUS_DEVICE_CONTAINER_HPP */
