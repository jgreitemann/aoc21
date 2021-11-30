#include <fmt/format.h>

#include "day00/solution.h"
#include "input.h"
#include "solution.h"

extern template struct AoC::Solution<0>;

int main() {
  auto stream = AoC::input_stream(18);
  fmt::print("Day 00, Part 1: {}", AoC::Solution<0>::part1(stream));
}
