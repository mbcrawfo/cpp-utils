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

#ifndef FILELOGWRITER_H_INCLUDED__
#define FILELOGWRITER_H_INCLUDED__

#include "prereqs.h"
#include "log/LogWriter.h"
#include <fstream>
#include <string>

namespace util
{

/**
 * A log writer that directs its output to a file.  Not thread safe.
 */
class FileLogWriter final
  : public LogWriter
{
private:
  std::ofstream file;

public:
  // constructors
  FileLogWriter() = default;
  FileLogWriter(const FileLogWriter&) = delete;

  /**
   * Creates a writer opening a file immediately.  Same behavior as open().  
   * Check isOpen() before using the file.
   */
  explicit FileLogWriter(const std::string& filename, bool append = false);
  
  // operators
  FileLogWriter& operator=(const FileLogWriter&) = delete;

  /**
   * Opens a file for writing.  If a file is currently open it will be closed 
   * before the new file is opened.
   * \param filename The path of the file to open.
   * \param append If true, appends to an existing file.  Otherwise replaces 
   * the existing file.
   * \return True if the file was opened.
   */
  bool open(const std::string& filename, bool append = false);

  /**
   * Closes the file, if one is open.
   */
  void close();

  /**
   * Returns true if a file is open.
   */
  bool isOpen() const;

protected:
  virtual void output(const std::string& msg) override;
};

}

#endif
