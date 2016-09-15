/*
 * Created by The Pious Authors on 14/09/2016.
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

#ifndef PIOUS_OS_SETTER_HPP
#define PIOUS_OS_SETTER_HPP

#include <boost/type_traits/is_base_of.hpp>

namespace pious {

class Os;

/*!
 * Inherit from OsSetter for an Os instance to be injected by compatible classes.
 */
class OsSetter {
 public:
  virtual ~OsSetter() = 0;

  virtual void SetOs(Os *os) = 0;

  /*! Injects an os into the instance if the type derives from OsSetter */
  template<typename T> static void InjectOs(T &ref, Os *os) {
    boost::is_base_of<OsSetter,T> type;
    InjectOs(type, ref, os);
  }

 private:

  template<typename T> static void InjectOs(boost::true_type, T &ref, Os *os) {
    ref.SetOs(os);
  }

  template<typename T> static void InjectOs(boost::false_type, T&, Os*) {}
};

}

#endif /*PIOUS_OS_SETTER_HPP*/
