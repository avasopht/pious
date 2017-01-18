/*
 * Created by The Pious Authors on 18/01/2017.
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
#include <emcee/emcee.hpp>
#include <api/pious_api.h>

TEST(PiousSpec,Basic) {
  Pious_Mem mem = emcee::PiousMem_CreateDefault();
  Pious_Db *db = PiousDb_Create(&mem);
  Pious_DeviceSpec *device_spec = PiousDb_CreateDevice(db, "Compressor");

  PiousSpec_AddDevicePort(device_spec, Pious_IoTypeSignalIn, "in");
  ASSERT_TRUE(PiousSpec_HasPort(device_spec, "in"));
  ASSERT_EQ(Pious_IoTypeSignalIn, PiousSpec_GetPortType(device_spec, "in"));

  PiousSpec_AddDevicePort(device_spec, Pious_IoTypeSignalOut, "out");
  ASSERT_TRUE(PiousSpec_HasPort(device_spec, "out"));
  ASSERT_EQ(Pious_IoTypeSignalOut, PiousSpec_GetPortType(device_spec, "out"));

  Pious_ReferenceSpec *gr = PiousSpec_AddDevice(device_spec, "com.avasopht.gain-reduction", "gr");
  ASSERT_EQ(gr, PiousSpec_FindDevice(device_spec, "gr"));
  PiousSpec_AddConnection(device_spec, "self", "in", "gr", "in");
  ASSERT_EQ(1, PiousSpec_ConnectionCount(device_spec));
  Pious_DeviceConnectionIds connection = PiousSpec_GetConnectionAt(device_spec, 0);
  ASSERT_STREQ("self", connection.source_device_id);
  ASSERT_STREQ("in", connection.source_device_port);
  ASSERT_STREQ("gr", connection.dest_device_id);
  ASSERT_STREQ("in", connection.dest_device_port);

  ASSERT_FALSE(PiousSpec_IsPolyphonic(device_spec, "gr"));
  PiousSpec_SetPolyphonic(device_spec, "gr", true);
  ASSERT_TRUE(PiousSpec_IsPolyphonic(device_spec, "gr"));
}