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

#ifndef LOGMESSAGE_H_INCLUDED__
#define LOGMESSAGE_H_INCLUDED__

#include "prereqs.h"
#include <chrono>
#include <string>

namespace libutil
{

/**
 * Specifies the detail level of a log message.
 */
enum class LogLevel
{
  /** Used to output all messages. */
  All,
  /** Used for overly detailed messages. */
  Verbose,
  /** Used for messages with extra debug info. */
  Debug,
  /** Used for general informative messages. */
  Info,
  /** Used for warnings about potentially bad events. */
  Warning,
  /** Used for errors that should not occur. */
  Error,
  /** Used to disable all messages. */
  None
};

/**
 * Get the string representation of a log level.
 */
std::string toString(const LogLevel level);

/**
 * Encapsulates all of the information about a log message.
 */
struct LogMessage final
{
  // instantiate using list initialization only
  LogMessage() = delete;
  LogMessage(LogMessage&) = delete;
  LogMessage& operator=(LogMessage&) = delete;

  /** The output level of the message. */
  const LogLevel level;
  /** The time when the message was created. */
  const std::chrono::system_clock::time_point timeStamp;
  /** The log that created this message. */
  const std::string logName;
  /** The output tag of the message. */
  const std::string tag;
  /** The actual message to be logged. */
  const std::string message;
};

/****************************************************************************
* Definitions
****************************************************************************/

inline std::string toString(const LogLevel level)
{
  switch (level)
  {
  case LogLevel::All:
    return "All";
  case LogLevel::Debug:
    return "Debug";
  case LogLevel::Info:
    return "Info";
  case LogLevel::Warning:
    return "Warning";
  case LogLevel::Error:
    return "Error";
  case LogLevel::None:
    return "None";
  }
}

}

#endif
