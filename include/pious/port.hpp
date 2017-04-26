/*
 * Created by The Pious Authors on 07/04/2017.
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

#ifndef PIOUS_PORT_INSTANCE_HPP
#define PIOUS_PORT_INSTANCE_HPP
#include <api/pious_spec.h>

namespace pious {

class SignalHoldEvent;
class DataPacket;

class Port {
 public:
  virtual ~Port(){};
  virtual void Connect(Port * dest_port) = 0;
  virtual Pious_IoType io_type() const = 0;
  virtual void SetIoType(Pious_IoType io_type) = 0;
  virtual void Disconnect() = 0;

  virtual bool CanReadSignal() const = 0;
  /*! Reads signal into dest, returning number of frames read. */
  virtual size_t ReadSignal(float * dest, size_t max_samples) const = 0;
  virtual bool CanWriteSignal() const = 0;
  /*! Writes signal to port, returning number of frames written. */
  virtual size_t WriteSignal(const float * signal, size_t frame_count) = 0;
  virtual bool CanReadSignalEvents() const = 0;
  virtual size_t ReadSignalEvents(SignalHoldEvent * events, size_t max_events) const = 0;
  virtual float GetHoldSignalAt(size_t position) const = 0;
  virtual bool CanWriteSignalEvents() const = 0;
  virtual size_t WriteSignalEvents(const SignalHoldEvent * events, size_t event_count) = 0;
  virtual void ClearSignalEvents() = 0;
  virtual void ClearPackets() = 0;
  virtual bool CanReadPackets() const = 0;
  virtual size_t ReadPackets(DataPacket * dest, size_t max_packet_count) const = 0;
  virtual bool CanWritePackets() const = 0;
  virtual size_t WritePackets(const DataPacket * packets, size_t packet_count) = 0;
};


}

#endif /* PIOUS_PORT_INSTANCE_HPP */
