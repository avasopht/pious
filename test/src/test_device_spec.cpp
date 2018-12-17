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
#include <pious/pious.hpp>

TEST(DeviceSpec, Basic) {
  emcee::DefaultMemory mem;
  pious::DeviceSpec spec(&mem);

  ASSERT_EQ(0, spec.device_count());

  spec.SetId("com.avasopht.super-comp");
  ASSERT_STREQ("com.avasopht.super-comp", spec.id()->sid_cstr());

  spec.AddPort(Pious_IoTypeSignalOut, "in");
  ASSERT_EQ(1, spec.port_count());
  pious::PortSpec *in_port = spec.FindPort("in");
  ASSERT_TRUE(in_port);
  ASSERT_EQ("in", in_port->sid());

  spec.AddDevice("com.avasopht.gain-reduction").As("gr");
  pious::ReferenceSpec *gr = spec.FindDevice("gr");
  ASSERT_TRUE(gr);
  ASSERT_FALSE(gr->is_poly_device());
  gr->SetPolyDevice(true);
  ASSERT_TRUE(gr->is_poly_device());

  spec.AddConnection("self").Port("in").Dest("gr").Port("in");
  ASSERT_EQ(1, spec.connection_count());
  pious::ConnectionSpec *conn = spec.ConnectionAt(0);
  ASSERT_TRUE(conn);
  ASSERT_EQ("self", conn->source_device());
  ASSERT_EQ("in", conn->source_port());
  ASSERT_EQ("gr", conn->dest_device());
  ASSERT_EQ("in", conn->dest_port());
}
