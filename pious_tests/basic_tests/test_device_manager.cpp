/*
 * Created by The Pious Authors on 25/04/2017.
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <emcee/memory.hpp>
#include <pious/rack.hpp>
#include <pious/device_manager.hpp>
#include <pious/mock/mock_device_manager.hpp>
#include <pious/mock/mock_device.hpp>
using ::testing::Return;
using ::testing::_;


TEST(DeviceManager,DeviceMock) {
  pious::MockDeviceManager mock_manager;
  pious::MockDevice mock_device;
  EXPECT_CALL(mock_manager,DeleteDevice(nullptr)).Times(1);
  mock_manager.DeleteDevice(nullptr);
  emcee::DefaultMemory mem;
  pious::Rack rack(&mem, &mock_manager);

  EXPECT_CALL(mock_manager,CreateDevice()).WillRepeatedly(Return(&mock_device));
  EXPECT_CALL(mock_device,parent()).WillRepeatedly(Return(&rack));
  EXPECT_CALL(mock_device,port_count()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(mock_device,child_count()).Times(1).WillOnce(Return(0));
  pious::Device * device = rack.CreateDevice();
  rack.RemoveDevice(device);
}
