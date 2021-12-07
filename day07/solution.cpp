#include "solution.h"
#include "../utils.h"

#include <numeric>
#include <ranges>

namespace Day07 {

  auto cost_to_align(std::span<int const> crabs, int pos, int (*profile)(int)) -> int {
    auto const distances =
            crabs | std::views::transform([=](int crab) { return profile(std::abs(crab - pos)); });
    return std::accumulate(distances.begin(), distances.end(), 0);
  }

  auto cheapest_aligned_position(std::span<int const> crabs, int (*profile)(int)) -> Alignment {
    auto [min_pos, max_pos] = std::ranges::minmax(crabs);
    return std::ranges::min(std::views::iota(min_pos, max_pos + 1)
                                    | std::views::transform([=](int pos) {
                                        return Alignment{pos, cost_to_align(crabs, pos, profile)};
                                      }),
                            std::less<>{}, &Alignment::cost);
  }

}// namespace Day07

namespace AoC {

  Solution<7>::Solution(std::istream &stream)
      : crabs{AoC::parse_comma_separated_ints_on_line(stream)} {}

  auto Solution<7>::part1() const -> int {
    return Day07::cheapest_aligned_position(crabs, Day07::identity).cost;
  }

  auto Solution<7>::part2() const -> int {
    return Day07::cheapest_aligned_position(crabs, Day07::gauss).cost;
  }

}// namespace AoC
