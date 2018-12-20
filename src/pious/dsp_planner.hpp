/*
 * Created by The Pious Authors on 27/04/2017.
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

#ifndef PIOUS_DSP_PLANNER_HPP
#define PIOUS_DSP_PLANNER_HPP

#include <cstddef>
#include <emcee/vector.hpp>
namespace emcee {
class Platform;
template<typename T> class Vector;
}

namespace pious {

class Device;
class DeviceContainer;

class DspPlanner : public virtual emcee::MemoryDependent {
 public:
  explicit DspPlanner(emcee::Platform * memory);
  void CreatePlan(DeviceContainer * container);
  int device_count() const;
  Device * DeviceAt(int index);

 private:
  emcee::Platform * memory_;
  emcee::Vector<Device*> dsp_plan_;

};

} /* pious */

#endif /* PIOUS_DSP_PLANNER_HPP */
