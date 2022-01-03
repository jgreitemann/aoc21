#include "solution.h"

namespace Day20 {

  auto parse_kernel(std::istream &stream) -> std::string {
    std::string kernel;
    std::getline(stream, kernel);
    stream.ignore();
    return kernel;
  }

  auto resize_extents(AoC::Dyn2DExtents extents, std::ptrdiff_t by) -> AoC::Dyn2DExtents {
    return AoC::Dyn2DExtents{extents.extent(0) + 2 * by, extents.extent(1) + 2 * by};
  }

  auto pad_image(Image2DConstView image, std::size_t padding)
          -> std::pair<std::string, Image2DView> {
    auto new_extents = resize_extents(image.extents(), padding);
    std::string new_image_data(new_extents.extent(0) * new_extents.extent(1), '.');
    auto new_image_view = Image2DView{new_image_data.data(), new_extents};
    auto subview = submdspan(new_image_view, std::pair{padding, padding + image.extent(0)},
                             std::pair{padding, padding + image.extent(1)});
    for (auto pt : AoC::all_points(image.extents()))
      subview(pt.x, pt.y) = image(pt.x, pt.y);
    return {std::move(new_image_data), new_image_view};
  }

  void enhance_image_impl(Image2DConstView input_image, Image2DView output_image,
                          std::string_view kernel) {
    for (auto pt : AoC::all_points(input_image.extents())) {
      std::array<int, 9> square{};
      std::ranges::fill(square, input_image(0, 0) == '#');
      AoC::View2D<int> square_view{square.data(), AoC::Dyn2DExtents{3, 3}};
      for (auto q : AoC::nearby_points(pt, input_image.extents())) {
        auto r = q + AoC::Point<std::size_t>{1, 1} - pt;
        square_view(r.x, r.y) = (input_image(q.x, q.y) == '#');
      }
      auto idx = AoC::accumulate(square, 0ul, [](std::size_t a, int i) { return (a << 1) + i; });
      output_image(pt.x, pt.y) = kernel[idx];
    }
  }

  void enhance_image(Image2DView image, std::string_view kernel, std::size_t count) {
    std::string workspace_data(image.size(), '.');
    Image2DView workspace_image{workspace_data.data(), image.extents()};

    for (auto _ : std::views::iota(0ul, count / 2)) {
      enhance_image_impl(image, workspace_image, kernel);
      enhance_image_impl(workspace_image, image, kernel);
    }

    if (count % 2 != 0) {
      enhance_image_impl(image, workspace_image, kernel);
      for (auto p : AoC::all_points(image.extents()))
        image(p.x, p.y) = workspace_image(p.x, p.y);
    }
  }

  auto count_lit_pixels(Image2DConstView image) -> std::size_t {
    return std::ranges::count_if(AoC::all_points(image.extents()),
                                 [image](auto p) { return image(p.x, p.y) == '#'; });
  }

  auto solve(Image2DConstView original_image, std::string_view kernel, std::size_t count)
          -> std::size_t {
    auto [padded_data, padded_view] = Day20::pad_image(original_image, count + 1);
    Day20::enhance_image(padded_view, kernel, count);
    return Day20::count_lit_pixels(padded_view);
  }

}// namespace Day20

namespace AoC {

  Solution<20>::Solution(std::istream &stream)
      : Solution{Day20::parse_kernel(stream), AoC::parse_char_image(stream)} {}

  Solution<20>::Solution(std::string &&kernel,
                         std::pair<std::vector<char>, Day20::Image2DView> &&image)
      : kernel{std::move(kernel)}
      , original_data{std::move(image.first)}
      , original_image{image.second} {}

  auto Solution<20>::part1() const -> std::size_t {
    return Day20::solve(original_image, kernel, 2);
  }

  auto Solution<20>::part2() const -> std::size_t {
    return Day20::solve(original_image, kernel, 50);
  }

}// namespace AoC
