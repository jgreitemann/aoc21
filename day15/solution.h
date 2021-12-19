#pragma once

#include "../solution.h"
#include "../utils.h"

#include <span>
#include <vector>

namespace Day15 {

  using Point = AoC::Point<std::size_t>;
  using MapConstView = AoC::View2D<int const>;
  using MapView = AoC::View2D<int>;

  auto least_risk_level_map(MapConstView map) -> std::vector<int>;

}// namespace Day15

namespace AoC {

  template <>
  struct Solution<15> {
    explicit Solution(std::istream &);
    auto part1() const -> int;

  private:
    explicit Solution(std::pair<std::vector<int>, Day15::MapConstView> pair);
    std::vector<int> data;
    Day15::MapConstView map;
  };

}// namespace AoC
