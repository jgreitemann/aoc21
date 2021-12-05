#include "solution.h"
#include "../utils.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day01 {

  auto number_of_increases(std::span<int const> measurements) -> std::size_t {
    std::vector<int> differences;
    differences.reserve(measurements.size());

    std::adjacent_difference(measurements.begin(), measurements.end(),
                             std::back_inserter(differences));

    return std::ranges::count_if(differences | std::views::drop(1),
                                 [](int delta) { return delta > 0; });
  }

  auto sliding_window_sums(std::span<int const> measurements) -> std::vector<int> {
    using cor3ntin::rangesnext::to;
    return sliding_window<3>(measurements) | std::views::transform([](auto &&window) {
             return std::accumulate(window.begin(), window.end(), 0);
           })
           | to<std::vector>();
  }

}// namespace Day01

namespace AoC {

  Solution<1>::Solution(std::istream &stream)
      : measurements{AoC::parse_vec<int>(stream)} {}

  auto Solution<1>::part1() const -> std::size_t {
    return Day01::number_of_increases(measurements);
  }

  auto Solution<1>::part2() const -> std::size_t {
    return Day01::number_of_increases(Day01::sliding_window_sums(measurements));
  }

}// namespace AoC
