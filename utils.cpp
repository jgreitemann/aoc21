#include "utils.h"

#include <iostream>
#include <iterator>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string {
    return {std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};
  }

}// namespace AoC
