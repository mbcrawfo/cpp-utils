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

#ifndef STDLIBALLOCATOR_H_INCLUDED__
#define STDLIBALLOCATOR_H_INCLUDED__

#include "prereqs.h"
#include <limits>

namespace util
{

/**
  * Wraps an allocator in a class suitable for usage with the STL. Allocator 
  * must conform to the model set by MemoryAllocator.
  */
template<typename T, typename Allocator>
class StdLibAllocator
{
public:
  // standard types
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using void_pointer = void*;
  using const_void_pointer = const void*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  template<typename U>
  struct rebind
  {
    using other = StdLibAllocator<U, Allocator>;
  };

  /**
    * Allocate memory without constructing an object.
    * \param[in] n The number of objects to allocate memory for.
    * \param[in] cvptr Unused.
    * \return A pointer to the allocated memory.
    */
  pointer allocate(const size_type n, const_void_pointer cvptr = nullptr);

  /**
    * Frees memory previously allocated by allocate, without calling 
    * destructors.
    * \param[in] ptr The memory to deallocate.
    * \param[in] n Unused.
    */
  void deallocate(pointer ptr, const size_type n);

  /**
    * Returns the maximum number of objects of type T that may be allocated.
    */
  size_type max_size();

  /**
    * Constructs an object using previously allocated memory.
    * \param[in,out] ptr The memory where the object should be constructed, 
    * points to the constructed object after return.
    * \param[in] args The parameters that will be passed the the constructor.
    */
  template<typename ...Args>
  void construct(pointer ptr, Args&&... args);

  /**
    * Calls the destructor of an object, but does not free memory.
    * \param[in] ptr The object to destroy.
    */
  void destroy(pointer ptr);
};

// all allocators evaluate as equal
template<typename T, typename U, typename Allocator>
bool operator ==(const StdLibAllocator<T, Allocator>&,
                  const StdLibAllocator<U, Allocator>&);

template<typename T, typename U, typename Allocator>
bool operator !=(const StdLibAllocator<T, Allocator>&,
                  const StdLibAllocator<U, Allocator>&);

/****************************************************************************
* Definitions
****************************************************************************/
  
template<typename T, typename Allocator>
typename StdLibAllocator<T, Allocator>::pointer
  StdLibAllocator<T, Allocator>::allocate(const size_type n,
                                          const_void_pointer cvptr)
  {
    LU_UNUSED(cvptr);
    return static_cast<pointer>(Allocator::malloc(sizeof(T) * n));
  }

template<typename T, typename Allocator>
void StdLibAllocator<T, Allocator>::deallocate(pointer ptr, const size_type n)
{
  LU_UNUSED(n);
  Allocator::free(ptr);
}

template<typename T, typename Allocator>
typename StdLibAllocator<T, Allocator>::size_type
  StdLibAllocator<T, Allocator>::max_size()
  {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

template<typename T, typename Allocator>
template<typename ...Args>
void StdLibAllocator<T, Allocator>::construct(pointer ptr, Args&&... args)
{
  new (ptr) T(std::forward<Args>(args)...);
}

template<typename T, typename Allocator>
void StdLibAllocator<T, Allocator>::destroy(pointer ptr)
{
  ptr->~T();
}

template<typename T, typename U, typename Allocator>
bool operator ==(const StdLibAllocator<T, Allocator>&,
                  const StdLibAllocator<U, Allocator>&)
{
  return true;
}

template<typename T, typename U, typename Allocator>
bool operator !=(const StdLibAllocator<T, Allocator>&,
                  const StdLibAllocator<U, Allocator>&)
{
  return false;
}

}

#endif