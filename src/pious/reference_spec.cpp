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

#include "reference_spec.hpp"

namespace pious {

ReferenceSpec::ReferenceSpec() : is_poly_device_(false) {

}

ReferenceSpec::ReferenceSpec(emcee::Memory * memory)
    : id_(memory), import_device_id_(memory), is_poly_device_(false) {}

void ReferenceSpec::SetSid(const char * sid) { id_.SetSid(sid); }

void ReferenceSpec::SetIid(uint32_t iid) { id_.SetIid(iid); }

void ReferenceSpec::SetImportDeviceSid(const char * sid) { import_device_id_.SetSid(sid); }

void ReferenceSpec::SetImportDeviceIid(uint32_t iid) { import_device_id_.SetIid(iid); }

void ReferenceSpec::SetPolyDevice(bool b) { is_poly_device_ = b; }

bool ReferenceSpec::is_poly_device() const { return is_poly_device_; }

Id ReferenceSpec::id() const { return id_; }

Id ReferenceSpec::import_id() const { return import_device_id_; }

}