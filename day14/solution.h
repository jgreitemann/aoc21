#pragma once

#include "../solution.h"
#include "../utils.h"

#include <span>
#include <unordered_map>
#include <vector>

namespace Day14 {

  struct Rule {
    std::array<char, 2> seq;
    char snippet;
    constexpr bool operator==(Rule const &) const noexcept = default;
  };

  auto parse_rules(std::istream &stream) -> std::vector<Rule>;
  auto react(std::string polymer, std::span<Rule const> rules) -> std::string;
  auto chain_react(std::string polymer, std::span<Rule const> rules, std::size_t times)
          -> std::string;
  auto histogrammize(std::string_view polymer) -> std::unordered_map<char, std::size_t>;
  auto minmax_diff(std::unordered_map<char, std::size_t> const &histogram) -> std::size_t;

}// namespace Day14

namespace AoC {

  template <>
  struct Solution<14> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::string polymer_template;
    std::vector<Day14::Rule> rules;
  };

}// namespace AoC
