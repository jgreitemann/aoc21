#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day11 {

  using AoC::Dyn2DExtents;
  using Point = AoC::Point<std::size_t>;
  using EnergyView = AoC::View2D<int>;
  using EnergyConstView = AoC::View2D<int const>;

  auto step(EnergyView energies) -> std::size_t;
  auto multi_step(EnergyView energies, std::size_t count) -> std::size_t;
  auto steps_until_sync(EnergyView energies) -> std::size_t;

}// namespace Day11

namespace AoC {

  template <>
  struct Solution<11> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    explicit Solution(std::pair<std::vector<int>, Day11::EnergyConstView>);
    std::vector<int> initial_energies;
    Day11::EnergyConstView initial_energies_view;
  };

}// namespace AoC
