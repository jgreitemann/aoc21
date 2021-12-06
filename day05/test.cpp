#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <algorithm>
#include <array>
#include <sstream>
#include <string>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day05;

constexpr std::string_view EXAMPLE = R"(0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
)";

constexpr std::array EXAMPLE_LINES = {
        Line{Point{0, 9}, Point{5, 9}}, Line{Point{8, 0}, Point{0, 8}},
        Line{Point{9, 4}, Point{3, 4}}, Line{Point{2, 2}, Point{2, 1}},
        Line{Point{7, 0}, Point{7, 4}}, Line{Point{6, 4}, Point{2, 0}},
        Line{Point{0, 9}, Point{2, 9}}, Line{Point{3, 4}, Point{1, 4}},
        Line{Point{0, 0}, Point{8, 8}}, Line{Point{5, 5}, Point{8, 2}},
};

constexpr std::array PARAXIAL_EXAMPLE_LINES = {
        Line{Point{0, 9}, Point{5, 9}}, Line{Point{9, 4}, Point{3, 4}},
        Line{Point{2, 2}, Point{2, 1}}, Line{Point{7, 0}, Point{7, 4}},
        Line{Point{0, 9}, Point{2, 9}}, Line{Point{3, 4}, Point{1, 4}},
};

// clang-format off
constexpr std::array PARAXIAL_EXAMPLE_IMAGE = {
        0,0,0,0,0,0,0,1,0,0,
        0,0,1,0,0,0,0,1,0,0,
        0,0,1,0,0,0,0,1,0,0,
        0,0,0,0,0,0,0,1,0,0,
        0,1,1,2,1,1,1,2,1,1,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        2,2,2,1,1,1,0,0,0,0,
};
constexpr std::array EXAMPLE_IMAGE = {
        1,0,1,0,0,0,0,1,1,0,
        0,1,1,1,0,0,0,2,0,0,
        0,0,2,0,1,0,1,1,1,0,
        0,0,0,1,0,2,0,2,0,0,
        0,1,1,2,3,1,3,2,1,1,
        0,0,0,1,0,2,0,0,0,0,
        0,0,1,0,0,0,1,0,0,0,
        0,1,0,0,0,0,0,1,0,0,
        1,0,0,0,0,0,0,0,1,0,
        2,2,2,1,1,1,0,0,0,0,
};
// clang-format on

constexpr std::experimental::extents EXAMPLE_EXTENTS{10, 10};

TEST(Day05, parse_input) {
  std::stringstream stream{std::string{EXAMPLE}};
  EXPECT_THAT(parse(stream), testing::ElementsAreArray(EXAMPLE_LINES));
}

TEST(Day05, get_extents) {
  constexpr Line lines[] = {{Point{4, 1}, Point{4, 8}}, {Point{1, 6}, Point{7, 6}}};
  EXPECT_EQ(Day05::get_extents(lines), (Day05::Extents2D{8, 9}));
  EXPECT_EQ(Day05::get_extents(EXAMPLE_LINES), EXAMPLE_EXTENTS);
}

TEST(Day05, is_paraxial) {
  EXPECT_TRUE(Day05::is_paraxial(Line{Point{3, 0}, Point{3, 5}}));
  EXPECT_TRUE(Day05::is_paraxial(Line{Point{0, 3}, Point{5, 3}}));
  EXPECT_FALSE(Day05::is_paraxial(Line{Point{3, 0}, Point{5, 3}}));

  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(EXAMPLE_LINES | std::views::filter(is_paraxial) | to<std::vector>(),
              ElementsAreArray(PARAXIAL_EXAMPLE_LINES));
}

TEST(Day05, points_on_line) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAre;
  EXPECT_THAT(Day05::points_on_line({{4, 3}, {7, 3}}) | to<std::vector>(),
              ElementsAre(Point{4, 3}, Point{5, 3}, Point{6, 3}, Point{7, 3}));
  EXPECT_THAT(Day05::points_on_line({{2, 8}, {2, 4}}) | to<std::vector>(),
              ElementsAre(Point{2, 8}, Point{2, 7}, Point{2, 6}, Point{2, 5}, Point{2, 4}));
  EXPECT_THAT(Day05::points_on_line({{3, 0}, {0, 3}}) | to<std::vector>(),
              ElementsAre(Point{3, 0}, Point{2, 1}, Point{1, 2}, Point{0, 3}));
}

TEST(Day05, render_micro) {
  // clang-format off
  std::array solution = {1, 2,
                         1, 0};
  // clang-format on
  std::array<Line, 2> lines{Line{Point{0, 0}, Point{1, 0}}, Line{Point{1, 0}, Point{0, 1}}};
  std::array<int, 4> image{};
  render(Image2DView{image.data(), Extents2D{2, 2}}, lines);
  EXPECT_EQ(image, solution);
}

TEST(Day05, render_mini) {
  // clang-format off
  std::array solution = {1, 2, 1,
                         1, 0, 0,
                         0, 1, 1};
  // clang-format on
  std::array<Line, 3> lines{Line{Point{0, 0}, Point{2, 0}}, Line{Point{1, 0}, Point{0, 1}},
                            Line{Point{1, 2}, Point{2, 2}}};
  std::array<int, 9> image{};
  render(Image2DView{image.data(), Extents2D{3, 3}}, lines);
  EXPECT_EQ(image, solution);
}

TEST(Day05, render_paraxial_example) {
  std::array<int, EXAMPLE_EXTENTS.extent(0) * EXAMPLE_EXTENTS.extent(1)> image{};
  render(Image2DView{image.data(), EXAMPLE_EXTENTS}, PARAXIAL_EXAMPLE_LINES);
  EXPECT_EQ(image, PARAXIAL_EXAMPLE_IMAGE);
}

TEST(Day05, render_example) {
  std::array<int, EXAMPLE_EXTENTS.extent(0) * EXAMPLE_EXTENTS.extent(1)> image{};
  render(Image2DView{image.data(), EXAMPLE_EXTENTS}, EXAMPLE_LINES);
  EXPECT_EQ(image, EXAMPLE_IMAGE);
}

TEST(Day05, number_of_overlaps) {
  EXPECT_EQ(Day05::number_of_overlaps(PARAXIAL_EXAMPLE_IMAGE), 5);
  EXPECT_EQ(Day05::number_of_overlaps(EXAMPLE_IMAGE), 12);
}
