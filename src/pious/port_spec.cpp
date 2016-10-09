/*
 * Created by The Pious Authors on 09/10/16.
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

#include <api/pious_device.h>

namespace pious {

pious::PortSpec::PortSpec()
  : id_(0), io_type_(Pious_IoTypeNone), name_() { }

pious::PortSpec::PortSpec(emcee::Memory &memory)
  : id_(0), io_type_(Pious_IoTypeNone), name_(memory) { }

pious::PortSpec::PortSpec(emcee::Memory&, const PortSpec &other)
  : id_(0), io_type_(other.io_type_), name_(other.name_) { }

unsigned int pious::PortSpec::id() const {
  return id_;
}

void pious::PortSpec::SetId(unsigned int id_) {
  PortSpec::id_ = id_;
}

Pious_IoType pious::PortSpec::io_type() const {
  return io_type_;
}

void pious::PortSpec::SetIoType(Pious_IoType io_type_) {
  PortSpec::io_type_ = io_type_;
}

const emcee::String &pious::PortSpec::name() const {
  return name_;
}

void pious::PortSpec::SetName(const emcee::String &name_) {
  PortSpec::name_ = name_;
}

const char *PortSpec::name_cstr() const {
  return name_.c_str();
}

}