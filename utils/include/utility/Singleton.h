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

#ifndef SINGLETON_H_INCLUDED__
#define SINGLETON_H_INCLUDED__

#include "prereqs.h"

namespace libutil
{

/**
  * Implements the singleton design pattern for the template parameter. The
  * inheriting class must provide a default constructor that is accessible to
  * its base classes.
  */
template<typename T>
class Singleton
{
  static_assert(std::is_class<T>::value, "Type must be a class");

  Singleton() = default;

public:
  /**
    * Returns the singleton instance. Creates the instance if it has not been
    * initialized.
    */
  static T& getInstance();

  Singleton(const Singleton&) = delete;
  Singleton& operator =(const Singleton&) = delete;
};

/****************************************************************************
  * Function definitions
  ****************************************************************************/

template<typename T>
T& Singleton<T>::getInstance()
{
  static T instance;
  return instance;
}

}

#endif