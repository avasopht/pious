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

#include "port_spec.hpp"

namespace pious {

PortSpec::PortSpec() : id_(nullptr), io_type_(Pious_IoTypeNone) { }
PortSpec::PortSpec(emcee::Memory *m) : id_(m), io_type_(Pious_IoTypeNone) { }
void PortSpec::SetMemory(emcee::Memory *m) { id_.SetMemory(m); }
uint32_t PortSpec::iid() const { return id_.iid(); }
void PortSpec::SetIid(uint32_t id) { id_.SetIid(id); }
const char *PortSpec::sid_cstr() const { return id_.sid_cstr(); }
emcee::String PortSpec::sid() const { return id_.sid(); }
void PortSpec::SetSid(const char *sid) { id_.SetSid(sid); }
Pious_IoType PortSpec::io_type() const { return io_type_;}
void PortSpec::SetIoType(Pious_IoType io_type) { io_type_ = io_type; }
}