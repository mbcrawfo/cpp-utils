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

#define LU_SYSTEM_ARCH_32 0
#define LU_SYSTEM_ARCH_64 1

#define LU_SYSTEM_ENDIAN_LITTLE 0
#define LU_SYSTEM_ENDIAN_BIG 1

#define LU_COMPILER_MSVC 0
#define LU_COMPILER_GNUCXX 1
#define LU_COMPILER_CLANG 2
#define LU_COMPILER_INTEL 3

#define LU_PLATFORM_WINDOWS 0
#define LU_PLATFORM_LINUX 1
#define LU_PLATFORM_APPLE 2

// set the system architecture type
#if defined(__x86_64__) || defined(_M_X64) || defined(__LP64__)
  #define LU_SYSTEM_ARCH LU_SYSTEM_ARCH_64
#else
  #define LU_SYSTEM_ARCH LU_SYSTEM_ARCH_32
#endif

// set the endianness (must be manually changed)
#define LU_SYSTEM_ENDIAN LU_SYSTEM_ENDIAN_LITTLE

// find the current compiler
#if defined(_MSC_VER)
  #define LU_COMPILER LU_COMPILER_MSVC
  #define LU_COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
  #define LU_COMPILER LU_COMPILER_GNUCXX
  #define LU_COMPILER_VERSION ((__GNUC__ * 100) + (__GNUC_MINOR__ * 10) + \
    (__GNUC_PATCHLEVEL__))
#elif defined(__clang__)
  #define LU_COMPILER LU_COMPILER_CLANG
  #define LU_COMPILER_VERSION __clang_major__
#elif defined(__INTEL_COMPILER)
  #define LU_COMPILER LU_COMPILER_INTEL
  #define LU_COMPILER_VERSION __INTEL_COMPILER
#else
  #error Unknown compiler
#endif

// find the current platform
#if defined(__WIN32__) || defined(_WIN32)
  #define LU_PLATFORM LU_PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
  #define LU_PLATFORM_APPLE
#else
  #define LU_PLATFORM LU_PLATFORM_LINUX
#endif

#endif
