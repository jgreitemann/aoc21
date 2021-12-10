#include "solution.h"
#include "../utils.h"

#include <ranges>
#include <stack>

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
    std::stack<char> expected_closing_brackets;
    for (char c : line) {
      if (auto needed_closing_bracket = closing_bracket(c)) {
        expected_closing_brackets.push(needed_closing_bracket);
      } else {
        if (!expected_closing_brackets.empty() && c == expected_closing_brackets.top())
          expected_closing_brackets.pop();
        else
          return Lints::Corrupted{expected_closing_brackets.top(), c};
      }
    }

    if (expected_closing_brackets.empty())
      return Lints::Ok{};
    else
      return Lints::Incomplete{};
  }

  auto score(Lints::Corrupted lint) -> std::size_t {
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

}// namespace Day10

namespace AoC {

  Solution<10>::Solution(std::istream &stream)
      : lines(AoC::lines(stream) | cor3ntin::rangesnext::to<std::vector>()) {}

  auto Solution<10>::part1() const -> std::size_t {
    return Day10::total_corrupted_score(lines | std::views::transform(Day10::lint));
  }

}// namespace AoC
