/*
 * Created by The Pious Authors on 16/08/2016.
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

#include "pious/id.hpp"

#include <cstring>

pious::Id::Id() :
  iid_(kInvalidIid) {
  sid_[0] = '\0';
}
pious::Id::Id(const char *sid)
  : iid_(kInvalidIid)
{
  SetSid(sid);
}

pious::Id::Id(uint64_t iid, const char *sid)
  : iid_(kInvalidIid) {
  SetSid(sid);
}

void pious::Id::SetSid(const char *sid) {
  sid_[kMaxSidLength] = '\0';
  strncpy(sid_, sid, kMaxSidLength);
}
void pious::Id::SetIid(uint64_t iid) { iid_ = iid; }
const char *pious::Id::sid() const { return sid_; }
uint64_t pious::Id::iid() const { return iid_; }
bool pious::Id::operator==(const pious::Id &rhs) const {

  return &rhs == this ||
      (iid_ == rhs.iid_ && SidEquals(rhs.sid_));
}
bool pious::Id::Matches(const pious::Id &rhs) const {
  return &rhs == this || iid_ == rhs.iid_ || SidEquals(rhs.sid_);
}
bool pious::Id::SidEquals(const char *rhs_sid) const {
  // Ensure there is null termination before string comparison.
  return strcmp(sid_, rhs_sid) == 0;
}
pious::Id::Id(uint64_t iid)
  : iid_(iid) {
  sid_[0] = '\0';
}
pious::Id::Id(const pious::Id &other) {
  SetIid(other.iid());
  SetSid(other.sid());
}
pious::Id &pious::Id::operator=(const pious::Id &rhs) {
  if(&rhs == this) return *this;

  SetSid(rhs.sid());
  SetIid(rhs.iid());

  return *this;
}
