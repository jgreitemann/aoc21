#include <fmt/format.h>

#include "day01/solution.h"
#include "input.h"
#include "solution.h"

extern template struct AoC::Solution<1>;

int main() {
  auto stream = AoC::input_stream(1);
  AoC::Solution<1> day01{stream};
  fmt::print("Day 01, Part 1: {}", day01.part1());
}
