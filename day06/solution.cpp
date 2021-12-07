#include "solution.h"
#include "../utils.h"

#include <numeric>

namespace Day06 {

  auto histogrammize(std::span<int const> population) -> Census {
    return std::accumulate(population.begin(), population.end(), Census{}, [](Census c, int days) {
      c[static_cast<std::size_t>(days)]++;
      return c;
    });
  }

  auto transition(Census const &census) -> Census {
    Census new_census;
    new_census[0] = census[1];
    new_census[1] = census[2];
    new_census[2] = census[3];
    new_census[3] = census[4];
    new_census[4] = census[5];
    new_census[5] = census[6];
    new_census[6] = census[0] + census[7];
    new_census[7] = census[8];
    new_census[8] = census[0];
    return new_census;
  }

  auto transition_n(Census census, std::size_t n) -> Census {
    for (auto _ : std::views::iota(0ul, n))
      census = transition(census);
    return census;
  }

}// namespace Day06

namespace AoC {

  Solution<6>::Solution(std::istream &stream)
      : initial_census{Day06::histogrammize(AoC::parse_comma_separated_ints_on_line(stream))} {}

  auto Solution<6>::part1() const -> std::size_t {
    return Day06::number_of_fish(Day06::transition_n(initial_census, 80));
  }

  auto Solution<6>::part2() const -> std::size_t {
    return Day06::number_of_fish(Day06::transition_n(initial_census, 256));
  }

}// namespace AoC
