#include <fmt/format.h>

#include "day01/solution.h"
#include "day02/solution.h"
#include "day03/solution.h"
#include "day04/solution.h"
#include "day05/solution.h"
#include "day06/solution.h"
#include "day07/solution.h"
#include "day08/solution.h"

#include "input.h"
#include "solution.h"

extern template struct AoC::Solution<1>;
extern template struct AoC::Solution<2>;
extern template struct AoC::Solution<3>;
extern template struct AoC::Solution<4>;
extern template struct AoC::Solution<5>;
extern template struct AoC::Solution<6>;
extern template struct AoC::Solution<7>;
extern template struct AoC::Solution<8>;

template <typename ThisSolution>
void handle_day(int day) {
  if constexpr (AoC::partially_solved<ThisSolution>) {
    auto stream = AoC::input_stream(day);
    ThisSolution solution{stream};
    fmt::print("Day {:02}, Part 1: {}\n", day, solution.part1());
    if constexpr (AoC::fully_solved<ThisSolution>) {
      fmt::print("Day {:02}, Part 2: {}\n", day, solution.part2());
    }
  }
}

template <int... Days>
void handle_all_days(std::integer_sequence<int, 0, Days...>) {
  (handle_day<AoC::Solution<Days>>(Days), ...);
}

int main() {
  handle_all_days(std::make_integer_sequence<int, 26>{});
}
