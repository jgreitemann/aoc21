#include "solution.h"
#include "../utils.h"

#include <ranges>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day10 {

  constexpr auto closing_bracket(char opening) noexcept -> char {
    switch (opening) {
      case '(':
        return ')';
      case '[':
        return ']';
      case '{':
        return '}';
      case '<':
        return '>';
      default:
        return '\0';
    }
  }

  auto lint(std::string_view line) -> Lint {
    using cor3ntin::rangesnext::to;
    std::vector<char> expected_closing_brackets;
    for (char c : line) {
      if (auto needed_closing_bracket = closing_bracket(c)) {
        expected_closing_brackets.push_back(needed_closing_bracket);
      } else {
        if (!expected_closing_brackets.empty() && c == expected_closing_brackets.back())
          expected_closing_brackets.pop_back();
        else
          return Lints::Corrupted{expected_closing_brackets.back(), c};
      }
    }

    if (expected_closing_brackets.empty())
      return Lints::Ok{};
    else
      return Lints::Incomplete{
              std::string{expected_closing_brackets.crbegin(), expected_closing_brackets.crend()}};
  }

  auto error_score(Lints::Corrupted lint) -> std::size_t {
    switch (lint.found) {
      case ')':
        return 3;
      case ']':
        return 57;
      case '}':
        return 1197;
      case '>':
        return 25137;
      default:
        return 0;
    }
  }

  auto completion_score(std::string_view completion) -> std::size_t {
    auto value = [](char c) -> std::size_t {
      switch (c) {
        case ')':
          return 1;
        case ']':
          return 2;
        case '}':
          return 3;
        case '>':
          return 4;
        default:
          return 0;
      }
    };

    return std::accumulate(
            completion.cbegin(), completion.cend(), 0ul,
            [value](std::size_t acc, char closing) { return 5 * acc + value(closing); });
  }

}// namespace Day10

namespace AoC {

  Solution<10>::Solution(std::istream &stream)
      : lints(AoC::lines(stream) | std::views::transform(Day10::lint)
              | cor3ntin::rangesnext::to<std::vector>()) {}

  auto Solution<10>::part1() const -> std::size_t { return Day10::total_corrupted_score(lints); }

  auto Solution<10>::part2() const -> std::size_t { return Day10::mean_completion_score(lints); }

}// namespace AoC
