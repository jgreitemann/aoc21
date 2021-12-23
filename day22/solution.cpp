#include "solution.h"

#include <fmt/ostream.h>
#include <regex>

namespace Day22 {

  auto Cuboid::clip(const Cuboid &other) const noexcept -> Cuboid {
    return Cuboid{std::max(x_min, other.x_min), std::min(x_max, other.x_max),
                  std::max(y_min, other.y_min), std::min(y_max, other.y_max),
                  std::max(z_min, other.z_min), std::min(z_max, other.z_max)};
  }

  auto operator<<(std::ostream &os, Cuboid const &cuboid) -> std::ostream & {
    fmt::print(os, "x={}..{},y={}..{},z={}..{}", cuboid.x_min, cuboid.x_max, cuboid.y_min,
               cuboid.y_max, cuboid.z_min, cuboid.z_max);
    return os;
  }

  auto parse_sequence(std::istream &stream) -> RebootSequence {
    using cor3ntin::rangesnext::to;
    return AoC::lines(stream) | std::views::transform([](std::string const &line) {
             std::regex re{
                     "(on|off) "
                     "x=(-?[0-9]+)..(-?[0-9]+),y=(-?[0-9]+)..(-?[0-9]+),z=(-?[0-9]+)..(-?[0-9]+)"};
             std::smatch match;
             std::regex_search(line, match, re);
             return std::pair{match[1].str() == "on",
                              Cuboid{std::stoi(match[2].str()), std::stoi(match[3].str()),
                                     std::stoi(match[4].str()), std::stoi(match[5].str()),
                                     std::stoi(match[6].str()), std::stoi(match[7].str())}};
           })
           | to<std::vector>();
  }

  auto points(RebootState const &state) -> std::vector<Point3D> {
    auto points_from_vec = [](std::vector<Cuboid> const &vec) {
      auto pts = AoC::accumulate(vec, std::vector<Point3D>{}, [](auto pts, Cuboid const &cuboid) {
        std::ranges::copy(points(cuboid), std::back_inserter(pts));
        return pts;
      });
      std::ranges::sort(pts);
      return pts;
    };
    auto pos_points = points_from_vec(state.pos);
    auto neg_points = points_from_vec(state.neg);
    std::vector<Point3D> diff{};
    std::ranges::set_difference(pos_points, neg_points, std::back_inserter(diff));
    return diff;
  }

  auto apply_reboot_step(RebootState state, RebootStep const &step) -> RebootState {
    using cor3ntin::rangesnext::to;
    auto filter_non_empty =
            std::views::filter([](auto const &c) { return number_of_points(c) > 0; });

    auto const &[on, cuboid] = step;
    auto new_neg = state.pos | clipped(cuboid) | filter_non_empty | to<std::vector>();
    std::ranges::copy(state.neg | clipped(cuboid) | filter_non_empty,
                      std::back_inserter(state.pos));
    std::ranges::copy(new_neg, std::back_inserter(state.neg));
    if (on)
      state.pos.push_back(cuboid);
    return state;
  }

  auto number_of_points(Cuboid const &cuboid) noexcept -> std::size_t {
    return static_cast<std::size_t>(std::max(0, cuboid.x_max - cuboid.x_min + 1))
           * static_cast<std::size_t>(std::max(0, cuboid.y_max - cuboid.y_min + 1))
           * static_cast<std::size_t>(std::max(0, cuboid.z_max - cuboid.z_min + 1));
  }

  auto number_of_points(RebootState const &state) -> std::size_t {
    auto to_number_of_points =
            std::views::transform([](Cuboid const &c) { return number_of_points(c); });
    return AoC::accumulate(state.pos | to_number_of_points, 0ul, std::plus<>{})
           - AoC::accumulate(state.neg | to_number_of_points, 0ul, std::plus<>{});
  }

}// namespace Day22

namespace AoC {

  Solution<22>::Solution(std::istream &stream)
      : sequence{Day22::parse_sequence(stream)} {}

  auto Solution<22>::part1() const -> std::size_t {
    return Day22::number_of_points(
            Day22::reboot(sequence | Day22::clipped_steps(Day22::bounding_box)));
  }

}// namespace AoC
