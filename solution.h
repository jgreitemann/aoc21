#pragma once

#include <iostream>
#include <iterator>
#include <string>

namespace AoC {

  template <typename T>
  concept partially_solved = std::constructible_from<T, std::istream &> && requires(T solution) {
    solution.part1();
  };

  template <typename T>
  concept fully_solved = partially_solved<T> && requires(T solution) {
    solution.part2();
  };

  template <int day>
  struct Solution {};

}// namespace AoC
