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
