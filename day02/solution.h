#pragma once

#include "../solution.h"

#include <span>
#include <variant>
#include <vector>

namespace Day02 {

  struct HorizontalDive {
    int translation;
    bool operator==(HorizontalDive const &) const = default;
  };

  struct VerticalDive {
    int amount;
    bool operator==(VerticalDive const &) const = default;
  };

  using Command = std::variant<HorizontalDive, VerticalDive>;

  std::istream &operator>>(std::istream &is, Command &cmd);

  struct Position {
    int lateral;
    int depth;
    bool operator==(Position const &) const = default;
  };

  auto parse(std::istream &stream) -> std::vector<Command>;

  auto track_sub(std::span<Command const> course) -> Position;

}// namespace Day02

namespace AoC {

  template <>
  struct Solution<2> {
    explicit Solution(std::istream &);
    auto part1() const -> int;

  private:
    std::vector<Day02::Command> course;
  };

}// namespace AoC
