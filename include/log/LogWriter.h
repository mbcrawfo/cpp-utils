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

#ifndef LOGWRITER_H_INCLUDED__
#define LOGWRITER_H_INCLUDED__

#include "prereqs.h"
#include "log/LogMessage.h"
#include "log/ILogFormatter.h"

namespace libutil
{

/**
 * The abstract base for anything that wants to output log messages.  The 
 * message should be formatted using the supplied formatter to ensure 
 * consistent behavior.  How the message is written to output is determined by
 * the implementation.
 * 
 * An implementation should clearly document if it is thread-safe, and whether 
 * or not it requires a thread-safe formatter.
 */
class LogWriter
{
private:
  StrongLogFormatterPtr formatter;
  LogLevel outputLevel;

public:
  // constructors
  LogWriter();
  LogWriter(const LogWriter&) = default;
  // destructor
  virtual ~LogWriter() = default;
  // operators
  LogWriter& operator=(const LogWriter&) = default;

  /**
   * Sets the formatter used by this writer.
   */
  void setFormatter(StrongLogFormatterPtr formatter);

  /**
   * Retrieves the formatter.
   */
  StrongLogFormatterPtr getFormatter() const;

  /**
   * Sets the output level of the writer.
   */
  void setLevel(LogLevel level);

  /**
   * Gets the output level of the writer.
   */
  LogLevel getLevel() const;

  /**
   * Returns true if the level is being written.
   */
  bool isActive(LogLevel level) const;

  /**
   * Sends a single message to the writer.  
   */
  void write(StrongLogMessagePtr msg);

protected:
  /**
   * Implemented by the writer to output the message.
   */
  virtual void output(const std::string& msg) = 0;
};

using StrongLogWriterPtr = StrongPtr<LogWriter>;
using WeakLogWriterPtr = WeakPtr<LogWriter>;

}

#endif
