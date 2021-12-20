#pragma once

#include "../solution.h"
#include "../utils.h"

#include <optional>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day17 {

  using Point = AoC::Point<int>;

  struct Rectangle {
    Point bottom_left;
    Point top_right;

    constexpr bool operator==(Rectangle const &) const noexcept = default;

    constexpr bool contains(Point p) const noexcept {
      return bottom_left.x <= p.x && p.x <= top_right.x && bottom_left.y <= p.y
             && p.y <= top_right.y;
    }
  };

  constexpr auto all_points(Rectangle rect) {
    using cor3ntin::rangesnext::product;
    return cor3ntin::rangesnext::product(std::views::iota(rect.bottom_left.x, rect.top_right.x + 1),
                                         std::views::iota(rect.bottom_left.y, rect.top_right.y + 1))
           | std::views::transform([](auto pair) {
               auto [x, y] = pair;
               return Point{x, y};
             });
  }

  auto parse_rectangle(std::string_view desc) -> std::optional<Rectangle>;

  auto trajectory(Point v) -> cor3ntin::rangesnext::generator<Point>;

  auto maximum_height_of_trajectory(Point v, Rectangle const &target) -> std::optional<int>;

  auto search_optimal_trajectory(Rectangle const &target) -> int;

  auto count_valid_trajectories(Rectangle const &target) -> std::size_t;

}// namespace Day17

namespace AoC {

  template <>
  struct Solution<17> {
    explicit Solution(std::istream &);
    auto part1() const -> int;
    auto part2() const -> std::size_t;

  private:
    Day17::Rectangle target;
  };

}// namespace AoC
