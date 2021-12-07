#pragma once

#include "../solution.h"

#include <array>
#include <numeric>
#include <span>

namespace Day06 {

  using Census = std::array<std::size_t, 9>;

  constexpr auto number_of_fish(Census const &census) -> std::size_t {
    return std::accumulate(census.begin(), census.end(), 0ul);
  }

  auto histogrammize(std::span<int const> population) -> Census;
  auto transition(Census const &census) -> Census;
  auto transition_n(Census census, std::size_t n) -> Census;

}// namespace Day06

namespace AoC {

  template <>
  struct Solution<6> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    Day06::Census initial_census;
  };

}// namespace AoC
