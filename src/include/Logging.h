#pragma once

#include <source_location>
#include <string>
#include <fstream>
#include <mutex>

namespace log {
  inline std::mutex logMutex;
  inline std::ofstream file;

  // Rotates the log file stream to a new log stream with the new short date
  void rotateLogFile();

  void setup();
  void shutdown();

  // For an error so bad, we cannot recover the node, this will shut down the node
  void critical(const std::string& message, const std::source_location& location = std::source_location::current());

  // We can still continue operating the node, and this error doesn't accept
  // the ability for us to s
  void error(const std::string& message, const std::source_location& location = std::source_location::current());
  void info(const std::string& message, const std::source_location& location = std::source_location::current());
  void warn(const std::string& message, const std::source_location& location = std::source_location::current());
}