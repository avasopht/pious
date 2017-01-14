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


Pious_Db* PiousDb_Create() { return nullptr; }
Pious_Db* PiousDb_CreateChildDb(struct Pious_Db *db) { (void)db; return nullptr; }
void PiousDb_RemoveChildDb(struct Pious_Db *db, struct Pious_Db *child) {
  (void)db;
  (void)child;
}
Pious_DeviceSpec* PiousDb_FindDevice(struct Pious_Db *db, const char *id) {
  (void)db;
  (void)id;
  return nullptr;
}
size_t PiousDb_GetDeviceCount(const struct Pious_Db *db) {
  (void)db;
  return 0;
}
Pious_DeviceSpec* PiousDb_DeviceAt(struct Pious_Db *db, size_t idx){
  (void)db;
  (void)idx;
  return nullptr;
}

Pious_DeviceSpec* PiousDb_CreateDevice(struct Pious_Db *db, const char *id){
  (void)db;
  (void)id;
}