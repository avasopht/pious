/*
 * Created by The Pious Authors on 28/04/2017.
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

#ifndef PIOUS_DEVICE_PATH_SEARCH_HPP
#define PIOUS_DEVICE_PATH_SEARCH_HPP

#include <emcee/vector.hpp>

namespace emcee {
class Platform;
}

namespace pious {

class Device;

class DevicePathSearch {
 public:
  DevicePathSearch(emcee::Platform * memory, Device * device);
  void AddConnectedDeviceFromPortAt(size_t port_idx);

  bool is_finished() const;
  Device * device() const;
  bool LoopIsDetected() const;
 private:
  emcee::Vector<Device*> path_;
  emcee::Vector<Device*>::Iterator iterator_;
  Device * device_;

  bool DeviceHasOutwardConnections() const;
};

}

#endif /* PIOUS_DEVICE_PATH_SEARCH_HPP */
