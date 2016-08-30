/*
 * Created by keldon on 20/08/16.
 */

#ifndef PIOUS_PORT_HPP
#define PIOUS_PORT_HPP

namespace pious {

class Connection;
class Id;
class Device;
class Os;

class Port {
 public:
  Port(Os &os);

  void SetConnection(Connection &connection);
  const Connection* connection() const;
  Connection* connection();
  void SetDevice(Device &device);
  const Device* device() const;
  Device* device();
  void SetId(const Id &id);
  Id id() const;
};

}

#endif /* PIOUS_PORT_HPP */
