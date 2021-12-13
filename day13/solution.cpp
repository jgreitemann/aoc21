#include "solution.h"

#include <algorithm>
#include <numeric>
#include <ranges>

namespace Day13 {

  auto parse_dots(std::span<std::string const> lines) -> std::vector<Point> {
    using cor3ntin::rangesnext::to;
    return lines | std::views::transform([](std::string_view line) {
             auto sep = line.find(',');
             Point dot;
             std::from_chars(line.data(), line.data() + sep, dot.x);
             std::from_chars(line.data() + sep + 1, line.data() + line.size(), dot.y);
             return dot;
           })
           | to<std::vector>();
  }

  auto parse_instructions(std::span<std::string const> lines) -> std::vector<FoldInstruction> {
    using cor3ntin::rangesnext::to;
    return lines | std::views::transform([](std::string_view line) {
             auto eq = line.find('=');
             FoldInstruction instr{line[eq - 1] == 'x' ? FoldDirection::Left : FoldDirection::Up};
             std::from_chars(line.data() + eq + 1, line.data() + line.size(), instr.distance);
             return instr;
           })
           | to<std::vector>();
  }

  constexpr auto FoldInstruction::operator()(const Point &p) const noexcept -> Point {
    switch (direction) {
      case FoldDirection::Left:
        return Point{p.x > distance ? (2 * distance - p.x) : p.x, p.y};
      case FoldDirection::Up:
        return Point{p.x, p.y > distance ? (2 * distance - p.y) : p.y};
    }
    return {};
  }

  auto fold(std::span<Point const> dots, std::span<FoldInstruction const> instructions)
          -> std::vector<Point> {
    using cor3ntin::rangesnext::to;
    auto folded = dots | std::views::transform([instructions](Point const &p) {
                    return std::accumulate(instructions.begin(), instructions.end(), p,
                                           [](Point const &q, FoldInstruction const &instruction) {
                                             return instruction(q);
                                           });
                  })
                  | to<std::vector>();
    std::ranges::sort(folded);
    auto [erase_first, erase_last] = std::ranges::unique(folded);
    folded.erase(erase_first, erase_last);
    return folded;
  }

  auto render(std::span<Point const> dots) -> std::string {
    auto max_x = std::ranges::max(dots | std::views::transform(&Point::x));
    auto max_y = std::ranges::max(dots | std::views::transform(&Point::y));
    auto display = std::vector(max_y + 1, std::string(max_x + 1, '.') + "\n");
    for (auto dot : dots) {
      display[dot.y][dot.x] = '#';
    }
    return std::accumulate(display.begin(), display.end(), std::string{"\n"});
  }

}// namespace Day13

namespace AoC {

  Solution<13>::Solution(std::istream &stream)
      : Solution{[&] {
        using cor3ntin::rangesnext::to;
        auto lines = AoC::lines(stream) | to<std::vector>();
        auto empty = std::ranges::find(lines, std::string{});
        return Solution{Day13::parse_dots(std::span{lines.begin(), empty}),
                        Day13::parse_instructions(std::span{empty + 1, lines.end()})};
      }()} {}

  Solution<13>::Solution(std::vector<Day13::Point> &&dots,
                         std::vector<Day13::FoldInstruction> &&instructions)
      : dots{std::move(dots)}
      , instructions{std::move(instructions)} {}

  auto Solution<13>::part1() const -> std::size_t {
    return Day13::fold(dots, std::array{instructions.front()}).size();
  }

  auto Solution<13>::part2() const -> std::string {
    return Day13::render(Day13::fold(dots, instructions));
  }

}// namespace AoC
