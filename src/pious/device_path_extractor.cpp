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
#include <pious/device_path_search.hpp>
#include <emcee/set.hpp>

namespace pious {

DevicePathExtractor::DevicePathExtractor(emcee::Platform * memory) : memory_(memory), paths_(memory){

}

void DevicePathExtractor::ExtractPaths(DeviceContainer * container) {
  for(size_t i = 0; i < container->child_count(); ++i) {
    ExtractPathsFromDevice(container->ChildAt(i));
  }
}

void DevicePathExtractor::ExtractPathsFromDevice(Device * device) {
  emcee::Vector<DevicePathSearch> searchlist (memory_);
  searchlist.PushBack(CreatePathSearch(device));
  while(!searchlist.Empty()) {
    emcee::Vector<DevicePathSearch> next_searchlist(memory_);
    for(emcee::Vector<DevicePathSearch>::Iterator search_iter = searchlist.begin(); search_iter != searchlist.end(); ++search_iter) {
      // For each connection, create a new path search, adding it to 'next' list.
      // PerformSearchStep(&search_iter.value(), &next_searchlist);
    }
    searchlist = next_searchlist;
  }
}

DevicePathSearch DevicePathExtractor::CreatePathSearch(Device * device) {
  DevicePathSearch search(memory_, device);
  return search;
}

void DevicePathExtractor::PerformSearchStep(DevicePathSearch * path_search, emcee::Vector<DevicePathSearch> * next_searchlist) {

}

} /* pious */
