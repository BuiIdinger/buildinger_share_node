#pragma once

#include <cstdlib>
#include <string>

namespace utilities {
  int64_t getCurrentEpoch();

  // Returns short date as d-m-y
  std::string getShortDate();
}