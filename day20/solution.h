#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day20 {

  using Image2DView = AoC::View2D<char>;
  using Image2DConstView = AoC::View2D<char const>;

  auto parse_kernel(std::istream &) -> std::string;
  auto pad_image(Image2DConstView image, std::size_t padding)
          -> std::pair<std::string, Image2DView>;
  void enhance_image(Image2DView image, std::string_view kernel, std::size_t count = 1);
  auto count_lit_pixels(Image2DConstView image) -> std::size_t;
  auto solve(Image2DConstView original_image, std::string_view kernel, std::size_t count)
          -> std::size_t;

}// namespace Day20

namespace AoC {

  template <>
  struct Solution<20> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    explicit Solution(std::string &&kernel,
                      std::pair<std::vector<char>, Day20::Image2DView> &&image);
    std::string kernel;
    std::vector<char> original_data;
    Day20::Image2DConstView original_image;
  };

}// namespace AoC
