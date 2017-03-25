/*
 * Created by The Pious Authors on 11/01/2017.
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

#include <api/pious_spec.h>
#include <api/pious_sys.h>
#include <api/pious_db.h>
#include <emcee/memory.hpp>
#include <emcee/map.hpp>
#include <emcee/emcee.hpp>
#include <pious/port_spec.hpp>
#include <pious/device_spec.hpp>
#include <pious/reference_spec.hpp>
#include <pious/connection_spec.hpp>

struct Pious_Db { };

namespace pious {
struct Db : public Pious_Db {
  Db() : mem(nullptr), parent(nullptr) {}

  Db(Pious_Mem *m) : mem(nullptr), parent(nullptr) {
    emcee::StructMemory *sm = new(m->Alloc(m->data,sizeof(emcee::StructMemory)))emcee::StructMemory(m);
    SetMemory(sm);
  }

  bool IsChild(const Db *child) const {
    for(size_t i = 0; i < children.size(); ++i) {
      if(children[i].get() == child)
        return true;
    }

    return false;
  }

  ~Db() {
    if(!parent && mem) {
      Pious_Mem *m = mem->mem_struct();
      mem->~StructMemory();
      m->Free(m->data, mem);
    }
  }

  DeviceSpec* CreateDevice(const char *sid) {
    DeviceSpec *spec = emcee::New<DeviceSpec>(mem).Create();
    spec->SetId(sid);
    devices[emcee::String (mem, sid)] = emcee::SharedPtr<DeviceSpec>(mem, spec);
    return spec;
  }

  void SetMemory(emcee::StructMemory *m) {
    mem = m;
    devices.SetMemory(m);
    children.SetMemory(m);
  }

  static Db* FromStruct(Pious_Db *db) {
    return static_cast<Db*>(db);
  }

  emcee::StructMemory *mem;
  emcee::Map<emcee::String,emcee::SharedPtr<DeviceSpec>> devices;
  Db *parent;
  emcee::Vector<emcee::SharedPtr<Db> > children;

  void RemoveChildDb(Db *child) {
    for(int i = 0; i < children.size(); ++i) {
      if(children[i].get() == child) {
        children.EraseAt(i);
        return;
      }
    }
  }

  void RemoveFromParent() {
    if(parent) {
      parent->RemoveChildDb(this);
    }
  }

  Db* CreateChildDb() {
    Db *child = emcee::New<Db>(mem).Create();
    child->SetMemory(mem);
    child->parent = this;
    emcee::SharedPtr<Db> ptr (mem, child);
    children.PushBack(ptr);
    return child;
  }
};

} // namespace pious

Pious_Db* PiousDb_Create(struct Pious_Mem *mem) {
  pious::Db *db = new(mem->Alloc(mem->data, sizeof(pious::Db)))pious::Db(mem);
  return db;
}

void PiousDb_DestroyDb(struct Pious_Db *s_db) {
  assert(s_db);
  pious::Db *db = static_cast<pious::Db*>(s_db);
  if(db->parent) {
    db->RemoveFromParent();
  } else {
    Pious_Mem *mem_struct = db->mem->mem_struct();
    db->~Db();
    mem_struct->Free(mem_struct->data, s_db);
  }
}

Pious_Db* PiousDb_CreateChildDb(struct Pious_Db *s_db) {
  assert(s_db);
  return static_cast<pious::Db*>(s_db)->CreateChildDb();
}


bool PiousDb_IsChildDb(const struct Pious_Db *db, const struct Pious_Db *child) {
  return static_cast<const pious::Db*>(db)->IsChild(static_cast<const pious::Db*>(child));
}

void PiousDb_RemoveChildDb(struct Pious_Db *sdb, struct Pious_Db *schild) {
  assert(sdb);
  assert(schild);
  pious::Db *db = static_cast<pious::Db*>(sdb);
  pious::Db *child = static_cast<pious::Db*>(schild);
  db->RemoveChildDb(child);
}
Pious_DeviceSpec* PiousDb_FindDevice(struct Pious_Db *sdb, const char *cid) {
  assert(sdb);
  pious::Db *db = static_cast<pious::Db*>(sdb);
  emcee::String sid(db->mem, cid);
  return db->devices[sid].get();
}
size_t PiousDb_GetDeviceCount(const struct Pious_Db *db) {
  return static_cast<const pious::Db*>(db)->devices.size();
}

Pious_DeviceSpec* PiousDb_CreateDevice(struct Pious_Db *db, const char *id){
  return static_cast<pious::Db*>(db)->CreateDevice(id);
}