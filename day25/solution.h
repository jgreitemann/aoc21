#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day25 {

  using Point = AoC::Point<std::size_t>;
  using MapView = AoC::View2D<char>;
  using MapConstView = AoC::View2D<char const>;

  auto step(MapConstView input_map, MapView output_map) -> bool;
  auto steps_until_converged(MapConstView input_map) -> std::size_t;

}// namespace Day25

namespace AoC {

  template <>
  struct Solution<25> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    explicit Solution(std::pair<std::vector<char>, Day25::MapView> &&pair);
    std::vector<char> initial_data;
    Day25::MapConstView initial_view;
  };

}// namespace AoC
