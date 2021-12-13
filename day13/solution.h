#pragma once

#include "../solution.h"
#include "../utils.h"

#include <charconv>
#include <concepts>
#include <ranges>
#include <span>
#include <vector>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day13 {

  using Point = AoC::Point<int>;

  enum class FoldDirection {
    Left,
    Up,
  };

  struct FoldInstruction {
    FoldDirection direction;
    int distance;
    constexpr bool operator==(FoldInstruction const &) const noexcept = default;

    constexpr auto operator()(Point const &p) const noexcept -> Point;
  };

  auto parse_dots(std::span<std::string const> lines) -> std::vector<Point>;
  auto parse_instructions(std::span<std::string const> lines) -> std::vector<FoldInstruction>;
  auto fold(std::span<Point const> dots, std::span<FoldInstruction const> instructions)
          -> std::vector<Point>;
  auto render(std::span<Point const> dots) -> std::string;

}// namespace Day13

namespace AoC {

  template <>
  struct Solution<13> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::string;

  private:
    explicit Solution(std::vector<Day13::Point> &&dots,
                      std::vector<Day13::FoldInstruction> &&instructions);
    std::vector<Day13::Point> dots;
    std::vector<Day13::FoldInstruction> instructions;
  };

}// namespace AoC
