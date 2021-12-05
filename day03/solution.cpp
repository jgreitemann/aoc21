#include "solution.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>


namespace Day03 {

  auto parse(std::istream &stream) -> std::vector<std::string> {
    std::vector<std::string> v;
    std::ranges::copy(std::ranges::istream_view<std::string>(stream), std::back_inserter(v));
    return v;
  }

  auto get_most_common_bit(std::vector<std::string> const &report, size_t col) -> char {
    size_t zeroes = std::ranges::count(
            report | std::views::transform([col](auto const &line) { return line[col]; }), '0');

    return report.size() >= 2 * zeroes ? '1' : '0';
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

  auto calculate_oxygen_generator_rating(std::vector<std::string> input) -> std::string {
    for (size_t col : std::views::iota(0ul, input.front().size())) {
      char most_common_bit = get_most_common_bit(input, col);
      std::erase_if(input, [col, most_common_bit](std::string const &line) {
        return line[col] != most_common_bit;
      });
      if (input.size() == 1) break;
    }
    return input.front();
  }


}// namespace Day03

namespace AoC {

  Solution<3>::Solution(std::istream &stream)
      : report{Day03::parse(stream)} {}

  auto Solution<3>::part1() const -> int {
    using namespace Day03;
    int gamma = binary_to_decimal(most_common_bits(report));
    int epsilon = binary_complement(gamma, report.front().size());
    return gamma * epsilon;
  }

  auto Solution<3>::part2() const -> int { return 42; }

}// namespace AoC
