/*
 * Created by The Pious Authors on 17/01/2017.
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
#include <api/pious_spec.h>
#include <api/pious_db.h>
#include <emcee/memory.hpp>

TEST(PiousDb,Basic) {
  Pious_Mem mem = emcee::PiousMem_CreateDefault();
  Pious_Db *db = PiousDb_Create(&mem);
  ASSERT_TRUE(db);

  {
    Pious_Db *child_db = PiousDb_CreateChildDb(db);
    ASSERT_TRUE(db);
    ASSERT_TRUE(PiousDb_IsChildDb(db, child_db));
    PiousDb_RemoveChildDb(db, child_db);
  }

  Pious_DeviceSpec *device = PiousDb_CreateDevice(db, "YoMama");
  ASSERT_EQ(1, PiousDb_GetDeviceCount(db));
  ASSERT_TRUE(device);
  ASSERT_EQ(device, PiousDb_FindDevice(db, "YoMama"));
}