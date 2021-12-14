#include "solution.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <set>

#include <cor3ntin/rangesnext/enumerate.hpp>

namespace Day14 {

  auto parse_rules(std::istream &stream) -> std::vector<Rule> {
    using cor3ntin::rangesnext::to;
    return AoC::lines(stream) | std::views::transform([](std::string_view line) {
             return Rule{std::array{line[0], line[1]}, line[6]};
           })
           | to<std::vector>();
  }

  auto react(std::string polymer, std::span<Rule const> rules) -> std::string {
    std::vector<std::optional<char>> insertions;
    insertions.reserve(polymer.size() - 1);
    std::adjacent_difference(
            polymer.begin(), polymer.end(), std::back_inserter(insertions),
            [rules](char rhs, char lhs) -> std::optional<char> {
              if (auto it = std::ranges::find(rules, std::array{lhs, rhs}, &Rule::seq);
                  it != rules.end()) {
                return it->snippet;
              } else {
                return std::nullopt;
              }
            });
    auto count = insertions.size() - std::ranges::count(insertions, std::optional<char>{});
    polymer.reserve(polymer.size() + count);

    using cor3ntin::rangesnext::enumerate;
    for (auto [i, insertion] : insertions | enumerate | std::views::drop(1) | std::views::reverse
                                       | std::views::filter([](auto pair) {
                                           auto &&[index, insertion] = pair;
                                           return insertion.has_value();
                                         })) {
      polymer.insert(polymer.begin() + i, *insertion);
    }

    return polymer;
  }

  auto react(CompressedPolymer polymer, std::span<Rule const> rules) -> CompressedPolymer {
    polymer.react(rules);
    return polymer;
  }

  auto histogrammize(std::string_view polymer) -> std::unordered_map<char, std::size_t> {
    using cor3ntin::rangesnext::to;
    auto stats = polymer | to<std::multiset>();
    std::unordered_map<char, std::size_t> histogram;
    for (auto it = stats.begin(); it != stats.end(); it = stats.upper_bound(*it))
      histogram[*it] = stats.count(*it);
    return histogram;
  }

  auto minmax_diff(std::unordered_map<char, std::size_t> const &histogram) -> std::size_t {
    auto [min, max] = std::ranges::minmax(
            histogram | std::views::transform([](auto const &p) { return p.second; }));
    return max - min;
  }

  CompressedPolymer::CompressedPolymer(std::string_view polymer)
      : start{polymer.front()}
      , end{polymer.back()} {
    std::multiset<std::array<char, 2>> seqs;
    std::transform(polymer.begin(), polymer.end() - 1, polymer.begin() + 1,
                   std::inserter(seqs, seqs.end()), [](char a, char b) {
                     return std::array{a, b};
                   });
    for (auto it = seqs.begin(); it != seqs.end(); it = seqs.upper_bound(*it))
      seq_histo.emplace(*it, seqs.count(*it));
  }

  auto CompressedPolymer::histogram() const -> std::unordered_map<char, std::size_t> {
    auto histo = std::unordered_map<char, std::size_t>{};
    for (auto [seq, count] : seq_histo) {
      histo[seq[0]] += count;
      histo[seq[1]] += count;
    }
    histo[start]++;
    histo[end]++;
    for (auto &[c, count] : histo)
      count /= 2;
    return histo;
  }

  void CompressedPolymer::react(std::span<const Rule> rules) {
    std::unordered_map<std::array<char, 2>, std::size_t> new_seq_histo;
    for (auto const &[seq, count] : seq_histo) {
      auto insertion = std::ranges::find(rules, seq, &Rule::seq)->snippet;
      new_seq_histo[std::array{seq[0], insertion}] += count;
      new_seq_histo[std::array{insertion, seq[1]}] += count;
    }
    seq_histo = std::move(new_seq_histo);
  }

}// namespace Day14

namespace AoC {

  Solution<14>::Solution(std::istream &stream)
      : polymer_template{[&] {
        std::string line1, line2;
        std::getline(stream, line1);
        std::getline(stream, line2);
        return line1;
      }()}
      , rules{Day14::parse_rules(stream)} {}

  auto Solution<14>::part1() const -> std::size_t {
    return Day14::minmax_diff(
            Day14::histogrammize(Day14::chain_react(polymer_template, rules, 10)));
  }

  auto Solution<14>::part2() const -> std::size_t {
    return Day14::minmax_diff(
            Day14::chain_react(Day14::CompressedPolymer{polymer_template}, rules, 40).histogram());
  }

}// namespace AoC
