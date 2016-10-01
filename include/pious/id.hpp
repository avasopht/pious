//
// Created by keldon on 16/08/16.
//

#ifndef PIOUS_ID_H
#define PIOUS_ID_H

#include <cinttypes>

namespace pious {
class Id {
 public:
  enum {
    kMaxSidLength = 256,
    kInvalidIid = ~0x0ULL
  };

  Id();
  Id(const Id &other);
  explicit Id(const char *sid);
  explicit Id(uint64_t iid);
  Id(uint64_t iid, const char *sid);

  void SetSid(const char *sid);
  void SetIid(uint64_t iid);

  const char* sid() const;
  uint64_t iid() const;

  bool operator==(const Id& rhs) const;
  Id& operator=(const Id& rhs);

  bool Matches(const Id& rhs) const;

 private:
  uint64_t iid_;
  char sid_[kMaxSidLength + 1];
  bool SidEquals(const char *sid_) const;
};
}

#endif //PIOUS_ID_H
