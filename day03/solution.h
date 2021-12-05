#pragma once

#include "../solution.h"

#include <span>
#include <vector>

namespace Day03 {
  auto most_common_bits(std::span<std::string const> report) -> std::string;
  auto binary_to_decimal(std::string const& binary_string) -> int;
  auto binary_complement(int number, int size) -> int;
  auto calculate_oxygen_generator_rating(std::span<std::string const> input) -> std::string;
  auto calculate_CO2_scrubber_rating(std::span<std::string const> input) -> std::string;
}

namespace AoC {

  template <>
  struct Solution<3> {
    explicit Solution(std::istream &);
    auto part1() const -> int;
    auto part2() const -> int;

  private:
    std::vector<std::string> report;
  };

}// namespace AoC
