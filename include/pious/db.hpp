/*
 * Created by The Pious Authors on 06/04/2017.
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

#ifndef PIOUS_DB_HPP
#define PIOUS_DB_HPP

#include <emcee/map.hpp>

namespace emcee {
class String;
}

namespace pious {
class DeviceSpec;
}

struct Pious_Db { };

namespace pious {
class Db : public Pious_Db {
 public:
  Db() : mem(nullptr), parent(nullptr) {}

  Db(Pious_Mem * m);

  bool IsChild(const Db * child) const;

  ~Db();

  DeviceSpec * CreateDevice(const char * sid);
  DeviceSpec * FindDevice(const char * sid);

  void SetMemory(emcee::StructMemory * m);

  static Db * FromStruct(Pious_Db * db);

  void RemoveChildDb(Db * child);
  void RemoveFromParent();
  Db * CreateChildDb();

  size_t device_count() const { return devices.size(); }
  bool HasParent() const { return parent != nullptr; }

  struct Pious_Mem * GetMemStruct();

 private:

  emcee::StructMemory *mem;
  emcee::Map<emcee::String, emcee::SharedPtr<DeviceSpec>> devices;
  Db *parent;
  emcee::Vector<emcee::SharedPtr<Db> > children;
};

}

#endif /* PIOUS_DB_HPP */
