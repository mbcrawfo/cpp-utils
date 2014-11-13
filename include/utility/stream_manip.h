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

#ifndef STREAM_MANIP_H_INCLUDED__
#define STREAM_MANIP_H_INCLUDED__

#include "prereqs.h"
#include <iomanip>
#include <iostream>

namespace util
{

// \{
/**
 * Manipulates an input or output stream to output or read integers in 
 * hexadecimal format with leading zeros.
 */
template<typename T, std::size_t width = sizeof(T) * 2>
std::ostream& hex(std::ostream& str);
template<typename T, std::size_t width = sizeof(T) * 2>
std::istream& hex(std::istream& str);
// \}

/****************************************************************************
* Definitions
****************************************************************************/

template<typename T, std::size_t width>
std::ostream& hex(std::ostream& str)
{
  str << std::setw(width) << std::setfill('0');
  return str;
}

template<typename T, std::size_t width>
std::istream& hex(std::istream& str)
{
  str >> std::setw(width) >> std::setfill('0');
  return str;
}

}

// operator overloads to allow usage with STL streams
namespace std
{

template<typename T>
ostream& operator<<(ostream& os, decltype(util::hex<T>) h)
{
  os << h;
  return os;
}

template<typename T>
istream& operator<<(istream& is, decltype(util::hex<T>) h)
{
  is >> h;
  return is;
}

}

#endif
