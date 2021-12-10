#pragma once

#include "../solution.h"
#include "../utils.h"

#include <numeric>
#include <ranges>
#include <span>
#include <string>
#include <variant>
#include <vector>

namespace Day10 {

  namespace Lints {
    struct Ok {
      constexpr bool operator==(Ok const &) const noexcept = default;
    };

    struct Incomplete {
      constexpr bool operator==(Incomplete const &) const noexcept = default;
    };

    struct Corrupted {
      char expected;
      char found;
      constexpr bool operator==(Corrupted const &) const noexcept = default;
    };
  }// namespace Lints

  using Lint = std::variant<Lints::Ok, Lints::Incomplete, Lints::Corrupted>;

  auto lint(std::string_view line) -> Lint;
  auto score(Lints::Corrupted lint) -> std::size_t;

  constexpr auto total_corrupted_score(std::ranges::input_range auto &&all_lints) -> std::size_t {
    auto all_scores = all_lints | std::views::transform([](Lint const &lint) {
                        return std::visit(AoC::overload{[](Lints::Corrupted corrupted) {
                                                          return score(corrupted);
                                                        },
                                                        [](auto &&) { return 0ul; }},
                                          lint);
                      });
    return std::accumulate(all_scores.begin(), all_scores.end(), 0ul);
  }

}// namespace Day10

namespace AoC {

  template <>
  struct Solution<10> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<std::string> lines;
  };

}// namespace AoC
