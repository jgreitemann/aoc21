#pragma once

#include "../solution.h"

#include <span>
#include <utility>
#include <vector>

#include <cor3ntin/rangesnext/generator.hpp>
#include <experimental/mdspan>

namespace Day05 {

  struct Point {
    int x, y;
    constexpr Point &operator+=(Point p) {
      x += p.x;
      y += p.y;
      return *this;
    }
    constexpr Point &operator-=(Point p) {
      x -= p.x;
      y -= p.y;
      return *this;
    }
    constexpr Point &operator*=(int s) {
      x *= s;
      y *= s;
      return *this;
    }
    constexpr Point &operator*=(Point p) {
      x *= p.x;
      y *= p.y;
      return *this;
    }
    constexpr Point &operator/=(int s) {
      x /= s;
      y /= s;
      return *this;
    }
    constexpr Point &operator/=(Point p) {
      x /= p.x;
      y /= p.y;
      return *this;
    }
    constexpr bool operator==(Point const &) const noexcept = default;
    [[nodiscard]] constexpr Point abs() const { return {std::abs(x), std::abs(y)}; }
  };

  constexpr Point operator+(Point lhs, Point rhs) { return lhs += rhs; }
  constexpr Point operator-(Point lhs, Point rhs) { return lhs -= rhs; }
  constexpr Point operator*(Point lhs, int rhs) { return lhs *= rhs; }
  constexpr Point operator*(int lhs, Point rhs) { return rhs *= lhs; }
  constexpr Point operator*(Point lhs, Point rhs) { return lhs *= rhs; }
  constexpr Point operator/(Point lhs, int rhs) { return lhs /= rhs; }
  constexpr Point operator/(int lhs, Point rhs) { return rhs /= lhs; }
  constexpr Point operator/(Point lhs, Point rhs) { return rhs /= lhs; }

  using Line = std::pair<Point, Point>;

  using Extents2D = std::experimental::extents<std::experimental::dynamic_extent,
                                               std::experimental::dynamic_extent>;
  using Image2DView = std::experimental::mdspan<int, Extents2D, std::experimental::layout_left>;

  auto parse(std::istream &stream) -> std::vector<Line>;
  auto get_extents(std::span<Line const> lines) -> Extents2D;
  auto is_paraxial(Line const &line) -> bool;
  auto points_on_line(Line const &line) -> cor3ntin::rangesnext::generator<Point>;
  void render(Image2DView image_view, std::span<Line const> lines);
  auto number_of_overlaps(std::span<int const> image) -> std::size_t;

}// namespace Day05

namespace AoC {

  template <>
  struct Solution<5> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    std::vector<Day05::Line> lines;
    Day05::Extents2D extents;
  };

}// namespace AoC
