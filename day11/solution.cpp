#include "solution.h"

#include <algorithm>
#include <numeric>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day11 {

  void increase_energy(EnergyView energies, Point p) {
    if (++energies(p.x, p.y) == 10) {
      std::ranges::for_each(AoC::surrounding_points(p, energies.extents()),
                            [energies](Point q) { return increase_energy(energies, q); });
    }
  }

  auto step(EnergyView energies) -> std::size_t {
    std::ranges::for_each(AoC::all_points(energies.extents()),
                          [energies](Point q) { return increase_energy(energies, q); });

    auto count = std::ranges::count_if(
            AoC::all_points(energies.extents())
                    | std::views::transform([energies](Point p) { return energies(p.x, p.y); }),
            [](int e) { return e >= 10; });

    std::ranges::fill(AoC::all_points(energies.extents())
                              | std::views::transform(
                                      [energies](Point p) -> int & { return energies(p.x, p.y); })
                              | std::views::filter([](int e) { return e >= 10; }),
                      0ul);

    return count;
  }

  auto multi_step(EnergyView energies, std::size_t count) -> std::size_t {
    auto flashes = std::views::iota(0ul, count)
                   | std::views::transform([energies](std::size_t) { return step(energies); });
    return std::accumulate(flashes.begin(), flashes.end(), 0ul);
  }

  auto steps_until_sync(EnergyView energies) -> std::size_t {
    return std::ranges::distance(
                   std::views::iota(0ul)
                   | std::views::transform([energies](std::size_t) { return step(energies); })
                   | std::views::take_while([size = energies.size()](std::size_t num_flashes) {
                       return num_flashes != size;
                     }))
           + 1;
  }

}// namespace Day11

namespace AoC {

  Solution<11>::Solution(std::istream &stream)
      : Solution{AoC::parse_matrix(stream)} {}

  Solution<11>::Solution(std::pair<std::vector<int>, Day11::EnergyConstView> pair)
      : initial_energies{std::move(pair.first)}
      , initial_energies_view{std::move(pair.second)} {}

  auto Solution<11>::part1() const -> std::size_t {
    auto energies = initial_energies;
    Day11::EnergyView energies_view{energies.data(), initial_energies_view.extents()};
    return Day11::multi_step(energies_view, 100);
  }

  auto Solution<11>::part2() const -> std::size_t {
    auto energies = initial_energies;
    Day11::EnergyView energies_view{energies.data(), initial_energies_view.extents()};
    return Day11::steps_until_sync(energies_view);
  }

}// namespace AoC
