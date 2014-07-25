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
 * Contains definitions to detect the system architecture, compiler, and 
 * operating system.
 */

#ifndef PLATFORM_H_INCLUDED__
#define PLATFORM_H_INCLUDED__

#define SYSTEM_ARCH_32 0
#define SYSTEM_ARCH_64 1

#define SYSTEM_ENDIAN_LITTLE 0
#define SYSTEM_ENDIAN_BIG 1

#define COMPILER_MSVC 0
#define COMPILER_GNUCXX 1
#define COMPILER_CLANG 2
#define COMPILER_INTEL 3

#define PLATFORM_WINDOWS 0
#define PLATFORM_LINUX 1
#define PLATFORM_APPLE 2

// set the system architecture type
#if defined(__x86_64__) || defined(_M_X64) || defined(__LP64__)
  #define SYSTEM_ARCH SYSTEM_ARCH_64
#else
  #define SYSTEM_ARCH SYSTEM_ARCH_32
#endif

// set the endianness (must be manually changed)
#define SYSTEM_ENDIAN SYSTEM_ENDIAN_LITTLE

// find the current compiler
#if defined(_MSC_VER)
  #define COMPILER COMPILER_MSVC
  #define COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
  #define COMPILER COMPILER_GNUCXX
  #define COMPILER_VERSION ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + \
    (__GNUC_PATCHLEVEL__))
#elif defined(__clang__)
  #define COMPILER COMPILER_CLANG
  #define COMPILER_VERSION __clang_major__
#elif defined(__INTEL_COMPILER)
  #define COMPILER COMPILER_INTEL
  #define COMPILER_VERSION __INTEL_COMPILER
#else
  #error Unknown compiler
#endif

// find the current platform
#if defined(__WIN32__) || defined(_WIN32)
  #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
  #define PLATFORM_APPLE
#else
  #define PLATFORM PLATFORM_LINUX
#endif

#endif