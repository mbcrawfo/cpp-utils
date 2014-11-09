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

/** \file
 * Includes common headers that are used throughout the utilities, and sets 
 * any platform or compiler specific options.
 */

#ifndef COMMON_H_INCLUDED__
#define COMMON_H_INCLUDED__

#include "platform.h"
#include "debug.h"

// Use to suppress warnings on unused code.
#define LU_UNUSED(x) static_cast<void>(x)

// set compiler specific options
#if LU_COMPILER == LU_COMPILER_MSVC
  #define _CRT_SECURE_NO_WARNINGS
  #define WIN32_LEAN_AND_MEAN
  #define NOMINMAX

  #if defined(LU_DEBUG_STL)
    #define _ITERATOR_DEBUG_LEVEL 1
  #else
    #define _ITERATOR_DEBUG_LEVEL 0
  #endif

#elif LU_COMPILER == LU_COMPILER_GNUCXX
  #if defined(LU_DEBUG_STL)
    #define _GLIBCXX_DEBUG
  #else
    #undef _GLIBCXX_DEBUG
  #endif

#elif LU_COMPILER == LU_COMPILER_CLANG
  #if defined(LU_DEBUG_STL)
    #error clang STL debug settings have not been added
  #endif

#elif LU_COMPILER == LU_COMPILER_INTEL
  #if defined(LU_DEBUG_STL)
    #error Intel STL debug settings have not been added
  #endif
#endif

// common standard headers
#include <cstdint>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <type_traits>
#include <utility>
#include <limits>
#include <memory>
#include <new>
#include <stdexcept>

/** Convenience type for shared pointers. */
template<typename T>
using StrongPtr = std::shared_ptr<T>;

/** Convenience type for weak pointers. */
template<typename T>
using WeakPtr = std::weak_ptr<T>;

#endif
