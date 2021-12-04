#include "solution.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day01 {

  auto parse(std::istream &stream) -> std::vector<int> {
    using cor3ntin::rangesnext::to;
    return std::ranges::subrange{std::istream_iterator<int>{stream}, std::istream_iterator<int>{}} | to<std::vector>();
  }

  auto number_of_increases(std::span<int const> measurements) -> std::size_t {
    std::vector<int> differences;
    differences.reserve(measurements.size());

    std::adjacent_difference(measurements.begin(), measurements.end(), std::back_inserter(differences));

    return std::ranges::count_if(differences | std::views::drop(1),
                                 [](int delta) { return delta > 0; });
  }

}// namespace Day01

namespace AoC {

  Solution<1>::Solution(std::istream &stream)
      : measurements{Day01::parse(stream)} {
  }

  auto Solution<1>::part1() const -> std::size_t {
    return Day01::number_of_increases(measurements);
  }

}// namespace AoC