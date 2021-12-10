#include "solution.h"
#include "../utils.h"

#include <numeric>

#include <cor3ntin/rangesnext/product.hpp>
#include <cor3ntin/rangesnext/to.hpp>

namespace Day09 {

  auto parse(std::istream &stream) -> std::pair<std::vector<int>, ElevationConstView> {
    using cor3ntin::rangesnext::to;
    auto lines = AoC::lines(stream) | to<std::vector>();
    auto const line_len = lines.front().size();
    auto elevations = lines | std::views::join
                      | std::views::transform([](char c) { return static_cast<int>(c - '0'); })
                      | to<std::vector>();
    return {std::move(elevations),
            ElevationConstView{elevations.data(),
                               Dyn2DExtents{elevations.size() / line_len, line_len}}};
  }

  auto surrounding_points(Point center, Dyn2DExtents ext)
          -> cor3ntin::rangesnext::generator<Point> {
    if (center.x + 1 < ext.extent(0))
      co_yield Point{center.x + 1, center.y};
    if (center.y + 1 < ext.extent(1))
      co_yield Point{center.x, center.y + 1};
    if (center.x > 0)
      co_yield Point{center.x - 1, center.y};
    if (center.y > 0)
      co_yield Point{center.x, center.y - 1};
  }

  bool is_local_minimum(ElevationConstView map, Point p) {
    return std::ranges::all_of(
            surrounding_points(p, map.extents()),
            [elev = map(p.x, p.y), map](Point q) { return map(q.x, q.y) > elev; });
  }

  auto all_points(Dyn2DExtents ext) {
    using cor3ntin::rangesnext::product;
    return cor3ntin::rangesnext::product(std::views::iota(0ul, ext.extent(0)),
                                         std::views::iota(0ul, ext.extent(1)))
           | std::views::transform([](auto pair) {
               auto [x, y] = pair;
               return Point{x, y};
             });
  }

  auto number_of_local_minima(ElevationConstView map) -> std::size_t {
    return std::ranges::count_if(all_points(map.extents()),
                                 [map](Point p) { return is_local_minimum(map, p); });
  }

  auto total_risk_level(ElevationConstView map) -> std::size_t {
    auto risk_levels = all_points(map.extents())
                       | std::views::filter([map](Point p) { return is_local_minimum(map, p); })
                       | std::views::transform([map](Point p) { return map(p.x, p.y) + 1; })
                       | std::views::common;

    return std::accumulate(risk_levels.begin(), risk_levels.end(), 0ul);
  }

  auto basin_map(ElevationConstView map) -> std::vector<int> {
    std::vector<int> basins(map.size(), 0);
    ElevationView basins_map{basins.data(), map.extents()};

    // Assign basin seed values to local minima
    std::ranges::generate(all_points(map.extents()) | std::views::filter([map](Point p) {
                            return is_local_minimum(map, p);
                          }) | std::views::transform([basins_map](Point p) -> int & {
                            return basins_map(p.x, p.y);
                          }),
                          [next_basin = 1]() mutable { return next_basin++; });

    // Successively grow basins, level-by-level
    for (int level : std::views::iota(1, 9)) {
      for (Point p : all_points(map.extents()) | std::views::filter([map, level](Point p) {
                       return map(p.x, p.y) == level && !is_local_minimum(map, p);
                     })) {
        basins_map(p.x, p.y) = std::ranges::max(
                surrounding_points(p, map.extents())
                | std::views::transform([basins_map](Point q) { return basins_map(q.x, q.y); }));
      }
    }

    return basins;
  }

  auto histogrammize(std::span<int const> basin_map) -> std::vector<std::size_t> {
    std::vector<std::size_t> histo(std::ranges::max(basin_map), 0);
    for (int i : basin_map | std::views::filter([](int i) { return i > 0; }))
      histo[static_cast<std::size_t>(i - 1)]++;
    return histo;
  }

  auto product_of_top_3(std::span<std::size_t const> data) -> std::size_t {
    std::array<std::size_t, 3> top_3{};
    std::ranges::partial_sort_copy(data, top_3, std::greater<>{});
    return std::accumulate(top_3.begin(), top_3.end(), 1ul, std::multiplies<>{});
  }

}// namespace Day09

namespace AoC {

  Solution<9>::Solution(std::istream &stream)
      : Solution(Day09::parse(stream)) {}

  Solution<9>::Solution(std::pair<std::vector<int>, Day09::ElevationConstView> p)
      : elevations{std::move(p.first)}
      , elevations_view{p.second} {}

  auto Solution<9>::part1() const -> std::size_t {
    return Day09::total_risk_level(elevations_view);
  }

  auto Solution<9>::part2() const -> std::size_t {
    return Day09::product_of_top_3(Day09::histogrammize(Day09::basin_map(elevations_view)));
  }

}// namespace AoC
