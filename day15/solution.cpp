#include "solution.h"

#include <algorithm>
#include <limits>
#include <set>

namespace Day15 {

  auto least_risk_level_map(MapConstView map) -> std::vector<int> {
    using cor3ntin::rangesnext::to;

    std::vector<int> risks(map.size(), std::numeric_limits<int>::max());
    risks.front() = 0;
    MapView risks_map{risks.data(), map.extents()};

    std::set<Point> points_to_access = {Point{0, 1}, Point{1, 0}};

    while (!points_to_access.empty()) {
      auto p = *points_to_access.begin();

      auto min_neighboring_risk = std::ranges::min(
              AoC::neighboring_points(p, map.extents())
              | std::views::transform([&](Point q) { return risks_map(q.x, q.y); }));

      if (risks_map(p.x, p.y) > min_neighboring_risk + map(p.x, p.y)) {
        risks_map(p.x, p.y) = min_neighboring_risk + map(p.x, p.y);
        std::ranges::copy(AoC::surrounding_points(p, map.extents()),
                          std::inserter(points_to_access, points_to_access.end()));
      }

      points_to_access.erase(p);
    }

    return risks;
  }

  auto replicate_fivefold(MapConstView map) -> std::pair<std::vector<int>, MapConstView> {
    std::vector<int> new_data(map.size() * 25);
    MapView new_map{new_data.data(), AoC::Dyn2DExtents{map.extent(0) * 5, map.extent(1) * 5}};
    Point offset{map.extent(0), map.extent(1)};

    for (Point p : AoC::all_points(map.extents())) {
      for (Point q : AoC::all_points(AoC::Dyn2DExtents{5, 5})) {
        auto r = p + q * offset;
        new_map(r.x, r.y) = (map(p.x, p.y) + q.x + q.y - 1) % 9 + 1;
      }
    }

    return {std::move(new_data), new_map};
  }

}// namespace Day15

namespace AoC {

  Solution<15>::Solution(std::istream &stream)
      : Solution{AoC::parse_matrix(stream)} {}

  Solution<15>::Solution(std::pair<std::vector<int>, Day15::MapConstView> pair)
      : data{std::move(pair.first)}
      , map{pair.second} {}

  auto Solution<15>::part1() const -> int { return Day15::least_risk_level_map(map).back(); }

  auto Solution<15>::part2() const -> int {
    auto [repl_data, repl_map] = Day15::replicate_fivefold(map);
    return Day15::least_risk_level_map(repl_map).back();
  }

}// namespace AoC
