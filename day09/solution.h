#pragma once

#include "../solution.h"
#include "../utils.h"

#include <span>
#include <utility>
#include <vector>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day09 {

  using AoC::Dyn2DExtents;
  using Point = AoC::Point<std::size_t>;
  using ElevationView = AoC::View2D<int>;
  using ElevationConstView = AoC::View2D<int const>;

  bool is_local_minimum(ElevationConstView, Point p);
  auto number_of_local_minima(ElevationConstView) -> std::size_t;
  auto total_risk_level(ElevationConstView map) -> std::size_t;
  auto basin_map(ElevationConstView map) -> std::vector<int>;
  auto histogrammize(std::span<int const> basin_map) -> std::vector<std::size_t>;
  auto product_of_top_3(std::span<std::size_t const> data) -> std::size_t;

}// namespace Day09

namespace AoC {

  template <>
  struct Solution<9> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    explicit Solution(std::pair<std::vector<int>, Day09::ElevationConstView>);
    std::vector<int> elevations;
    Day09::ElevationConstView elevations_view;
  };

}// namespace AoC
