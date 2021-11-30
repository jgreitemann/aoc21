#pragma once

#include "../solution.h"

#include <string_view>

namespace Day00 {

  auto count_characters(std::string_view str) -> std::size_t;

}

namespace AoC {

  template <>
  struct Solution<0> {
    static auto part1(std::istream &) -> std::size_t;
  };

}// namespace AoC
