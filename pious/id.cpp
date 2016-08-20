//
// Created by keldon on 16/08/16.
//

#include "id.hpp"

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
