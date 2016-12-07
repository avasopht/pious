/*
 * Created by The Pious Authors on 10/10/16.
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

#include "connection_spec.hpp"

namespace pious {

ConnectionSpec::ConnectionSpec(emcee::Memory *memory)
  : source_device_(memory),
    source_port_(memory),
    dest_device_(memory),
    dest_port_(memory) { }

void ConnectionSpec::AddSourceDevice(const char *sid) { source_device_.SetSid(sid); }

void ConnectionSpec::AddSourceDevice(uint32_t iid) { source_device_.SetIid(iid); }

void ConnectionSpec::AddSourcePort(const char *sid) { source_port_.SetSid(sid); }

void ConnectionSpec::AddSourcePort(uint32_t iid) { source_port_.SetIid(iid); }

void ConnectionSpec::AddDestDevice(const char *sid) { dest_device_.SetSid(sid); }

void ConnectionSpec::AddDestDevice(uint32_t iid) { dest_device_.SetIid(iid); }

void ConnectionSpec::AddDestPort(const char *sid) { dest_port_.SetSid(sid); }

void ConnectionSpec::AddDestPort(uint32_t iid) { dest_port_.SetIid(iid); }

}