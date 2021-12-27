#pragma once

#include "../utils.h"

#include <array>
#include <tuple>

namespace Day24 {

  constexpr auto compute_simplified(std::input_iterator auto input_it) -> int {
    constexpr std::array params = {
            std::tuple{12, 6, 1},   std::tuple{11, 12, 1},  std::tuple{10, 5, 1},
            std::tuple{10, 10, 1},  std::tuple{-16, 7, 26}, std::tuple{14, 0, 1},
            std::tuple{12, 4, 1},   std::tuple{-4, 12, 26}, std::tuple{15, 14, 1},
            std::tuple{-7, 13, 26}, std::tuple{-8, 10, 26}, std::tuple{-4, 11, 26},
            std::tuple{-15, 9, 26}, std::tuple{-8, 9, 26},
    };

    return AoC::accumulate(params, 0, [&](int acc, auto const &tuple) {
      auto [a, b, c] = tuple;
      int const input = *(input_it++);

      if ((acc % 26 + a) != input)
        return acc / c * 26 + input + b;
      else
        return acc / c;
    });
  }

}// namespace Day24
