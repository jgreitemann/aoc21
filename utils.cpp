#include "utils.h"

#include <iostream>
#include <iterator>
#include <ranges>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string {
    return {std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};
  }

  auto parse_comma_separated_ints_on_line(std::istream &stream) -> std::vector<int> {
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

  auto lines(std::istream &stream) -> cor3ntin::rangesnext::generator<std::string> {
    std::string line;
    while (std::getline(stream, line))
      co_yield std::move(line);
  }

}// namespace AoC
