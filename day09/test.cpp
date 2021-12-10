#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../utils.h"
#include "solution.h"

#include <array>
#include <sstream>
#include <string>

using namespace Day09;

constexpr std::string_view EXAMPLE_ELEVATION_STRING = R"(2199943210
3987894921
9856789892
8767896789
9899965678
)";

// clang-format off
constexpr std::array<int, 10*5> EXAMPLE_ELEVATIONS = {
        2,1,9,9,9,4,3,2,1,0,
        3,9,8,7,8,9,4,9,2,1,
        9,8,5,6,7,8,9,8,9,2,
        8,7,6,7,8,9,6,7,8,9,
        9,8,9,9,9,6,5,6,7,8,
};

constexpr std::array<int, 10*5> EXAMPLE_BASINS = {
        1,1,0,0,0,2,2,2,2,2,
        1,0,3,3,3,0,2,0,2,2,
        0,3,3,3,3,3,0,4,0,2,
        3,3,3,3,3,0,4,4,4,0,
        0,3,0,0,0,4,4,4,4,4,
};
// clang-format on

constexpr Dyn2DExtents EXAMPLE_EXTENTS{5, 10};
constexpr ElevationConstView EXAMPLE_ELEVATIONS_VIEW{EXAMPLE_ELEVATIONS.data(), EXAMPLE_EXTENTS};
constexpr ElevationConstView EXAMPLE_BASINS_VIEW{EXAMPLE_BASINS.data(), EXAMPLE_EXTENTS};

TEST(Day09, parse_input) {
  std::stringstream stream{std::string{EXAMPLE_ELEVATION_STRING}};
  auto [elevations, view] = Day09::parse(stream);

  using ::testing::ElementsAreArray;
  EXPECT_THAT(elevations, ElementsAreArray(EXAMPLE_ELEVATIONS));
  EXPECT_EQ(view.extents(), EXAMPLE_ELEVATIONS_VIEW.extents());
  EXPECT_EQ(view(0, 0), 2);
  EXPECT_EQ(view(2, 4), 7);
  EXPECT_EQ(view(4, 9), 8);
}

TEST(Day09, surrounding_points) {
  using cor3ntin::rangesnext::to;
  using ::testing::UnorderedElementsAre;
  constexpr auto ext = EXAMPLE_ELEVATIONS_VIEW.extents();
  EXPECT_THAT(surrounding_points(Point{0, 0}, ext) | to<std::vector>(),
              UnorderedElementsAre(Point{0, 1}, Point{1, 0}));
  EXPECT_THAT(surrounding_points(Point{2, 4}, ext) | to<std::vector>(),
              UnorderedElementsAre(Point{3, 4}, Point{1, 4}, Point{2, 3}, Point{2, 5}));
  EXPECT_THAT(surrounding_points(Point{4, 5}, ext) | to<std::vector>(),
              UnorderedElementsAre(Point{4, 4}, Point{4, 6}, Point{3, 5}));
}

TEST(Day09, is_local_minimum) {
  EXPECT_TRUE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{0, 1}));
  EXPECT_TRUE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{0, 9}));
  EXPECT_TRUE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{2, 2}));
  EXPECT_TRUE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{4, 6}));

  EXPECT_FALSE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{0, 3}));
  EXPECT_FALSE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{1, 7}));
  EXPECT_FALSE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{2, 3}));
  EXPECT_FALSE(is_local_minimum(EXAMPLE_ELEVATIONS_VIEW, Point{3, 2}));
}

TEST(Day09, number_of_local_minima) {
  EXPECT_EQ(number_of_local_minima(EXAMPLE_ELEVATIONS_VIEW), 4);
}

TEST(Day09, total_risk_level) {
  EXPECT_EQ(total_risk_level(EXAMPLE_ELEVATIONS_VIEW), 15);
}

TEST(Day09, basin_map) {
  using ::testing::ElementsAreArray;
  auto basin_data = basin_map(EXAMPLE_ELEVATIONS_VIEW);
  EXPECT_THAT(basin_data, ElementsAreArray(EXAMPLE_BASINS));
}

TEST(Day09, basin_map_watershed) {
  using ::testing::ElementsAreArray;
  std::array watershed_elevations = {1, 2, 4, 4, 3, 2};
  ElevationConstView watershed_elevations_view{watershed_elevations.data(), Dyn2DExtents{1, 6}};
  std::array watershed_basins = {1, 1, 1, 2, 2, 2};
  auto basin_data = basin_map(watershed_elevations_view);
  EXPECT_THAT(basin_data, ElementsAreArray(watershed_basins));
}

TEST(Day09, histogrammize) {
  using ::testing::UnorderedElementsAre;
  EXPECT_THAT(histogrammize(EXAMPLE_BASINS), UnorderedElementsAre(3ul, 9ul, 9ul, 14ul));
}

TEST(Day09, product_of_top_3) {
  EXPECT_EQ(product_of_top_3(std::array{1ul, 2ul}), 0ul);
  EXPECT_EQ(product_of_top_3(std::array{1ul, 2ul, 3ul}), 6ul);
  EXPECT_EQ(product_of_top_3(std::array{1ul, 2ul, 3ul, 4ul}), 24ul);
  EXPECT_EQ(product_of_top_3(std::array{1ul, 2ul, 3ul, 4ul, 5ul}), 60ul);
  EXPECT_EQ(product_of_top_3(std::array{5ul, 3ul, 4ul, 1ul, 2ul}), 60ul);
  EXPECT_EQ(product_of_top_3(std::array{3ul, 9ul, 9ul, 14ul}), 1134ul);
}
