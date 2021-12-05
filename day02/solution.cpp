#include "solution.h"
#include "../utils.h"

#include <numeric>
#include <ranges>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day02 {

  std::istream &operator>>(std::istream &is, Command &cmd) {
    std::string direction;
    int amount;
    is >> direction >> amount;
    if (direction == "forward") cmd = HorizontalDive{amount};
    else if (direction == "up")
      cmd = VerticalDive{amount};
    else if (direction == "down")
      cmd = VerticalDive{-amount};
    else
      is.setstate(std::ios_base::failbit);
    return is;
  }

  auto track_sub1(std::span<Command const> course) -> Position {
    return std::accumulate(
            course.begin(), course.end(), Position{}, [](Position pos, Command const &cmd) {
              std::visit(AoC::overload{
                                 [&pos](HorizontalDive hdive) { pos.lateral += hdive.translation; },
                                 [&pos](VerticalDive vdive) { pos.depth -= vdive.amount; }},
                         cmd);
              return pos;
            });
  }

  auto track_sub2(std::span<Command const> course) -> Position {
    return std::accumulate(
            course.begin(), course.end(), Position{}, [](Position pos, Command const &cmd) {
              std::visit(AoC::overload{[&pos](HorizontalDive hdive) {
                                         pos.lateral += hdive.translation;
                                         pos.depth += pos.aim * hdive.translation;
                                       },
                                       [&pos](VerticalDive vdive) { pos.aim -= vdive.amount; }},
                         cmd);
              return pos;
            });
  }

}// namespace Day02

namespace AoC {

  Solution<2>::Solution(std::istream &stream)
      : course{AoC::parse_vec<Day02::Command>(stream)} {}

  auto Solution<2>::part1() const -> int {
    auto const final_pos = Day02::track_sub1(course);
    return final_pos.lateral * final_pos.depth;
  }

  auto Solution<2>::part2() const -> int {
    auto const final_pos = Day02::track_sub2(course);
    return final_pos.lateral * final_pos.depth;
  }

}// namespace AoC
