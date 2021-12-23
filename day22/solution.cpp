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

  auto points(RebootState const& state) -> std::vector<Point3D> {
    return state;
  }

  auto apply_reboot_step(RebootState const &state, RebootStep const &step) -> RebootState {
    RebootState res;
    auto const &[on, cuboid] = step;
    if (on)
      std::ranges::set_union(state, points(cuboid), std::back_inserter(res));
    else
      std::ranges::set_difference(state, points(cuboid), std::back_inserter(res));
    return res;
  }

  auto number_of_points(RebootState const &state) -> std::size_t { return state.size(); }

}// namespace Day22

namespace AoC {

  Solution<22>::Solution(std::istream &stream)
      : sequence{Day22::parse_sequence(stream)} {}

  auto Solution<22>::part1() const -> std::size_t {
    return Day22::number_of_points(
            Day22::reboot(sequence | Day22::clipped_steps(Day22::bounding_box)));
  }

}// namespace AoC
