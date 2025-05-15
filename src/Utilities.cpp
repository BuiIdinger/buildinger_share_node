#include "Utilities.h"
#include <chrono>

int64_t utilities::getCurrentEpoch() {
  return std::chrono::system_clock::now().time_since_epoch().count();
}