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

#include "log/Log.h"
#include <cstdio>

// The printf style log functions use a fixed size stack buffer to process the 
// format string.
static const int PRINTF_BUFFER_SIZE = 256;

namespace util
{

Log::Log(const std::string& logName, LogLevel outputLevel)
  : logName(logName),
    outputLevel(outputLevel),
    writers()
{}

void Log::setName(const std::string& logName)
{
  this->logName = logName;
}

const std::string& Log::getName() const
{
  return logName;
}

void Log::setLevel(LogLevel outputLevel)
{
  this->outputLevel = outputLevel;
}

LogLevel Log::getLevel() const
{
  return outputLevel;
}

bool Log::isActive(LogLevel level) const
{
  return outputLevel <= level;
}

bool Log::hasWriter(const std::string& name) const
{
  return writers.find(name) != writers.end();
}

bool Log::addWriter(const std::string& name, StrongLogWriterPtr writer)
{
  assert(writer != nullptr);
  if (hasWriter(name))
  {
    return false;
  }
  writers[name] = writer;
  return true;
}

bool Log::removeWriter(const std::string& name)
{
  auto itr = writers.find(name);
  if (itr == writers.end())
  {
    return false;
  }
  writers.erase(itr);
  return true;
}

Log::StreamHelper Log::info(const std::string& tag)
{
  return stream(LogLevel::Info, tag);
}

void Log::info(const std::string& tag, const std::string& msg)
{
  log(LogLevel::Info, tag, msg);
}

void Log::infof(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  logv(LogLevel::Info, tag, fmt, args);
  va_end(args);
}

Log::StreamHelper Log::warning(const std::string& tag)
{
  return stream(LogLevel::Warning, tag);
}

void Log::warning(const std::string& tag, const std::string& msg)
{
  log(LogLevel::Warning, tag, msg);
}

void Log::warningf(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  logv(LogLevel::Warning, tag, fmt, args);
  va_end(args);
}

Log::StreamHelper Log::error(const std::string& tag)
{
  return stream(LogLevel::Error, tag);
}

void Log::error(const std::string& tag, const std::string& msg)
{
  log(LogLevel::Error, tag, msg);
}

void Log::errorf(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  logv(LogLevel::Error, tag, fmt, args);
  va_end(args);
}

void Log::log(LogLevel level, const std::string& tag, const std::string& msg)
{
  if (isActive(level))
  {
    dispatch(level, tag, msg);
  }
}

void Log::logf(LogLevel level, const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  logv(level, tag, fmt, args);
  va_end(args);
}

void Log::logv(LogLevel level, const std::string& tag, const char* fmt, 
  va_list args)
{
  if (!isActive(level))
  {
    return;
  }

  char buffer[PRINTF_BUFFER_SIZE];
  int result = vsnprintf(buffer, PRINTF_BUFFER_SIZE, fmt, args);
  std::string msg;

  // as of msvc 2013 microsoft's vsnprintf has a non-standard return value,
  // it only signals when the buffer is too small
#if LU_COMPILER == LU_COMPILER_MSVC
  if (result == -1)
  {
    buffer[PRINTF_BUFFER_SIZE - 1] = '\0';
    msg = std::string(buffer).append("...");
  }
#else
  if (result == -1)
  {
    msg = std::string("vsnprintf error in Log::logv");
  }
  else if (result >= PRINTF_BUFFER_SIZE)
  {
    buffer[PRINTF_BUFFER_SIZE - 1] = '\0';
    msg = std::string(buffer).append("...");
  }
#endif
  else
  {
    msg = std::string(buffer);
  }

  dispatch(level, tag, msg);
}

Log::StreamHelper Log::stream(LogLevel level, const std::string& tag)
{
  return StreamHelper(*this, level, tag);
}

void Log::dispatch(LogLevel level, const std::string& tag, 
  const std::string& msg)
{
  StrongLogMessagePtr lm(new LogMessage{
    level,
    std::chrono::system_clock::now(),
    logName,
    tag,
    msg
    }
  );

  for (auto writer : writers)
  {
    writer.second->write(lm);
  }
}

Log::StreamHelper::StreamHelper(Log& log, LogLevel level, 
  const std::string& tag)
  : impl(new StreamHelperImpl(log, level, tag))
{
}

Log::StreamHelper& Log::StreamHelper::operator<<(
  Log::StreamHelper::Manipulator manip)
{
  manip(impl->os);
  return *this;
}


Log::DummyStreamHelper& Log::DummyStreamHelper::operator<<(Manipulator manip)
{
  LU_UNUSED(manip);
  return *this;
}

Log::StreamHelperImpl::StreamHelperImpl(Log& log, LogLevel level, 
  const std::string& tag) 
: log(log),
  level(level),
  tag(tag),
  os()
{
}

Log::StreamHelperImpl::~StreamHelperImpl()
{
  log.log(level, tag, os.str());
}

}
