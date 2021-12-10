#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <ranges>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day10;
using namespace Day10::Lints;
using namespace std::string_view_literals;

constexpr std::array EXAMPLE_LINES{"[({(<(())[]>[[{[]{<()<>>"sv, "[(()[<>])]({[<{<<[]>>("sv,
                                   "{([(<{}[<>[]}>{[]{[(<()>"sv, "(((({<>}<{<{<>}{[]{[]{}"sv,
                                   "[[<[([]))<([[{}[[()]]]"sv,   "[{[{({}]{}}([{[{{{}}([]"sv,
                                   "{<[[]]>}<{[{[{[]{()[[[]"sv,  "[<(<(<(<{}))><([]([]()"sv,
                                   "<{([([[(<>()){}]>(<<{{"sv,   "<{([{{}}[<[[[<>{}]]]>[]]"sv};

constexpr std::array<Lint, EXAMPLE_LINES.size()> EXAMPLE_LINTS{
        Incomplete{},        Incomplete{},        Corrupted{']', '}'}, Incomplete{},
        Corrupted{']', ')'}, Corrupted{')', ']'}, Incomplete{},        Corrupted{'>', ')'},
        Corrupted{']', '>'}, Incomplete{}};

TEST(Day10, lint) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(EXAMPLE_LINES | std::views::transform(lint) | to<std::vector>(),
              ElementsAreArray(EXAMPLE_LINTS));
}

TEST(Day10, score) {
  EXPECT_EQ(score(Corrupted{']', '}'}), 1197);
  EXPECT_EQ(score(Corrupted{']', ')'}), 3);
  EXPECT_EQ(score(Corrupted{')', ']'}), 57);
  EXPECT_EQ(score(Corrupted{'>', ')'}), 3);
  EXPECT_EQ(score(Corrupted{']', '>'}), 25137);
}

TEST(Day10, total_corrupted_score) {
  EXPECT_EQ(total_corrupted_score(EXAMPLE_LINTS), 26397);
}
