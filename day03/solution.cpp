#include "solution.h"
#include "../utils.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>


namespace Day03 {

  auto get_most_common_bit(std::span<std::string const> report, size_t col) -> char {
    size_t zeroes = std::ranges::count(
            report | std::views::transform([col](auto const &line) { return line[col]; }), '0');

    return report.size() >= 2 * zeroes ? '1' : '0';
  }

  auto get_least_common_bit(std::span<std::string const> report, size_t col) -> char {
    size_t zeroes = std::ranges::count(
            report | std::views::transform([col](auto const &line) { return line[col]; }), '0');

    return report.size() >= 2 * zeroes ? '0' : '1';
  }

  auto most_common_bits(std::vector<std::string> const &report) -> std::string {
    std::string result{};

    std::ranges::copy(std::views::iota(0ul, report.front().size())
                              | std::views::transform([&report](size_t col) {
                                  return get_most_common_bit(report, col);
                                }),
                      std::back_inserter(result));

    return result;
  }

  auto binary_to_decimal(std::string const &binary_string) -> int {
    return std::accumulate(binary_string.begin(), binary_string.end(), 0,
                           [](int acc, char bit) { return (acc << 1) + (bit == '1'); });
  }

  auto binary_complement(int number, int size) -> int { return (1 << size) - number - 1; }

  template <typename FilterStrategy>
  auto calculate_rating(std::span<std::string const> report, FilterStrategy &&strat)
          -> std::string {
    auto indices = std::views::iota(0ul, report.front().size()) | std::views::common;

    return std::accumulate(indices.begin(), indices.end(),
                           std::vector<std::string>{report.begin(), report.end()},
                           [&strat](auto list, std::size_t col) {
                             if (list.size() > 1) {
                               std::erase_if(list, [col, most_common_bit = strat(list, col)](
                                                           std::string const &line) {
                                 return line[col] != most_common_bit;
                               });
                             }
                             return list;
                           })
            .front();
  }

  auto calculate_oxygen_generator_rating(std::span<std::string const> report) -> std::string {
    return calculate_rating(report, get_most_common_bit);
  }

  auto calculate_CO2_scrubber_rating(std::span<std::string const> report) -> std::string {
    return calculate_rating(report, get_least_common_bit);
  }

}// namespace Day03

namespace AoC {

  Solution<3>::Solution(std::istream &stream)
      : report{AoC::parse_vec<std::string>(stream)} {}

  auto Solution<3>::part1() const -> int {
    using namespace Day03;
    int gamma = binary_to_decimal(most_common_bits(report));
    int epsilon = binary_complement(gamma, report.front().size());
    return gamma * epsilon;
  }

  auto Solution<3>::part2() const -> int {
    using namespace Day03;
    int oxygen_generator_rating = binary_to_decimal(calculate_oxygen_generator_rating(report));
    int CO2_scrubber_rating = binary_to_decimal(calculate_CO2_scrubber_rating(report));
    return oxygen_generator_rating * CO2_scrubber_rating;
  }

}// namespace AoC
