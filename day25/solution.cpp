#include "solution.h"

#include <cassert>

namespace Day25 {

  auto step(MapConstView input_map, MapView output_map) -> bool {
    assert(input_map.extents() == output_map.extents());

    auto to_the_right = [](Point p, AoC::Dyn2DExtents ext) {
      return Point{p.x, (p.y + 1) % ext.extent(1)};
    };

    auto down = [](Point p, AoC::Dyn2DExtents ext) {
      return Point{(p.x + 1) % ext.extent(0), p.y};
    };

    auto move_herd = [&](char herd, auto &&move_op) {
      bool moved = false;
      for (auto p : AoC::all_points(input_map.extents())) {
        if (char in = input_map(p.x, p.y); in == herd) {
          auto q = move_op(p, output_map.extents());
          if (input_map(q.x, q.y) < herd && output_map(q.x, q.y) == '.') {

            output_map(q.x, q.y) = in;
            moved = true;
          } else {
            output_map(p.x, p.y) = in;
          }
        }
      }
      return moved;
    };

    for (auto p : AoC::all_points(output_map.extents()))
      output_map(p.x, p.y) = '.';

    return move_herd('>', to_the_right) | move_herd('v', down);
  }

  auto steps_until_converged(MapConstView input_map) -> std::size_t {
    std::vector<char> first_data(input_map.size(), '.');
    MapView first_map{first_data.data(), input_map.extents()};

    std::vector<char> second_data(input_map.size(), '.');
    MapView second_map{second_data.data(), input_map.extents()};

    for (auto p : AoC::all_points(input_map.extents()))
      first_map(p.x, p.y) = input_map(p.x, p.y);

    std::size_t count = 1;
    for (; step(first_map, second_map); ++count) {
      std::swap(first_data, second_data);
      std::swap(first_map, second_map);
    }

    return count;
  }

}// namespace Day25

namespace AoC {

  Solution<25>::Solution(std::istream &stream)
      : Solution(AoC::parse_char_image(stream)) {}

  Solution<25>::Solution(std::pair<std::vector<char>, Day25::MapView> &&pair)
      : initial_data{std::move(pair.first)}
      , initial_view{pair.second} {}

  auto Solution<25>::part1() const -> std::size_t {
    return Day25::steps_until_converged(initial_view);
  }

}// namespace AoC
