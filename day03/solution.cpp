#include "solution.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>
#include <iostream>


namespace Day03 {

  auto parse(std::istream &stream) -> std::vector<std::string> {
    std::vector<std::string> v;
    std::copy(std::istream_iterator<std::string>{stream}, std::istream_iterator<std::string>{}, std::back_inserter(v));
    return v;
  }

  auto most_common_bits(std::vector<std::string> const &report) -> std::string {
    std::string result{};

    for (size_t i = 0; i < report.front().size(); i++) {
      size_t counter_0 = 0;
      size_t counter_1 = 0;
      for (auto const &line : report) {
        if (line[i] == '0')
          counter_0++;
        else
          counter_1++;
      }

      if (counter_0 > counter_1)
        result.push_back('0');
      else
        result.push_back('1');
    }

    return result;
  }

  auto binary_to_decimal(std::string const &binary_string) -> int {
    size_t acc = 0;

    for (size_t i = 0; i< binary_string.size(); i++)
    {
      acc <<= 1;
      acc += (binary_string[i]=='1');
    }

    return acc;
  }

  auto binary_complement(int number, int size) -> int
  {
    return (1 << size) - number - 1;
  }


}// namespace Day03

namespace AoC {

  Solution<3>::Solution(std::istream &stream)
      : report{Day03::parse(stream)} {
  }

  auto Solution<3>::part1() const -> int {
    using namespace Day03;
    int gamma = binary_to_decimal(most_common_bits(report));
    int epsilon = binary_complement(gamma, report.front().size());
    return gamma*epsilon;
  }

}// namespace AoC
