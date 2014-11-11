/* The MIT License (MIT)
*
* Copyright (c) 2014 Michael Crawford
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef IHASHABLE_H_INCLUDED__
#define IHASHABLE_H_INCLUDED__

#include "prereqs.h"

namespace util
{

/**
 * Provides an interface for any classes that support hashing.
 */
class IHashable
{
public:
  virtual ~IHashable() = default;

  /**
   * Returns the hash of the object.
   */
  virtual std::size_t hash() const = 0;
};

}

/**
 * Generates specializations of std::hash and std::equal_to for a hashable 
 * class, allowing them to be used with STL hashing containers.  There is no 
 * way to declare a single specialization for these functors since template 
 * containers are instantiated using the most derived type.
 */
#define HASHABLE_STL_HELPER_DECLARATION(hashable) \
  namespace std { \
    template<> \
    struct hash<hashable> { \
      size_t operator()(const hashable& h) { \
        return h.hash(); \
      } \
    }; \
    template<> \
    struct equal_to<hashable> { \
      bool operator()(const hashable& lhs, const hashable& rhs) { \
        return lhs.hash() == rhs.hash(); \
      } \
    }; \
  }

#endif
