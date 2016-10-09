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

#include "reference_spec.hpp"

namespace pious {

ReferenceSpec::ReferenceSpec()
  : id_(0), import_device_id_(0), label_(), is_poly_device_(false) { }

ReferenceSpec::ReferenceSpec(emcee::Memory &memory)
  : id_(0), import_device_id_(0), label_(memory), is_poly_device_(false) {}

void ReferenceSpec::SetId(uint32_t id) { id_ = id; }

uint32_t ReferenceSpec::id() const { return id_; }

void ReferenceSpec::SetImportDeviceId(uint32_t id) { import_device_id_ = id; }

uint32_t ReferenceSpec::import_device_id() const { return import_device_id_; }

void ReferenceSpec::SetLabel(const char *label) {
  assert(label_.memory());
  label_ = emcee::String(*label_.memory(), label);
}

void ReferenceSpec::SetLabel(const emcee::String &label) { label_ = label; }

const char *ReferenceSpec::label_cstr() const { return label_.c_str(); }

emcee::String ReferenceSpec::label() const { return label_; }

void ReferenceSpec::SetPolyDevice(bool b) { is_poly_device_ = b; }

bool ReferenceSpec::is_poly_device() const { return false; }

emcee::Memory *ReferenceSpec::memory() { return label_.memory(); }

ReferenceSpec::ReferenceSpec(emcee::Memory&,
                             const ReferenceSpec &other)
  : id_(other.id_),
    import_device_id_(other.import_device_id_),
    label_(other.label_),
    is_poly_device_(other.is_poly_device_) { }

} // namespace pious

