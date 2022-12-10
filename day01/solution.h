#pragma once

#include "../solution.h"

#include <span>
#include <utility>
#include <vector>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day01 {

  template <std::size_t N, typename R>
  auto sliding_window(R &&range)
          -> cor3ntin::rangesnext::generator<decltype(std::ranges::subrange{range})> {
    auto begin = range.begin(), end = range.begin();

    for (std::size_t i = 0; i < N; ++i) {
      if (end == range.end()) co_return;
      ++end;
    }

    for (; end != range.end(); ++begin, ++end) co_yield std::ranges::subrange{begin, end};

    co_yield std::ranges::subrange{begin, end};
  }

  auto number_of_increases(std::span<int const> measurements) -> std::size_t;
  auto sliding_window_sums(std::span<int const> measurements) -> std::vector<int>;

}// namespace Day01

namespace AoC {

  template <>
  struct Solution<1> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    std::vector<int> measurements;
  };

}// namespace AoC
