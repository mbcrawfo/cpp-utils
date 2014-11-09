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

#ifndef STREAMLOGWRITER_H_INCLUDED__
#define STREAMLOGWRITER_H_INCLUDED__

#include "prereqs.h"
#include "log/LogWriter.h"
#include <ostream>

namespace libutil
{

/**
 * This writer wraps a stream, sending all log output to that stream.
 */
class StreamLogWriter final
  : public LogWriter
{
private:
  std::ostream& stream;

public:
  // constructors
  StreamLogWriter() = delete;
  StreamLogWriter(const StreamLogWriter&) = default;
  StreamLogWriter(std::ostream& stream);
  // destructor
  virtual ~StreamLogWriter() = default;
  // operators
  StreamLogWriter& operator=(const StreamLogWriter&) = delete;

protected:
  virtual void output(const std::string& msg) override;
};

// Writers for standard output and error
extern StreamLogWriter StdOutLogWriter;
extern StreamLogWriter StdErrLogWriter;

/****************************************************************************
* Definitions
****************************************************************************/

inline StreamLogWriter::StreamLogWriter(std::ostream& stream)
  : stream(stream)
{
}

inline void StreamLogWriter::output(const std::string& msg)
{
  stream << msg << std::endl;
}

}

#endif
