#include "solution.h"

#include <limits>
#include <regex>

namespace Day17 {

  auto parse_rectangle(std::string_view desc) -> std::optional<Rectangle> {
    std::match_results<std::string_view::const_iterator> match;
    std::regex re{R"(target area: x=(-?\d+)..(-?\d+), y=(-?\d+)..(-?\d+))"};
    if (std::regex_search(desc.begin(), desc.end(), match, re)) {
      return Rectangle{{std::stoi(match[1]), std::stoi(match[3])},
                       {std::stoi(match[2]), std::stoi(match[4])}};
    } else {
      return std::nullopt;
    }
  }

  auto trajectory(Point v) -> cor3ntin::rangesnext::generator<Point> {
    Point p{};
    while (true) {
      p += v;

      if (v.x < 0)
        v.x += 1;
      else if (v.x > 0)
        v.x -= 1;

      v.y -= 1;

      co_yield p;
    }
  }

  auto maximum_height_of_trajectory(Point v, Rectangle const &target) -> std::optional<int> {
    int max_height = std::numeric_limits<int>::min();
    for (Point p : trajectory(v)) {
      max_height = std::max(p.y, max_height);
      if (target.contains(p))
        return max_height;
      if (p.y < target.bottom_left.y)
        return std::nullopt;
    }
    return std::nullopt;
  }

  static auto search_area(Rectangle const &target) -> Rectangle {
    return Rectangle{{0, target.bottom_left.y},
                     {target.top_right.x, 3 * std::abs(target.bottom_left.y)}};
  }

  auto search_optimal_trajectory(Rectangle const &target) -> int {
    int max_height = std::numeric_limits<int>::min();

    for (Point v : all_points(search_area(target))) {
      auto peak = maximum_height_of_trajectory(v, target);
      if (peak)
        max_height = std::max(max_height, *peak);
    }
    return max_height;
  }

  auto count_valid_trajectories(Rectangle const &target) -> std::size_t {
    std::size_t count = 0;

    for (Point v : all_points(search_area(target))) {
      count += maximum_height_of_trajectory(v, target).has_value();
    }
    return count;
  }

}// namespace Day17

namespace AoC {

  Solution<17>::Solution(std::istream &stream)
      : target{Day17::parse_rectangle(AoC::as_string(stream)).value()} {}


  auto Solution<17>::part1() const -> int { return Day17::search_optimal_trajectory(target); }

  auto Solution<17>::part2() const -> std::size_t {
    return Day17::count_valid_trajectories(target);
  }

}// namespace AoC
