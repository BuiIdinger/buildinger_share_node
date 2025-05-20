#include "Logging.h"
#include <string>
#include <source_location>
#include <fstream>
#include <iostream>
#include "Utilities.h"
#include <mutex>
#include "Main.h"

void log::setup() {
  file.open("logs/" + utilities::getShortDate() + ".txt", std::ofstream::out | std::ofstream::app);
  if (!file.is_open()) {
    std::cerr << "Failed to open logging file." << std::endl;
  }
}

void log::shutdown() {
  std::scoped_lock<std::mutex> guard(logMutex);
  file.close();
}

void log::rotateLogFile() {
  std::scoped_lock<std::mutex> guard(logMutex);
  file.open("logs/" + utilities::getShortDate() + ".txt", std::ofstream::out | std::ofstream::app);
  if (!file.is_open()) {
    std::cerr << "Failed to open logging file." << std::endl;
  }
}

void log::critical(const std::string& message, const std::source_location& location) {
  const std::string output = "[CRITICAL] " +
                              std::string(location.function_name()) +
                              " (" + std::to_string(location.line()) +
                              ":" +
                              std::to_string(location.column()) + "): " +
                              message + "\n";

  std::unique_lock <std::mutex> guard(logMutex);
  if (file.is_open()) {
    file.write(output.c_str(), static_cast<long>(output.size()));
  } else {
    std::cerr << output << std::endl;
  }
  guard.unlock();

  ::shutdown(EXIT_FAILURE);
}

void log::error(const std::string& message, const std::source_location& location) {
  const std::string output = "[ERROR] " +
                              std::string(location.function_name()) +
                              " (" + std::to_string(location.line()) +
                              ":" +
                              std::to_string(location.column()) + "): " +
                              message + "\n";


  std::scoped_lock<std::mutex> guard(logMutex);
  if (file.is_open()) {
    file.write(output.c_str(), static_cast<long>(output.size()));
  } else {
    std::cerr << output << std::endl;
  }
}

void log::warn(const std::string& message, const std::source_location& location) {
  const std::string output = "[WARNING] " +
                              std::string(location.function_name()) +
                              " (" + std::to_string(location.line()) +
                              ":" +
                              std::to_string(location.column()) + "): " +
                              message + "\n";


  std::scoped_lock<std::mutex> guard(logMutex);
  if (file.is_open()) {
    file.write(output.c_str(), static_cast<long>(output.size()));
  } else {
    std::cout << output << "\n";
  }
}

void log::info(const std::string& message, const std::source_location& location) {
  const std::string output = "[INFO] " +
                              std::string(location.function_name()) +
                              " (" + std::to_string(location.line()) +
                              ":" +
                              std::to_string(location.column()) + "): " +
                              message + "\n";


  std::scoped_lock<std::mutex> guard(logMutex);
  if (file.is_open()) {
    file.write(output.c_str(), static_cast<long>(output.size()));
  } else {
    std::cout << output << "\n";
  }
}


