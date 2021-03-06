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

#ifndef SINGULARITY_H_INCLUDED__
#define SINGULARITY_H_INCLUDED__

#include "prereqs.h"

namespace util
{

/**
  * A variant of the singleton that allows for explicit instantiation and
  * destruction of the instance, so that the class may use a non-default
  * constructor. Single-instance is more loosely enforced (using assertions).
  *
  * Based on http://scottbilas.com/publications/gem-singleton/
  */
template<typename T>
class Singularity
{
  static_assert(std::is_class<T>::value, "Type must be a class");

  static T* instance;

public:
  /**
    * Returns the class instance.  Class must be instantiated before usage.
    */
  static T& getInstance();

  Singularity();
  ~Singularity();

  Singularity(const Singularity&) = delete;
  Singularity& operator =(const Singularity&) = delete;
};

/****************************************************************************
* Function definitions
*****************************************************************************/

template<typename T>
T* Singularity<T>::instance = nullptr;

template<typename T>
T& Singularity<T>::getInstance()
{
  assert(instance && "Not initialized");
  return *instance;
}

template<typename T>
Singularity<T>::Singularity()
{
  assert(!instance && "Duplicate initialization");
  instance = static_cast<T*>(this);
}

template<typename T>
Singularity<T>::~Singularity()
{
  assert(instance);
  instance = nullptr;
}

}

#endif
