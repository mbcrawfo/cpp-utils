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

#ifndef LOG_H_INCLUDED__
#define LOG_H_INCLUDED__

#include "prereqs.h"
#include "log/LogMessage.h"
#include "log/LogWriter.h"
#include <unordered_map>
#include <cstdarg>
#include <sstream>

namespace libutil
{

/**
 * Used for logging information about the program execution.  Each log 
 * encapsulates a set of writers that may direct output to different targets.  
 * Output is filtered based on the level of a message, with filtering done by 
 * both the log itself and each individual writer.
 */
class Log final
{
private:
  std::string logName;
  LogLevel outputLevel;
  std::unordered_map<std::string, StrongLogWriterPtr> writers;

  class StreamHelper;
  
public:
  // constructors
  Log(const Log&) = default;
  explicit Log(const std::string& logName, 
    LogLevel outputLevel = LogLevel::All);
  // operators
  Log& operator=(const Log&) = default;

  /**
   * Sets the name of this log.
   */
  void setName(const std::string& logName);

  /**
   * Retrieves the name of this log.
   */
  const std::string& getName() const;

  /**
   * Sets the output level of this log.  Messages below the set level will not 
   * but output.
   */
  void setLevel(LogLevel outputLevel);

  /**
   * Retrieves the output level of this log.
   */
  LogLevel getLevel() const;

  /**
   * Returns true if messages at the provided level will be output by the log.
   */
  bool isActive(LogLevel level) const;

  /**
   * Returns true if the log has a writer with the provided name.
   */
  bool hasWriter(const std::string& name) const;

  /**
   * Adds a writer to the log with the given name.
   * \return false if a log already exists with that name.
   */
  bool addWriter(const std::string& name, StrongLogWriterPtr writer);

  /**
   * Removes the writer with the given name.
   * \return true if the writer was found and removed.
   */
  bool removeWriter(const std::string& name);

  // \{
  /**
   * These functions are wrappers around log and logf to provide simple or 
   * printf style logging at a specific level.
   * 
   * If LU_LOG_DISABLE_VERBOSE is defined then the verbose methods are no-ops.
   * If LU_LOG_DISABLE_DEBUG is defined then the debug methods are no-ops.
   */
  void verbose(const std::string& tag, const std::string& msg);
  void verbosef(const std::string& tag, const char* fmt, ...);
  void debug(const std::string& tag, const std::string& msg);
  void debugf(const std::string& tag, const char* fmt, ...);
  void info(const std::string& tag, const std::string& msg);
  void infof(const std::string& tag, const char* fmt, ...);
  void warning(const std::string& tag, const std::string& msg);
  void warningf(const std::string& tag, const char* fmt, ...);
  void error(const std::string& tag, const std::string& msg);
  void errorf(const std::string& tag, const char* fmt, ...);
  // \}

  // \{
  /**
   * Process a log message message that is passed to the writers, if the 
   * given level is enabled.
   */
  void log(LogLevel level, const std::string& tag, const std::string& msg);
  void logf(LogLevel level, const std::string& tag, const char* fmt, ...);
  void logv(LogLevel level, const std::string& tag, const char* fmt, 
    va_list args);
  // \}

  /**
   * Returns a helper object that allows the log to accept stream input.  
   * You should never hold a reference to the helper, because if the helper 
   * outlives the log that created it, bad things will happen.  Also, the 
   * helper does not forward its accumulated input back to the log until it is 
   * destroyed.
   */
  StreamHelper stream(LogLevel level, const std::string& tag);

private:
  /**
   * Creates a LogMessage from the provided parameters and forwards that 
   * message to the writers of this log.
   */
  void dispatch(LogLevel level, const std::string& tag, const std::string& msg);

  /**
   * Helper class that allows logs to accept stream input.  Input is 
   * accumulated in a stringstream and dispatched back to the log when the 
   * helper is destroyed.
   */
  class StreamHelper final
  {
  private:
    Log& log;
    const LogLevel level;
    const std::string tag;
    std::ostringstream os;    

  public:
    using Manipulator = std::ostream& (*)(std::ostream&);

    // constructors
    StreamHelper() = delete;
    StreamHelper(Log& log, LogLevel level, const std::string& tag);
    StreamHelper(const StreamHelper&) = delete;
    // destructor
    ~StreamHelper();    
    // operators
    StreamHelper& operator=(const StreamHelper&) = delete;

    /**
     * Insert an object into the helper stream.
     */
    template<typename T>
    StreamHelper& operator<<(const T& arg);

    /**
     * Apply a stream manipulator to the stream.
     */
    StreamHelper& operator<<(Manipulator manip);
  };
};

using StrongLogPtr = StrongPtr<Log>;
using WeakLogPtr = WeakPtr<Log>;

/****************************************************************************
* Definitions
****************************************************************************/

template<typename T>
Log::StreamHelper& Log::StreamHelper::operator<<(const T& arg)
{
  os << arg;
  return *this;
}

}

#endif
