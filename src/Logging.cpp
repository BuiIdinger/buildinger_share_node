#include "Logging.h"
#include <string>
#include <source_location>

// For now just print everything to std error and std output
#include <iostream>

void log::critical(const std::string& message, const std::source_location& location) {
}

void log::error(const std::string& message, const std::source_location& location) {
}

void log::warn(const std::string& message, const std::source_location& location) {
}

void log::info(const std::string& message, const std::source_location& location) {
}


