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


TEST(Rack,CreateAndDelete) {
  emcee::DefaultMemory mem;
  emcee::UniquePtr<pious::MockDeviceManager> mock_manager(&mem, emcee::New<pious::MockDeviceManager>(&mem).Create());
  emcee::UniquePtr<pious::MockDevice> mock_device(&mem, emcee::New<pious::MockDevice>(&mem).Create());
  pious::Rack rack(&mem, mock_manager.get());

  EXPECT_CALL(*mock_manager,CreateDevice()).WillOnce(Return(mock_device.get()));
  EXPECT_CALL(*mock_device,parent()).WillOnce(Return(&rack));
  EXPECT_CALL(*mock_device,port_count()).WillOnce(Return(0));
  EXPECT_CALL(*mock_device,child_count()).WillOnce(Return(0));
  EXPECT_CALL(*mock_manager,DeleteDevice(mock_device.get())).Times(1);
  pious::Device * device = rack.CreateDevice();
  rack.RemoveDevice(device);
}

TEST(Rack,ChildOrdering) {
//  pious::MockDeviceManager device_manager;
//  pious::MockDevice device_1, device_2, device_3, device_4;
//  emcee::DefaultMemory mem;
//  pious::Rack rack(&mem, &device_manager);
//
//  EXPECT_CALL(device_manager,CreateDevice())
//      .WillOnce(Return(&device_1))
//      .WillOnce(Return(&device_2))
//      .WillOnce(Return(&device_3))
//      .WillOnce(Return(&device_4));
//  EXPECT_CALL(device_manager,DeleteDevice(&device_3));
//  EXPECT_CALL(device_1,port_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_2,port_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_3,port_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_4,port_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_1,child_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_2,child_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_3,child_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_4,child_count()).WillRepeatedly(Return(0));
//  EXPECT_CALL(device_1,parent()).WillRepeatedly(Return(&rack));
//  EXPECT_CALL(device_2,parent()).WillRepeatedly(Return(&rack));
//  EXPECT_CALL(device_3,parent()).WillRepeatedly(Return(&rack));
//  EXPECT_CALL(device_4,parent()).WillRepeatedly(Return(&rack));
//  ASSERT_EQ(rack.CreateDevice(), &device_1);
//  ASSERT_EQ(rack.CreateDevice(), &device_2);
//  ASSERT_EQ(rack.CreateDevice(), &device_3);
//  ASSERT_EQ(rack.CreateDevice(), &device_4);
//  ASSERT_EQ(&device_4, rack.DeviceAt(3));
//  rack.RemoveDevice(&device_3);
//  ASSERT_EQ(&device_4, rack.DeviceAt(2));
}
