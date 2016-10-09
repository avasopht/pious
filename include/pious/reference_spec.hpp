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

#ifndef PIOUS_SPEC_REFERENCE_HPP
#define PIOUS_SPEC_REFERENCE_HPP

#include <emcee/string.hpp>
#include <emcee/memory_dependent.hpp>

namespace emcee {
class Memory;
}

namespace pious {

class ReferenceSpec : public virtual emcee::MemoryDependent {
 public:
  ReferenceSpec();
  ReferenceSpec(emcee::Memory &memory);
  ReferenceSpec(emcee::Memory &memory, const ReferenceSpec &other);

  void SetId(uint32_t id);
  uint32_t id() const;

  void SetImportDeviceId(uint32_t id);
  uint32_t import_device_id() const;

  void SetLabel(const char *label);
  void SetLabel(const emcee::String &label);
  const char* label_cstr() const;
  emcee::String label() const;

  void SetPolyDevice(bool b);
  bool is_poly_device() const;

  emcee::Memory* memory();

 private:
  /*! Unique id of reference */
  uint32_t id_;
  /*! Id of DeviceSpec this reference refers to. */
  uint32_t import_device_id_;
  /*! Label for this reference. */
  emcee::String label_;
  /*! Whether device is instantiated by polyphonic voice banks. */
  bool is_poly_device_;
};

}

#endif /* PIOUS_SPEC_REFERENCE_HPP */
