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
      std::string completion;
      bool operator==(Incomplete const &) const noexcept = default;
    };

    struct Corrupted {
      char expected;
      char found;
      constexpr bool operator==(Corrupted const &) const noexcept = default;
    };
  }// namespace Lints

  using Lint = std::variant<Lints::Ok, Lints::Incomplete, Lints::Corrupted>;

  auto lint(std::string_view line) -> Lint;
  auto error_score(Lints::Corrupted lint) -> std::size_t;

  template <std::ranges::input_range R>
  constexpr auto total_corrupted_score(R &&all_lints) -> std::size_t {
    auto all_scores = std::forward<R>(all_lints) | std::views::transform([](Lint const &lint) {
                        return std::visit(AoC::overload{[](Lints::Corrupted corrupted) {
                                                          return error_score(corrupted);
                                                        },
                                                        [](auto &&) { return 0ul; }},
                                          lint);
                      });
    return std::accumulate(all_scores.begin(), all_scores.end(), 0ul);
  }

  auto completion_score(std::string_view completion) -> std::size_t;

  template <std::ranges::input_range R>
  constexpr auto mean_completion_score(R &&all_lints) -> std::size_t {
    using cor3ntin::rangesnext::to;
    auto all_scores = std::forward<R>(all_lints) | std::views::filter([](Lint const &l) {
                        return std::holds_alternative<Lints::Incomplete>(l);
                      })
                      | std::views::transform([](Lint const &l) {
                          return completion_score(std::get<Lints::Incomplete>(l).completion);
                        })
                      | to<std::vector>();

    auto midpoint = all_scores.begin() + (all_scores.size() - 1) / 2;
    std::ranges::nth_element(all_scores, midpoint);
    return *midpoint;
  }

}// namespace Day10

namespace AoC {

  template <>
  struct Solution<10> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    std::vector<Day10::Lint> lints;
  };

}// namespace AoC
