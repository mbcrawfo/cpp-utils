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

#ifndef MEMORYALLOCATOR_H_INCLUDED__
#define MEMORYALLOCATOR_H_INCLUDED__

#include "prereqs.h"
#include "memory/MemoryCounter.h"

namespace libutil
{

  /**
   * Wraps standard allocators into a system that allows for memory usage 
   * tracking. Make a separate class/struct for each subsystem, and the 
   * allocator will automatically create a counter for the memory usage by that 
   * system.
   * 
   * Custom allocators can be created using this template. Any custom allocator 
   * should have functions two malloc functions, realloc, and free with 
   * signatures and functionality matching the functions in this class.
   */
  template<typename System>
  class MemoryAllocator
  {
  public:
    /** A shortcut to the usage counter for this allocator. */
    using Counter = MemoryCounter<System>;

    /**
     * Allocates a block of memory.
     * \param[in] sz The size in bytes to allocate.
     * \return A pointer to the memory allocated, or null on an error.
     */
    static void* malloc(const std::size_t sz);

    /**
     * Allocates a block of memory for an array.
     * \param[in] sz The size of each element.
     * \param[in] count The number of elements in the array.
     * \return A pointer to the memory allocated, or null on an error.
     */
    static void* malloc(const std::size_t sz, const std::size_t count);

    /**
     * Attempts to resize an allocated block of memory.
     * \pre ptr must point to a previously allocated block of memory that has 
     * not yet been freed, or it may be null. If it is null, the function 
     * behaves like malloc.
     * \post If null is returned, the block could not be reallocated. The 
     * original block of memory was not freed. Otherwise, the old block of 
     * memory has been freed, a new block has been allocated with the new size, 
     * and then contents of the old block were copied to the new block.
     * \param ptr The location to resize.
     * \param sz The new size of the block.
     * \return A pointer to the memory allocated, or null on an error.
     */
    static void* realloc(void* ptr, const std::size_t sz);

    /**
     * Frees a previously allocated block of memory.
     * \pre ptr should point to a block of memory that has not yet been freed. 
     * Freeing a null pointer is a no-op. Freeing the same block of memory 
     * twice is undefined.
     * \post The memory block pointed to by ptr has been freed and is no longer 
     * valid.
     * \param[in] ptr The memory location to free.
     */
    static void free(void* ptr);
  };

  /****************************************************************************
  * Definitions
  ****************************************************************************/

  template<typename System>
  void* MemoryAllocator<System>::malloc(const std::size_t sz)
  {
    void* ptr = std::malloc(sz);

#if defined(LU_DEBUG_MEMORY_TRACK)
    if (ptr)
    {
      Counter::trackAlloc(ptr, sz);
    }    
#endif

    return ptr;
  }

  template<typename System>
  void* MemoryAllocator<System>::malloc(const std::size_t sz, 
                                        const std::size_t count)
  {
    return MemoryAllocator<System>::malloc(sz * count);
  }

  template<typename System>
  void* MemoryAllocator<System>::realloc(void* ptr, const std::size_t sz)
  {
    void* newPtr = std::realloc(ptr, sz);

#if defined(LU_DEBUG_MEMORY_TRACK)
    // free old block, allocate new block
    if (newPtr && ptr)
    {
      Counter::trackFree(ptr);
      Counter::trackAlloc(newPtr, sz);
    }
    // new allocation only
    else if (newPtr && !ptr)
    {
      Counter::trackAlloc(newPtr, sz);
    }
#endif

    return newPtr;
  }

  template<typename System>
  void MemoryAllocator<System>::free(void* ptr)
  {
    if (ptr)
    {
#if defined(LU_DEBUG_MEMORY_TRACK)
      Counter::trackFree(ptr);
#endif
      std::free(ptr);
    }
  }
}

#endif