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

#ifndef PIOUS_SPEC_FINDER_HPP
#define PIOUS_SPEC_FINDER_HPP

#include <emcee/map.hpp>

namespace emcee {
class String;
}

namespace pious {

class DeviceSpec;

class SpecFinder {
 public:
  virtual ~SpecFinder() = 0;
  virtual DeviceSpec * FindSpec(const char * sid) = 0;
};

class CachedSpecFinder : public SpecFinder {
 public:
  CachedSpecFinder(emcee::Memory * memory, SpecFinder * finder);
  DeviceSpec * FindSpec(const char * sid) override;

 private:
  emcee::Memory * memory_;
  SpecFinder * finder_;
  emcee::Map<emcee::String,DeviceSpec*> device_map_;

};

} // pious

#endif /* PIOUS_SPEC_FINDER_HPP */
