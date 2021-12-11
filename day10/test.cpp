#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <ranges>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>
#include <fmt/core.h>

using namespace Day10;
using namespace Day10::Lints;
using namespace std::string_view_literals;

constexpr std::array EXAMPLE_LINES{"[({(<(())[]>[[{[]{<()<>>"sv, "[(()[<>])]({[<{<<[]>>("sv,
                                   "{([(<{}[<>[]}>{[]{[(<()>"sv, "(((({<>}<{<{<>}{[]{[]{}"sv,
                                   "[[<[([]))<([[{}[[()]]]"sv,   "[{[{({}]{}}([{[{{{}}([]"sv,
                                   "{<[[]]>}<{[{[{[]{()[[[]"sv,  "[<(<(<(<{}))><([]([]()"sv,
                                   "<{([([[(<>()){}]>(<<{{"sv,   "<{([{{}}[<[[[<>{}]]]>[]]"sv};

static const std::array<Lint, EXAMPLE_LINES.size()> EXAMPLE_LINTS{
        Incomplete{"}}]])})]"},  Incomplete{")}>]})"}, Corrupted{']', '}'},
        Incomplete{"}}>}>))))"}, Corrupted{']', ')'},  Corrupted{')', ']'},
        Incomplete{"]]}}]}]}>"}, Corrupted{'>', ')'},  Corrupted{']', '>'},
        Incomplete{"])}>"}};

TEST(Day10, lint) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(EXAMPLE_LINES | std::views::transform(lint) | to<std::vector>(),
              ElementsAreArray(EXAMPLE_LINTS));
}

TEST(Day10, error_score) {
  EXPECT_EQ(error_score(Corrupted{']', '}'}), 1197);
  EXPECT_EQ(error_score(Corrupted{']', ')'}), 3);
  EXPECT_EQ(error_score(Corrupted{')', ']'}), 57);
  EXPECT_EQ(error_score(Corrupted{'>', ')'}), 3);
  EXPECT_EQ(error_score(Corrupted{']', '>'}), 25137);
}

TEST(Day10, total_corrupted_score) {
  EXPECT_EQ(total_corrupted_score(EXAMPLE_LINTS), 26397);
}

TEST(Day10, appending_completion_strings_results_in_Ok_lines) {
  for (auto line : EXAMPLE_LINES) {
    auto lint = Day10::lint(line);
    if (std::holds_alternative<Incomplete>(lint)) {
      EXPECT_TRUE(std::holds_alternative<Ok>(
              Day10::lint(fmt::format("{}{}", line, std::get<Incomplete>(lint).completion))));
    }
  }
}

TEST(Day10, completion_score) {
  EXPECT_EQ(completion_score("}}]])})]"), 288957);
  EXPECT_EQ(completion_score(")}>]})"), 5566);
  EXPECT_EQ(completion_score("}}>}>))))"), 1480781);
  EXPECT_EQ(completion_score("]]}}]}]}>"), 995444);
  EXPECT_EQ(completion_score("])}>"), 294);
}

TEST(Day10, mean_completion_score) {
  EXPECT_EQ(mean_completion_score(EXAMPLE_LINTS), 288957);
}
