#pragma once

#include <iosfwd>
#include <ranges>
#include <vector>

#include <cor3ntin/rangesnext/to.hpp>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string;

  template <typename T>
  auto parse_vec(std::istream &stream) -> std::vector<T> {
    using cor3ntin::rangesnext::to;
    return std::ranges::istream_view<T>(stream) | to<std::vector>();
  }

  template <typename... Bases>
  struct overload : Bases... {
    using Bases::operator()...;
  };

  template <typename... Bases>
  overload(Bases &&...) -> overload<Bases...>;

}// namespace AoC
