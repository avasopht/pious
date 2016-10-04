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

#ifndef PIOUS_CONNECTION_HPP
#define PIOUS_CONNECTION_HPP

#include "pious_device.h"

#include <cstdlib>

namespace pious {

class Port;
class SignalBuffer;
class Id;
class Os;

class Connection {
 public:
  Connection(Os& os);

  const Port* source() const;
  Port* source();
  const Port* dest() const;
  Port* dest();
  Pious_UnitIoType io_type() const;
  Id id() const;

  size_t ReadSignal(float dest, size_t max_size) const;
  bool WriteSignal(const float *source, size_t size);
  size_t ReadSignalEvents(Pious_HoldSignalEvent *signal_events, size_t max_size) const;
  bool WriteSignalEvents(const Pious_HoldSignalEvent *signal_events, size_t size);
  size_t ReadPackets(Pious_DataPacket *data_packets, size_t max_size) const;
  bool WritePackets(const Pious_DataPacket *data_packets, size_t size);

};

}

#endif /* PIOUS_CONNECTION_HPP */
