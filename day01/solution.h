#pragma once

#include "../solution.h"

#include <span>
#include <vector>

namespace Day01 {

  auto number_of_increases(std::span<int const> measurements) -> std::size_t;

}

namespace AoC {

  template <>
  struct Solution<1> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<int> measurements;
  };

}// namespace AoC
