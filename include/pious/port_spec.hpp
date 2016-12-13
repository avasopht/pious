/*
 * Created by The Pious Authors on 07/10/16.
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

#ifndef PIOUS_SPEC_PORT_HPP
#define PIOUS_SPEC_PORT_HPP

#include "id.hpp"

#include <emcee/string.hpp>
#include <emcee/memory_dependent.hpp>

#include <api/pious_device.h>

namespace emcee {
class Memory;
}

namespace pious {

/*! Stores details of a port for a Device Specification. */
class PortSpec : public virtual emcee::MemoryDependent {
 public:
  PortSpec() {};
  PortSpec(emcee::Memory *memory) {}

  uint32_t iid() const { return 0;  }
  void SetIid(uint32_t id) {};
  const char *sid_cstr() const { return 0; }
  emcee::String sid() const { return emcee::String(0); }
  void SetSid(const char *sid) {};
  Pious_IoType io_type() const { return Pious_IoTypeNone;  }
  void SetIoType(Pious_IoType io_type_) {}

 private:
  Id id_;
  Pious_IoType io_type_;
};

}

#endif /* PIOUS_SPEC_PORT_HPP */
