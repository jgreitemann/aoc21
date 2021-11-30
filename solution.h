#pragma once

#include <iostream>
#include <iterator>
#include <string>

namespace AoC {

  template <int day>
  struct Solution;

  inline auto as_string(std::istream &stream) -> std::string {
    return {std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};
  }

}// namespace AoC
