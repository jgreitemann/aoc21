#pragma once

#include "../solution.h"
#include "../utils.h"

#include <span>

namespace Day22 {

  struct Cuboid {
    int x_min{}, x_max{};
    int y_min{}, y_max{};
    int z_min{}, z_max{};

    constexpr auto operator<=>(Cuboid const &) const noexcept = default;
    auto clip(Cuboid const &other) const noexcept -> Cuboid;
  };

  auto operator<<(std::ostream &os, Cuboid const &cuboid) -> std::ostream &;

  using RebootStep = std::pair<bool, Day22::Cuboid>;
  using RebootSequence = std::vector<RebootStep>;
  using RebootSequenceView = std::span<RebootStep const>;

  auto parse_sequence(std::istream &stream) -> RebootSequence;

  using Point3D = std::tuple<int, int, int>;

  constexpr auto points(Cuboid const &cuboid) {
    using cor3ntin::rangesnext::product;
    return product(std::views::iota(cuboid.x_min, std::max(cuboid.x_min, cuboid.x_max + 1)),
                   std::views::iota(cuboid.y_min, std::max(cuboid.y_min, cuboid.y_max + 1)),
                   std::views::iota(cuboid.z_min, std::max(cuboid.z_min, cuboid.z_max + 1)));
  }

  using RebootState = std::vector<Point3D>;

  auto points(RebootState const& state) -> std::vector<Point3D>;

  auto apply_reboot_step(RebootState const &state, RebootStep const &step) -> RebootState;

  auto reboot(std::ranges::input_range auto seq) -> RebootState {
    return AoC::accumulate(seq, RebootState{}, apply_reboot_step);
  }

  auto number_of_points(RebootState const& state) -> std::size_t;

  constexpr inline Cuboid bounding_box{-50, 50, -50, 50, -50, 50};
  constexpr inline auto clipped = [](Cuboid const &box) {
    return std::views::transform([box](Cuboid const &c) { return c.clip(box); });
  };
  constexpr inline auto clipped_steps = [](Cuboid const &box) {
    return std::views::transform([box](RebootStep const &step) {
      return RebootStep{step.first, step.second.clip(box)};
    });
  };

}// namespace Day22

namespace AoC {

  template <>
  struct Solution<22> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    Day22::RebootSequence sequence;
  };

}// namespace AoC
