/*
 * Created by The Pious Authors on 07/10/16.
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

#ifndef PIOUS_CONNECTION_HPP
#define PIOUS_CONNECTION_HPP

#include "id.hpp"
#include <cstdint>

namespace emcee {
class Memory;
}

namespace pious {

/*! Stores details for a connection between ports in a device specification. */
class ConnectionSpec {
 public:
  ConnectionSpec(emcee::Memory *memory);

  void AddSourceDevice(const char *sid);
  void AddSourceDevice(uint32_t iid);
  void AddSourcePort(const char *sid);
  void AddSourcePort(uint32_t iid);
  void AddDestDevice(const char *sid);
  void AddDestDevice(uint32_t iid);
  void AddDestPort(const char *sid);
  void AddDestPort(uint32_t iid);

  Id source_device() const;
  Id source_port() const;
  Id dest_device() const;
  Id dest_port() const;

 private:
  Id source_device_;
  Id source_port_;
  Id dest_device_;
  Id dest_port_;
};

}

#endif /* PIOUS_CONNECTION_HPP */

