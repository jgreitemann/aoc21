#pragma once

#include "../solution.h"

#include <span>
#include <vector>

namespace Day07 {

  struct Alignment {
    int pos;
    int cost;
  };

  constexpr int identity(int n) { return n; }
  constexpr int gauss(int n) { return n * (n + 1) / 2; }

  auto cost_to_align(std::span<int const> crabs, int pos, int (*profile)(int)) -> int;
  auto cheapest_aligned_position(std::span<int const> crabs, int (*profile)(int)) -> Alignment;

}// namespace Day07

namespace AoC {

  template <>
  struct Solution<7> {
    explicit Solution(std::istream &);
    auto part1() const -> int;
    auto part2() const -> int;

  private:
    std::vector<int> crabs;
  };

}// namespace AoC
