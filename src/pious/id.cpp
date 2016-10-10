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

#include "id.hpp"

namespace pious {

Id::Id() : iid_(0) { }

Id::Id(emcee::Memory &memory) : sid_(memory), iid_(0) { }

Id::Id(emcee::String sid, uint32_t iid) : sid_(sid), iid_(iid) { }

Id::Id(emcee::String sid) : sid_(sid), iid_(0) { }

Id::Id(uint32_t iid) : iid_(iid) { }

void Id::SetSid(const char *sid) {
  assert(sid_.memory());
  sid_ = emcee::String(*sid_.memory(), sid);
}

void Id::SetSid(const emcee::String &sid) { sid_ = sid; }

void Id::SetIid(uint32_t iid) { iid_ = iid; }

const char *Id::sid_cstr() const { return sid_.c_str(); }

emcee::String Id::sid() const { return sid_; }

uint32_t Id::iid() const { return iid_; }


}