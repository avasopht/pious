/*
 * Created by keldon on 20/08/16.
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
