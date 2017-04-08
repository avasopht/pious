/*
 * Created by The Pious Authors on 07/04/2017.
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

#include <pious/spec_finder.hpp>
#include <emcee/string.hpp>

namespace pious {

SpecFinder::~SpecFinder() {}

CachedSpecFinder::CachedSpecFinder(emcee::Memory * memory, SpecFinder * finder)
    : memory_(memory), finder_(finder), device_map_(memory) {}

DeviceSpec * CachedSpecFinder::FindSpec(const char * sid) {
  emcee::String id (memory_, sid);
  if(device_map_.ContainsKey(id)) {
    return device_map_[id];
  }

  DeviceSpec * spec = finder_->FindSpec(sid);
  if(spec)
    device_map_[id] = spec;
  return spec;
}

} // pious
