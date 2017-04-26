#ifndef PIOUS_MOCK_DEVICE_MANAGER_HPP
#define PIOUS_MOCK_DEVICE_MANAGER_HPP
#include <gmock/gmock.h>
#include "../device_manager.hpp"
namespace pious {

class MockDeviceManager : public DeviceManager {
 public:
  MOCK_METHOD0(CreateDevice,
      Device*());
  MOCK_METHOD1(DeleteDevice,
      void(Device * d));
};

}  // namespace pious
#endif // PIOUS_MOCK_DEVICE_MANAGER_HPP

