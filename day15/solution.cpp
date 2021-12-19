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

}// namespace Day15

namespace AoC {

  Solution<15>::Solution(std::istream &stream)
      : Solution{AoC::parse_matrix(stream)} {}

  Solution<15>::Solution(std::pair<std::vector<int>, Day15::MapConstView> pair)
      : data{std::move(pair.first)}
      , map{pair.second} {}

  auto Solution<15>::part1() const -> int { return Day15::least_risk_level_map(map).back(); }

}// namespace AoC
