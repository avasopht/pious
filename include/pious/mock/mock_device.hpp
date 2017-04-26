#pragma once
#include "../device.hpp"
#include <emcee/string.hpp>
#include <gmock/gmock.h>
namespace pious {

class MockDevice : public Device {
 public:
  MOCK_CONST_METHOD0(has_dsp,
      bool());
  MOCK_METHOD0(GetInnerDevice,
      Device*());
  MOCK_METHOD1(SetLabel,
      void(const char * name));
  MOCK_CONST_METHOD0(label,
      const char*());
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
  MOCK_METHOD1(SetParent,
      void(DeviceContainer * parent));
  MOCK_METHOD0(parent,
      DeviceContainer*());
  MOCK_METHOD2(CreatePort,
      Port*(const char * id, Pious_IoType io_type));
  MOCK_METHOD1(PortAt,
      Port*(size_t index));
  MOCK_CONST_METHOD0(port_count,
      size_t());
  MOCK_METHOD1(FindPort,
      Port*(const char * id));
  MOCK_METHOD1(FindPort,
      Port*(const emcee::String & id));
};

}  // namespace pious
