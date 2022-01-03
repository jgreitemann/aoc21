#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day20;

constexpr std::string_view EXAMPLE_INPUT =
        R"(..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#

#..#.
#....
##..#
..#..
..###
)";

constexpr std::string_view EXAMPLE_KERNEL = EXAMPLE_INPUT.substr(0, 512);
constexpr std::string_view EXAMPLE_ORIGINAL_IMAGE_DATA = "#..#."
                                                         "#...."
                                                         "##..#"
                                                         "..#.."
                                                         "..###";
constexpr Image2DConstView EXAMPLE_ORIGINAL_IMAGE_VIEW{EXAMPLE_ORIGINAL_IMAGE_DATA.data(),
                                                       AoC::Dyn2DExtents{5, 5}};

constexpr std::string_view EXAMPLE_ENHANCED_ONCE_IMAGE_DATA = "..............."
                                                              "..............."
                                                              "..............."
                                                              "..............."
                                                              ".....##.##....."
                                                              "....#..#.#....."
                                                              "....##.#..#...."
                                                              "....####..#...."
                                                              ".....#..##....."
                                                              "......##..#...."
                                                              ".......#.#....."
                                                              "..............."
                                                              "..............."
                                                              "..............."
                                                              "...............";
constexpr Image2DConstView EXAMPLE_ENHANCED_ONCE_IMAGE_VIEW{EXAMPLE_ENHANCED_ONCE_IMAGE_DATA.data(),
                                                            AoC::Dyn2DExtents{15, 15}};

constexpr std::string_view EXAMPLE_ENHANCED_TWICE_IMAGE_DATA = "..............."
                                                               "..............."
                                                               "..............."
                                                               "..........#...."
                                                               "....#..#.#....."
                                                               "...#.#...###..."
                                                               "...#...##.#...."
                                                               "...#.....#.#..."
                                                               "....#.#####...."
                                                               ".....#.#####..."
                                                               "......##.##...."
                                                               ".......###....."
                                                               "..............."
                                                               "..............."
                                                               "...............";
constexpr Image2DConstView EXAMPLE_ENHANCED_TWICE_IMAGE_VIEW{
        EXAMPLE_ENHANCED_TWICE_IMAGE_DATA.data(), AoC::Dyn2DExtents{15, 15}};

TEST(Day20, parse_input) {
  std::stringstream stream{std::string{EXAMPLE_INPUT}};
  EXPECT_EQ(parse_kernel(stream), EXAMPLE_KERNEL);
  auto [image_data, image_view] = AoC::parse_char_image(stream);
  EXPECT_EQ(std::string(image_data.begin(), image_data.end()), EXAMPLE_ORIGINAL_IMAGE_DATA);
  EXPECT_EQ(image_view.extents(), EXAMPLE_ORIGINAL_IMAGE_VIEW.extents());
}

TEST(Day20, pad_image) {
  constexpr std::string_view IMAGE_3x3_DATA = "..#"
                                              "#.."
                                              ".#.";
  constexpr Image2DConstView IMAGE_3x3_VIEW{IMAGE_3x3_DATA.data(), AoC::Dyn2DExtents{3, 3}};

  constexpr std::string_view IMAGE_5x5_DATA = "....."
                                              "...#."
                                              ".#..."
                                              "..#.."
                                              ".....";
  constexpr Image2DConstView IMAGE_5x5_VIEW{IMAGE_5x5_DATA.data(), AoC::Dyn2DExtents{5, 5}};

  constexpr std::string_view IMAGE_9x9_DATA = "........."
                                              "........."
                                              "........."
                                              ".....#..."
                                              "...#....."
                                              "....#...."
                                              "........."
                                              "........."
                                              ".........";
  constexpr Image2DConstView IMAGE_9x9_VIEW{IMAGE_9x9_DATA.data(), AoC::Dyn2DExtents{9, 9}};

  auto test = [IMAGE_3x3_VIEW]<typename T>(T &&pair, auto expected_image_data,
                                           auto expected_image_view) {
    auto [image_data, image_view] = std::forward<T>(pair);
    EXPECT_THAT(image_data, expected_image_data);
    ASSERT_EQ(image_view.extents(), expected_image_view.extents());

    for (auto p : AoC::all_points(image_view.extents()))
      EXPECT_EQ(image_view(p.x, p.y), expected_image_view(p.x, p.y));

    std::size_t padding = (image_view.extent(0) - 3) / 2;
    auto subview =
            submdspan(image_view, std::pair{padding, padding + 3}, std::pair{padding, padding + 3});
    for (auto p : AoC::all_points(IMAGE_3x3_VIEW.extents()))
      EXPECT_EQ(subview(p.x, p.y), IMAGE_3x3_VIEW(p.x, p.y));
  };

  auto image_5x5_pair = pad_image(IMAGE_3x3_VIEW, 1);
  test(image_5x5_pair, IMAGE_5x5_DATA, IMAGE_5x5_VIEW);

  test(pad_image(image_5x5_pair.second, 2), IMAGE_9x9_DATA, IMAGE_9x9_VIEW);
  test(pad_image(IMAGE_3x3_VIEW, 3), IMAGE_9x9_DATA, IMAGE_9x9_VIEW);
}

TEST(Day20, enhance_image_by_single_steps) {
  auto [image_data, image_view] = pad_image(EXAMPLE_ORIGINAL_IMAGE_VIEW, 5);

  enhance_image(image_view, EXAMPLE_KERNEL);
  EXPECT_EQ(image_data, EXAMPLE_ENHANCED_ONCE_IMAGE_DATA);

  enhance_image(image_view, EXAMPLE_KERNEL);
  EXPECT_EQ(image_data, EXAMPLE_ENHANCED_TWICE_IMAGE_DATA);
}

TEST(Day20, enhance_image_by_even_numbered_steps) {
  auto [image_data, image_view] = pad_image(EXAMPLE_ORIGINAL_IMAGE_VIEW, 5);

  enhance_image(image_view, EXAMPLE_KERNEL, 2);
  EXPECT_EQ(image_data, EXAMPLE_ENHANCED_TWICE_IMAGE_DATA);
}

TEST(Day20, count_lit_pixels) {
  EXPECT_EQ(count_lit_pixels(EXAMPLE_ENHANCED_TWICE_IMAGE_VIEW), 35);
}

TEST(Day20, solve) {
  EXPECT_EQ(solve(EXAMPLE_ORIGINAL_IMAGE_VIEW, EXAMPLE_KERNEL, 2), 35);
  EXPECT_EQ(solve(EXAMPLE_ORIGINAL_IMAGE_VIEW, EXAMPLE_KERNEL, 50), 3351);
}
