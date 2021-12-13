#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <sstream>
#include <string>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day13;

constexpr std::string_view EXAMPLE_INPUT = R"(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5)";

constexpr std::array EXAMPLE_DOTS = {
        Point{6, 10}, Point{0, 14}, Point{9, 10}, Point{0, 3},  Point{10, 4},  Point{4, 11},
        Point{6, 0},  Point{6, 12}, Point{4, 1},  Point{0, 13}, Point{10, 12}, Point{3, 4},
        Point{3, 0},  Point{8, 4},  Point{1, 10}, Point{2, 14}, Point{8, 10},  Point{9, 0}};

constexpr std::array EXAMPLE_DOTS_AFTER_1ST_FOLD = {
        Point{0, 0}, Point{2, 0}, Point{3, 0},  Point{6, 0}, Point{9, 0}, Point{0, 1},
        Point{4, 1}, Point{6, 2}, Point{10, 2}, Point{0, 3}, Point{4, 3}, Point{1, 4},
        Point{3, 4}, Point{6, 4}, Point{8, 4},  Point{9, 4}, Point{10, 4}};

constexpr std::array EXAMPLE_DOTS_AFTER_2ND_FOLD = {
        Point{0, 0}, Point{1, 0}, Point{2, 0}, Point{3, 0}, Point{4, 0}, Point{0, 1},
        Point{4, 1}, Point{0, 2}, Point{4, 2}, Point{0, 3}, Point{4, 3}, Point{0, 4},
        Point{1, 4}, Point{2, 4}, Point{3, 4}, Point{4, 4}};

constexpr std::array EXAMPLE_INSTRUCTIONS = {FoldInstruction{FoldDirection::Up, 7},
                                             FoldInstruction{FoldDirection::Left, 5}};

constexpr std::string_view EXAMPLE_RENDERED = R"(
#####
#...#
#...#
#...#
#####
)";

TEST(Day13, parse_input) {
  using cor3ntin::rangesnext::to;
  std::stringstream stream{std::string{EXAMPLE_INPUT}};
  auto lines = AoC::lines(stream) | to<std::vector>();
  auto empty = std::ranges::find(lines, std::string{});
  auto dots = Day13::parse_dots(std::span{lines.begin(), empty});
  auto instructions = Day13::parse_instructions(std::span{empty + 1, lines.end()});

  using ::testing::ElementsAreArray;
  EXPECT_THAT(dots, ElementsAreArray(EXAMPLE_DOTS));
  EXPECT_THAT(instructions, ElementsAreArray(EXAMPLE_INSTRUCTIONS));
}

TEST(Day13, dots_after_fold) {
  using ::testing::UnorderedElementsAreArray;
  EXPECT_THAT(fold(EXAMPLE_DOTS, std::array{EXAMPLE_INSTRUCTIONS[0]}),
              UnorderedElementsAreArray(EXAMPLE_DOTS_AFTER_1ST_FOLD));

  EXPECT_THAT(fold(EXAMPLE_DOTS, EXAMPLE_INSTRUCTIONS),
              UnorderedElementsAreArray(EXAMPLE_DOTS_AFTER_2ND_FOLD));
}

TEST(Day13, render) {
  EXPECT_EQ(render(fold(EXAMPLE_DOTS, EXAMPLE_INSTRUCTIONS)), EXAMPLE_RENDERED);
}
