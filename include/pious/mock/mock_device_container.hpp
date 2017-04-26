#ifndef PIOUS_MOCK_DEVICE_CONTAINER_HPP
#define PIOUS_MOCK_DEVICE_CONTAINER_HPP
#include "../device_container.hpp"
#include <gmock/gmock.h>
namespace pious {

class MockDeviceContainer : public DeviceContainer {
 public:
  MOCK_CONST_METHOD0(child_count,
      size_t());
  MOCK_METHOD1(AddChild,
      void(Device * device));
  MOCK_METHOD1(RemoveChild,
      void(Device * child));
  MOCK_METHOD1(ChildAt,
      Device*(size_t idx));
  MOCK_CONST_METHOD1(IsChild,
      bool(Device * device));
};

}  // namespace pious
#endif /* PIOUS_MOCK_DEVICE_CONTAINER_HPP */

