#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day18 {

  auto magnitude(std::string_view number) -> std::size_t;
  auto try_explode(std::string &number) -> bool;
  auto try_split(std::string &number) -> bool;
  void reduce(std::string &number);
  auto add(std::string_view lhs, std::string_view rhs) -> std::string;
  auto add_all(std::ranges::input_range auto &&rng) -> std::string {
    return AoC::accumulate(rng | std::views::drop(1), std::string{*rng.begin()}, add);
  }

}// namespace Day18

namespace AoC {

  template <>
  struct Solution<18> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<std::string> summands;
  };

}// namespace AoC
