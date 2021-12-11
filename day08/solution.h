#pragma once

#include "../solution.h"

#include <array>
#include <istream>
#include <string>
#include <vector>

namespace Day08 {

  struct Entry {
    std::array<std::string, 10> patterns;
    std::array<std::string, 4> output_digits;

    auto output() const -> std::size_t;
    bool operator==(Entry const &) const noexcept = default;
  };

  std::istream &operator>>(std::istream &stream, Entry &e);

  auto number_of_unique_output_digits(Entry const &e) -> std::size_t;
  void solve(std::array<std::string, 10> &patterns);

}// namespace Day08

namespace AoC {

  template <>
  struct Solution<8> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    std::vector<Day08::Entry> entries;
  };

}// namespace AoC
