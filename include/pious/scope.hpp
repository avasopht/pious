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

#ifndef PIOUS_SCOPE_HPP
#define PIOUS_SCOPE_HPP

#include <api/pious_device.h>
#include <cstdint>

struct Pious_HoldSignalEvent;
struct Pious_DataPacket;

namespace pious {

class PortInstance;


class Scope {
 public:
  virtual ~Scope() {}

  virtual void SetPluginDelay(float delay_in_samples) = 0;
  virtual Pious_Handle GetHandle(const char *object_uri) = 0;
  virtual bool IsValidHandle(const Pious_Handle *handle) = 0;
  virtual PortInstance* GetPort(const Pious_Handle *handle) = 0;
};

}

#endif /* PIOUS_SCOPE_HPP */
