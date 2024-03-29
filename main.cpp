#include <fmt/format.h>

#include "day01/solution.h"
#include "day02/solution.h"
#include "day03/solution.h"
#include "day04/solution.h"
#include "day05/solution.h"
#include "day06/solution.h"
#include "day07/solution.h"
#include "day08/solution.h"
#include "day09/solution.h"
#include "day10/solution.h"
#include "day11/solution.h"
#include "day12/solution.h"
#include "day13/solution.h"
#include "day14/solution.h"
#include "day15/solution.h"
#include "day16/solution.h"
#include "day17/solution.h"
#include "day18/solution.h"
#include "day19/solution.h"
#include "day20/solution.h"
#include "day21/solution.h"
#include "day22/solution.h"
#include "day24/solution.h"
#include "day25/solution.h"

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
extern template struct AoC::Solution<10>;
extern template struct AoC::Solution<11>;
extern template struct AoC::Solution<12>;
extern template struct AoC::Solution<13>;
extern template struct AoC::Solution<14>;
extern template struct AoC::Solution<15>;
extern template struct AoC::Solution<16>;
extern template struct AoC::Solution<17>;
extern template struct AoC::Solution<18>;
extern template struct AoC::Solution<19>;
extern template struct AoC::Solution<20>;
extern template struct AoC::Solution<21>;
extern template struct AoC::Solution<22>;
extern template struct AoC::Solution<24>;
extern template struct AoC::Solution<25>;

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

int main() try {
  handle_all_days(std::make_integer_sequence<int, 26>{});
} catch (std::exception const &e) {
  fmt::print("Error: {}\n", e.what());
  return 1;
}
