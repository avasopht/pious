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

#ifndef PIOUS_ID_HPP
#define PIOUS_ID_HPP

#include <emcee/string.hpp>
#include <cstdint>

namespace pious {

class Id : public virtual emcee::MemoryDependent {
 public:
  Id();
  Id(emcee::Memory *memory);
  Id(emcee::String sid, uint32_t iid);
  Id(emcee::String sid);
  Id(uint32_t iid);

  Id& SetSid(const char *sid);
  Id& SetSid(const emcee::String &sid);
  Id& SetIid(uint32_t iid);

  const char* sid_cstr() const;
  emcee::String sid() const;
  uint32_t iid() const;

  int Compare(const Id &rhs) const;

 private:
  emcee::String sid_;
  uint32_t iid_;
};

}

#endif /* PIOUS_ID_HPP */
