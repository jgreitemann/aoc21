#pragma once

#include "../solution.h"
#include "../utils.h"

#include <span>
#include <unordered_map>
#include <vector>

namespace std {
  template <>
  struct hash<std::array<char, 2>> {
    auto operator()(std::array<char, 2> const &a) const noexcept -> std::size_t {
      return std::hash<char>{}(a[0]) ^ (std::hash<char>{}(a[1]) << 1);
    }
  };
}// namespace std

namespace Day14 {

  struct Rule {
    std::array<char, 2> seq;
    char snippet;
    constexpr bool operator==(Rule const &) const noexcept = default;
  };

  struct CompressedPolymer {
    char start, end;
    std::unordered_map<std::array<char, 2>, std::size_t> seq_histo;

    explicit CompressedPolymer(std::string_view polymer);
    auto histogram() const -> std::unordered_map<char, std::size_t>;
    void react(std::span<Rule const> rules);
  };

  auto parse_rules(std::istream &stream) -> std::vector<Rule>;
  auto react(std::string polymer, std::span<Rule const> rules) -> std::string;
  auto react(CompressedPolymer polymer, std::span<Rule const> rules) -> CompressedPolymer;

  auto chain_react(auto polymer, std::span<Rule const> rules, std::size_t times) {
    for (auto _ : std::views::iota(0ul, times))
      polymer = react(std::move(polymer), rules);
    return polymer;
  }

  auto histogrammize(std::string_view polymer) -> std::unordered_map<char, std::size_t>;
  auto minmax_diff(std::unordered_map<char, std::size_t> const &histogram) -> std::size_t;

}// namespace Day14

namespace AoC {

  template <>
  struct Solution<14> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    std::string polymer_template;
    std::vector<Day14::Rule> rules;
  };

}// namespace AoC
