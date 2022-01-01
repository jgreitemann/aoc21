#include "solution.h"

#include <cassert>
#include <numeric>
#include <queue>

namespace Day19 {

  auto manhattan(Point const &lhs, Point const &rhs) -> int {
    return std::transform_reduce(lhs.begin(), lhs.end(), rhs.begin(), 0, std::plus<>{},
                                 [](int l, int r) { return std::abs(l - r); });
  }

  auto max_manhattan_distance(std::span<Point const> points) -> int {
    return std::ranges::max(AoC::pairs(points) | std::views::transform([](auto &&pair) {
                              return std::apply(manhattan, pair);
                            }));
  }

  auto parse_scanners(std::istream &stream) -> std::vector<std::vector<Point>> {
    std::vector<std::vector<Point>> scanners;
    std::string line;
    while (std::getline(stream, line)) {
      if (line.starts_with("---")) {
        scanners.emplace_back();
      } else if (!line.empty()) {
        auto first_comma_pos = line.find(',');
        auto last_comma_pos = line.rfind(',');
        scanners.back().push_back(Point{std::stoi(line.substr(0, first_comma_pos)),
                                        std::stoi(line.substr(first_comma_pos + 1, last_comma_pos)),
                                        std::stoi(line.substr(last_comma_pos + 1))});
      }
    }
    return scanners;
  }

  auto orientations(std::span<Point const> points)
          -> cor3ntin::rangesnext::generator<std::vector<Point>> {

    struct criss_cross {
      constexpr void operator()(Point &p) const noexcept {
        p[i] *= -1;
        std::swap(p[i], p[j]);
      }
      std::size_t i, j;
    };

    std::vector<Point> points_vec(points.begin(), points.end());
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 2});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{0, 2});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{0, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{0, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{0, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 2});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{1, 2});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 0});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
    std::ranges::for_each(points_vec, criss_cross{2, 1});
    co_yield points_vec;
  }

  auto translations(std::span<Point const> target, std::span<Point const> reference)
          -> cor3ntin::rangesnext::generator<std::pair<std::vector<Point>, Point>> {
    std::vector<Point> target_vec(target.begin(), target.end());
    for (auto const &target_pivot : target_vec) {
      for (auto reference_point : reference) {
        std::ranges::transform(reference_point, target_pivot, reference_point.begin(),
                               std::minus<>{});
        for (auto &target_point : target_vec)
          std::ranges::transform(target_point, reference_point, target_point.begin(),
                                 std::plus<>{});

        co_yield std::pair{target_vec, reference_point};

        for (auto &target_point : target_vec)
          std::ranges::transform(target_point, reference_point, target_point.begin(),
                                 std::minus<>{});
      }
    }
  }

  auto overlap(std::span<Point const> target, ReconstructResult const &sorted_reference,
               std::size_t threshold) -> std::optional<ReconstructResult> {
    assert(std::ranges::is_sorted(sorted_reference.beacons));

    for (auto &&oriented_target : orientations(target)) {
      for (auto [translated_target, scanner_pos] :
           translations(oriented_target, sorted_reference.beacons)) {
        std::ranges::sort(translated_target);
        std::vector<Point> intersection;
        std::ranges::set_intersection(translated_target, sorted_reference.beacons,
                                      std::back_inserter(intersection));
        if (intersection.size() >= threshold) {
          ReconstructResult overlapped_result{{}, sorted_reference.scanners};
          std::ranges::set_union(translated_target, sorted_reference.beacons,
                                 std::back_inserter(overlapped_result.beacons));
          overlapped_result.scanners.push_back(scanner_pos);
          return overlapped_result;
        }
      }
    }

    return std::nullopt;
  }

  auto reconstruct_vec(std::vector<std::vector<Point>> scanners, std::size_t threshold)
          -> ReconstructResult {
    std::queue<std::vector<Point>> queue;
    ReconstructResult result{scanners.front(), {Point{}}};
    std::ranges::sort(result.beacons);
    auto process = [&](std::vector<Point> &&scanner) {
      if (auto new_result = overlap(scanner, result, threshold))
        result = std::move(*new_result);
      else
        queue.push(std::move(scanner));
    };

    for (auto &scanner : scanners | std::views::drop(1))
      process(std::move(scanner));

    while (!queue.empty()) {
      process(std::move(queue.front()));
      queue.pop();
    }

    return result;
  }

}// namespace Day19

namespace AoC {

  Solution<19>::Solution(std::istream &stream)
      : reconstruction{Day19::reconstruct(Day19::parse_scanners(stream), 12)} {}

  auto Solution<19>::part1() const -> std::size_t { return reconstruction.beacons.size(); }

  auto Solution<19>::part2() const -> int {
    return Day19::max_manhattan_distance(reconstruction.scanners);
  }

}// namespace AoC
