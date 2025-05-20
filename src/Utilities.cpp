#include "Utilities.h"
#include <chrono>
#include <string>
#include <sstream>

int64_t utilities::getCurrentEpoch() {
  return std::chrono::system_clock::now().time_since_epoch().count();
}

std::string utilities::getShortDate() {
  const std::time_t now = std::time(nullptr);
  const std::tm* localTime = std::localtime(&now);

  std::ostringstream oss;
  oss << localTime->tm_mday << "-"
      << (localTime->tm_mon + 1) << "-"
      << (localTime->tm_year + 1900);

  return oss.str();
}

void utilities::removeWhitespace(std::string& str) {
  std::erase_if(str, isspace);
}