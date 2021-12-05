#include "solution.h"
#include "../utils.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>


namespace Day03 {

  auto most_common_bits(std::vector<std::string> const &report) -> std::string {
    std::string result{};

    std::ranges::copy(std::views::iota(0ul, report.front().size())
                              | std::views::transform([&report](size_t col) {
                                  return std::ranges::count(
                                          report | std::views::transform([col](auto const &line) {
                                            return line[col];
                                          }),
                                          '0');
                                })
                              | std::views::transform([&report](size_t zeroes) {
                                  return report.size() > 2 * zeroes ? '1' : '0';
                                }),
                      std::back_inserter(result));

    return result;
  }

  auto binary_to_decimal(std::string const &binary_string) -> int {
    return std::accumulate(binary_string.begin(), binary_string.end(), 0,
                           [](int acc, char bit) { return (acc << 1) + (bit == '1'); });
  }

  auto binary_complement(int number, int size) -> int { return (1 << size) - number - 1; }


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

}// namespace AoC
