#include "solution.h"
#include "../utils.h"

#include <ranges>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day04 {

  auto parse_numbers(std::istream &stream) -> std::vector<int> {
    using cor3ntin::rangesnext::to;
    using namespace std::string_view_literals;
    std::string first_line;
    if (std::getline(stream, first_line)) {
      return std::views::split(first_line, ","sv) | std::views::transform([](auto &&num) {
               auto common_num = num | std::views::common;
               return std::stoi(std::string{common_num.begin(), common_num.end()});
             })
             | to<std::vector>();
    } else {
      return {};
    }
  }

  auto parse_boards(std::istream &stream) -> std::vector<int> {
    return AoC::parse_vec<int>(stream);
  }

}// namespace Day04

namespace AoC {

  Solution<4>::Solution(std::istream &stream)
      : numbers{Day04::parse_numbers(stream)}
      , boards_storage{Day04::parse_boards(stream)} {}

  auto Solution<4>::part1() const -> std::size_t { return 42; }

}// namespace AoC
