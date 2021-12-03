#pragma once

#include "../solution.h"

#include <span>
#include <vector>

namespace Day03 {
  auto most_common_bits(std::vector<std::string> const& report) -> std::string;
  auto binary_to_decimal(std::string const& binary_string ) -> int;
  auto binary_complement(int number, int size) -> int;
}

namespace AoC {

  template <>
  struct Solution<3> {
    explicit Solution(std::istream &);
    auto part1() const -> int;

  private:
    std::vector<std::string> report;
  };

}// namespace AoC
