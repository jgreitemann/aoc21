#pragma once

#include "../solution.h"
#include "../utils.h"

#include <ranges>
#include <span>

namespace Day19 {

  using Point = std::array<int, 3>;

  auto parse_scanners(std::istream &) -> std::vector<std::vector<Point>>;
  auto orientations(std::span<Point const> points)
          -> cor3ntin::rangesnext::generator<std::vector<Point>>;
  auto translations(std::span<Point const> target, std::span<Point const> reference)
          -> cor3ntin::rangesnext::generator<std::vector<Point>>;
  auto overlap(std::span<Point const> target, std::span<Point const> sorted_reference,
               std::size_t threshold) -> std::vector<Point>;
  auto reconstruct_vec(std::vector<std::vector<Point>> scanners, std::size_t threshold)
          -> std::vector<Point>;

  auto reconstruct(std::ranges::input_range auto &&scanners, std::size_t threshold)
          -> std::vector<Point> {
    using cor3ntin::rangesnext::to;
    return reconstruct_vec(scanners | std::views::transform([](auto &&rng) {
                             return rng | to<std::vector>();
                           }) | to<std::vector>(),
                           threshold);
  }

}// namespace Day19

namespace AoC {

  template <>
  struct Solution<19> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<std::vector<Day19::Point>> scanner_data;
  };

}// namespace AoC
