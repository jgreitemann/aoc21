#include "solution.h"

#include <cassert>
#include <queue>

namespace Day19 {

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
          -> cor3ntin::rangesnext::generator<std::vector<Point>> {
    std::vector<Point> target_vec(target.begin(), target.end());
    for (auto const &target_pivot : target_vec) {
      for (auto reference_point : reference) {
        std::ranges::transform(reference_point, target_pivot, reference_point.begin(),
                               std::minus<>{});
        for (auto &target_point : target_vec)
          std::ranges::transform(target_point, reference_point, target_point.begin(),
                                 std::plus<>{});
        co_yield target_vec;
      }
    }
  }

  auto overlap(std::span<Point const> target, std::span<Point const> sorted_reference,
               std::size_t threshold) -> std::vector<Point> {
    assert(std::ranges::is_sorted(sorted_reference));

    for (auto &&oriented_target : orientations(target)) {
      for (auto translated_target : translations(oriented_target, sorted_reference)) {
        std::ranges::sort(translated_target);
        std::vector<Point> intersection;
        std::ranges::set_intersection(translated_target, sorted_reference,
                                      std::back_inserter(intersection));
        if (intersection.size() >= threshold) {
          std::vector<Point> overlapping_union;
          std::ranges::set_union(translated_target, sorted_reference,
                                 std::back_inserter(overlapping_union));

          return overlapping_union;
        }
      }
    }

    return {};
  }

  auto reconstruct_vec(std::vector<std::vector<Point>> scanners, std::size_t threshold)
          -> std::vector<Point> {
    std::queue<std::vector<Point>> queue;
    std::vector<Point> beacons = scanners.front();
    std::ranges::sort(beacons);
    auto process = [&](std::vector<Point> &&scanner) {
      auto new_beacons = overlap(scanner, beacons, threshold);
      if (new_beacons.empty())
        queue.push(std::move(scanner));
      else
        beacons.swap(new_beacons);
    };

    for (auto &scanner : scanners)
      process(std::move(scanner));

    while (!queue.empty()) {
      process(std::move(queue.front()));
      queue.pop();
    }

    return beacons;
  }

}// namespace Day19

namespace AoC {

  Solution<19>::Solution(std::istream &stream)
      : scanner_data{Day19::parse_scanners(stream)} {}

  auto Solution<19>::part1() const -> std::size_t {
    return Day19::reconstruct(scanner_data, 12).size();
  }

}// namespace AoC
