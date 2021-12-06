#pragma once

#include "../solution.h"

#include <array>
#include <vector>

#include <experimental/mdspan>

namespace Day04 {

  using BoardsExtent = std::experimental::extents<std::experimental::dynamic_extent, 5, 5>;
  using BoardsConstView = std::experimental::mdspan<int const, BoardsExtent>;
  using BoardsView = std::experimental::mdspan<int, BoardsExtent>;

  auto parse_numbers(std::istream &stream) -> std::vector<int>;
  auto parse_boards(std::istream &stream) -> std::vector<int>;

}// namespace Day04

namespace AoC {

  template <>
  struct Solution<4> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<int> numbers;
    std::vector<int> boards_storage;
  };

}// namespace AoC
