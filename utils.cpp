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

  auto parse_matrix(std::istream &stream) -> std::pair<std::vector<int>, View2D<int const>> {
    using cor3ntin::rangesnext::to;
    auto lines = AoC::lines(stream) | to<std::vector>();
    auto const line_len = lines.front().size();
    auto data = lines | std::views::join
                | std::views::transform([](char c) { return static_cast<int>(c - '0'); })
                | to<std::vector>();
    return {std::move(data), {data.data(), Dyn2DExtents{data.size() / line_len, line_len}}};
  }

  auto parse_char_image(std::istream &stream) -> std::pair<std::vector<char>, View2D<char>> {
    using cor3ntin::rangesnext::to;
    auto image_lines = lines(stream) | to<std::vector>();
    auto data = image_lines | std::views::join | to<std::vector>();
    return {std::move(data),
            {data.data(), Dyn2DExtents{image_lines.size(), image_lines.front().size()}}};
  }


}// namespace AoC
