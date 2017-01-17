/*
 * Created by The Pious Authors on 26/09/2016.
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

#include <cstdlib>
#include <emcee/memory.hpp>
#include <api/pious_sys.h>




namespace emcee {

static void* DefaultAlloc(void*, size_t size) { return malloc(size); }
static void DefaultFree(void*, void *ptr) { free(ptr); }

Pious_Mem PiousMem_CreateDefault() {
  Pious_Mem def { DefaultAlloc, DefaultFree};
  return def;
}

void *DefaultMemory::Allocate(size_t size) {
  return malloc(size);
}

void DefaultMemory::Free(void *ptr) {
  free(ptr);
}

void *StructMemory::Allocate(size_t size) {
  if(!mem_.Alloc)
    return nullptr;
  return mem_.Alloc(mem_.data, size);
}
void StructMemory::Free(void *ptr) {
  if(mem_.Free)
    mem_.Free(mem_.data, ptr);
}


}