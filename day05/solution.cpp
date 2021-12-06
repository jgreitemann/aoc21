#include "solution.h"
#include "../utils.h"

#include <algorithm>
#include <ranges>
#include <regex>
#include <vector>

#include <cor3ntin/rangesnext/to.hpp>

namespace Day05 {

  auto parse(std::istream &stream) -> std::vector<Line> {
    using cor3ntin::rangesnext::to;
    std::regex const re{R"((\d+),(\d+) -> (\d+),(\d+))"};

    return AoC::lines(stream) | std::views::transform([&re](std::string line) {
             std::smatch match;
             if (std::regex_match(line, match, re)) {
               return Line{Point{std::stoi(match[1].str()), std::stoi(match[2].str())},
                           Point{std::stoi(match[3].str()), std::stoi(match[4].str())}};
             } else {
               return Line{};
             }
           })
           | to<std::vector>();
  }

  auto get_extents(std::span<Line const> lines) -> Extents2D {
    auto max_dim = [lines](auto const &proj) {
      return std::invoke(proj, *std::ranges::max_element(lines, std::less<>{}, proj));
    };
    auto max_x = std::max(max_dim([](Line const &l) { return l.first.x; }),
                          max_dim([](Line const &l) { return l.second.x; }));
    auto max_y = std::max(max_dim([](Line const &l) { return l.first.y; }),
                          max_dim([](Line const &l) { return l.second.y; }));
    return Extents2D{max_x + 1, max_y + 1};
  }

  auto is_paraxial(Line const &line) -> bool {
    return line.first.x == line.second.x || line.first.y == line.second.y;
  }

  auto points_on_line(Line const &line) -> cor3ntin::rangesnext::generator<Point> {
    Point delta = line.second - line.first;
    delta /= delta.norm1();
    Point p = line.first;
    for (; p != line.second; p += delta)
      co_yield p;
    co_yield p;
  }

  void render(Image2DView image_view, std::span<Line const> lines) {
    for (Line const &line : lines)
      for (Point p : points_on_line(line))
        image_view(p.x, p.y)++;
  }

  auto number_of_overlaps(std::span<int const> image) -> std::size_t {
    return std::ranges::count_if(image, [](int pixel) { return pixel > 1; });
  }

}// namespace Day05

namespace AoC {

  Solution<5>::Solution(std::istream &stream)
      : lines{Day05::parse(stream)}
      , extents{Day05::get_extents(lines)} {}

  auto Solution<5>::part1() const -> std::size_t {
    using cor3ntin::rangesnext::to;
    auto const paraxial_lines = lines | std::views::filter(Day05::is_paraxial) | to<std::vector>();
    std::vector<int> image(extents.extent(0) * extents.extent(1));
    Day05::render(Day05::Image2DView{image.data(), extents}, paraxial_lines);
    return Day05::number_of_overlaps(image);
  }

  auto Solution<5>::part2() const -> std::size_t {
    std::vector<int> image(extents.extent(0) * extents.extent(1));
    Day05::render(Day05::Image2DView{image.data(), extents}, lines);
    return Day05::number_of_overlaps(image);
  }

}// namespace AoC
