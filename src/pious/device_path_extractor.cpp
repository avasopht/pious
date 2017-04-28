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

#include <pious/device_path_extractor.hpp>
#include <pious/device_container.hpp>

namespace pious {

DevicePathExtractor::DevicePathExtractor(emcee::Memory * memory) : memory_(memory), paths_(memory){

}

void DevicePathExtractor::ExtractPaths(DeviceContainer * container) {
  for(size_t i = 0; i < container->child_count(); ++i) {
    ExtractPaths(container->ChildAt(i));
  }
}

void DevicePathExtractor::ExtractPaths(Device * device) {
  emcee::Vector<PathSearch> searches (memory_);
  searches.PushBack(CreatePathSearch(device));
}

DevicePathExtractor::PathSearch DevicePathExtractor::CreatePathSearch(Device * device) {
  PathSearch search;
  search.path.SetMemory(memory_);
  search.path.PushBack(device);
  search.iterator = search.path.begin();
  return search;
}

}
