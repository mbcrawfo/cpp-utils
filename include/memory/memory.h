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

#ifndef MEMORY_H__
#define MEMORY_H__

#include "prereqs.h"
#include "memory/MemoryAllocator.h"
#include "memory/StdLibAllocator.h"

namespace util
{

/**
  * Allocates memory and initializes an object with the provided parameters. 
  * Use in place of new.
  * \throw std::bad_alloc If the allocator returns null when allocation fails 
  * bad_alloc is thrown to signal the failure.
  */
template<typename Allocator, typename T, typename ...Args>
T* create(Args&& ...args);  

/**
  * Allocates memory for an array of size count, and initializes each element 
  * with the provided parameters. Use in place of new[].
  * \throw std::bad_alloc If the allocator returns null when allocation fails
  * bad_alloc is thrown to signal the failure.
  */
template<typename Allocator, typename T, typename ...Args>
T* createArray(std::size_t count, Args&& ...args);

/**
  * Destructs an object and frees its memory. Use in place of delete.
  */
template<typename Allocator, typename T>
void destroy(T* ptr);

/**
  * Destructs each item in an array and frees its memory. You must supply the 
  * correct array size to ensure that all destructors are run. Use in place 
  * of delete[].
  */
template<typename Allocator, typename T>
void destroyArray(std::size_t count, T* ptr);

/**
  * Shortcut specialization of create using GeneralAllocator.
  */
template<typename T, typename ...Args>
T* create(Args&& ...args);

/**
  * Shortcut specialization of createArray using GeneralAllocator.
  */
template<typename T, typename ...Args>
T* createArray(std::size_t count, Args&& ...args);

/**
  * Shortcut specialization of destroy using GeneralAllocator.
  */
template<typename T>
void destroy(T* ptr);

/**
  * Shortcut specialization of destroyArray using GeneralAllocator.
  */
template<typename T>
void destroyArray(std::size_t count, T* ptr);

// general usage allocator
namespace MemorySystem { class General {}; }
using GeneralAllocator = MemoryAllocator<MemorySystem::General>;

/****************************************************************************
* Definitions
****************************************************************************/
  
template<typename Allocator, typename T, typename ...Args>
T* create(Args&& ...args)
{
  T* ptr = static_cast<T*>(Allocator::malloc(sizeof(T)));
  if (!ptr)
  {
    throw std::bad_alloc();
  }
  new (ptr) T(std::forward<Args>(args)...);
  return ptr;
}

template<typename Allocator, typename T, typename ...Args>
T* createArray(std::size_t count, Args&& ...args)
{
  T* ptr = static_cast<T*>(Allocator::malloc(sizeof(T), count));
  if (!ptr)
  {
    throw std::bad_alloc();
  }
  for (std::size_t i = 0; i < count; i++)
  {
    new (ptr + i) T(std::forward<Args>(args)...);
  }
  return ptr;
}

template<typename Allocator, typename T>
void destroy(T* ptr)
{
  if (ptr)
  {
    ptr->~T();
    Allocator::free(ptr);
  }
}

template<typename Allocator, typename T>
void destroyArray(std::size_t count, T* ptr)
{
  if (ptr)
  {
    for (std::size_t i = 0; i < count; i++)
    {
      (ptr + i)->~T();
    }
    Allocator::free(ptr);
  }
}

template<typename T, typename ...Args>
T* create(Args&& ...args)
{
  return create<GeneralAllocator, T, Args...>(std::forward<Args>(args)...);
}

template<typename T, typename ...Args>
T* createArray(std::size_t count, Args&& ...args)
{
  return createArray<GeneralAllocator, T, Args...>(
    count, 
    std::forward<Args>(args)...
    );
}

template<typename T>
void destroy(T* ptr)
{
  destroy<GeneralAllocator, T>(ptr);
}

template<typename T>
void destroyArray(std::size_t count, T* ptr)
{
  destroyArray<GeneralAllocator, T>(count, ptr);
}

}

#endif