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
 * Controls settings used to control debugging features.
 */

#ifndef DEBUG_H_INCLUDED__
#define DEBUG_H_INCLUDED__

// Enables debugging in the STL when defined, if it's supported by the 
// implementation
//#define LU_DEBUG_STL

// Enables tracking of memory allocations when defined
//#define LU_DEBUG_MEMORY_TRACK

// Enables detailed memory tracking when defined. LU_DEBUG_MEMORY_TRACK must 
// also be defined. When enabled, current usage is tracked as well as total 
// usage
//#define LU_DEBUG_MEMORY_TRACK_DETAIL

#endif