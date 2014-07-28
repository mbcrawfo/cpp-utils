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

#ifndef MEMORYTRACKER_H__
#define MEMORYTRACKER_H__

#include "prereqs.h"
#include <unordered_map>

namespace libutil
{

  /**
   * Tracks memory allocations and deallocations. Make a class/struct for each 
   * subsystem that you wish to track the memory usage of, and supply the type 
   * name as the template parameter to create a new tracker for that subsystem.
   */
  template<typename System>
  class MemoryTracker
  {
    static std::size_t totalAllocations;
    static std::size_t totalFrees;
    static std::size_t totalBytesAllocated;
    static std::size_t curNumAllocations;
    static std::size_t curBytesAllocated;
    static std::unordered_map<void*, std::size_t> allocations;

  public:
    /**
     * Returns the total number of allocations that have been done.
     */
    static std::size_t getTotalNumAllocations();

    /**
     * Returns the total number of frees that have been done.
     */
    static std::size_t getTotalFrees();

    /**
     * Returns the total number of bytes that have been allocated.
     */
    static std::size_t getTotalBytes();

    /**
     * Returns the number of allocations that are currently being used. Valid 
     * only when LU_DEBUG_MEMORY_TRACK_DETAIL is defined.
     */
    static std::size_t getCurrentAllocations();

    /**
     * Returns the bytes of memory that are currently in use. Valid only when 
     * LU_DEBUG_MEMORY_TRACK_DETAIL is defined.
     */
    static std::size_t getCurrentBytes();

    /**
     * Adds an allocation to the memory tracker.
     * \param[in] ptr The address that was allocated.
     * \param[in] sz The size of the allocation.
     */
    static void trackAllocation(void* ptr, std::size_t sz);

    /**
     * Adds a free to the memory tracker.
     * \param[in] ptr The address that was freed.
     */
    static void trackFree(void* ptr);
  };

  /****************************************************************************
  * Definitions
  ****************************************************************************/

  template<typename System>
  std::size_t MemoryTracker<System>::totalAllocations = 0;

  template<typename System>
  std::size_t MemoryTracker<System>::totalFrees = 0;

  template<typename System>
  std::size_t MemoryTracker<System>::totalBytesAllocated = 0;

  template<typename System>
  std::size_t MemoryTracker<System>::curNumAllocations = 0;

  template<typename System>
  std::size_t MemoryTracker<System>::curBytesAllocated = 0;

  template<typename System>
  std::size_t MemoryTracker<System>::getTotalNumAllocations()
  {
    return totalAllocations;
  }

  template<typename System>
  std::size_t MemoryTracker<System>::getTotalFrees()
  {
    return totalFrees;
  }

  template<typename System>
  std::size_t MemoryTracker<System>::getTotalBytes()
  {
    return totalBytesAllocated;
  }

  template<typename System>
  std::size_t MemoryTracker<System>::getCurrentAllocations()
  {
    return curNumAllocations;
  }

  template<typename System>
  std::size_t MemoryTracker<System>::getCurrentBytes()
  {
    return curBytesAllocated;
  }

  template<typename System>
  void MemoryTracker<System>::trackAllocation(void* ptr, std::size_t sz)
  {
    assert(ptr != nullptr);
    totalAllocations++;
    totalBytesAllocated += sz;

#if defined(LU_DEBUG_MEMORY_TRACK_DETAIL)
    assert(allocations.count(ptr) == 0);
    curNumAllocations++;
    curBytesAllocated += sz;
    allocations.emplace(ptr, sz);
#endif
  }

  template<typename System>
  void MemoryTracker<System>::trackFree(void* ptr)
  {
    // catch duplicate frees
    assert(ptr != nullptr);
    totalFrees++;

#if defined(LU_DEBUG_MEMORY_TRACK_DETAIL)
    auto itr = allocations.find(ptr);
    assert(itr != allocations.end());
    curNumAllocations--;
    curBytesAllocated -= itr->second;
    allocations.erase(itr);
#endif
  }

}

#endif