#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <span>

#include "solution.h"

using namespace Day17;

constexpr std::string_view EXAMPLE_TARGET_DESC = "target area: x=20..30, y=-10..-5";
constexpr Rectangle EXAMPLE_TARGET = {{20, -10}, {30, -5}};

constexpr std::array TRAJECTORY_7_2 = {
        Point{7, 2},  Point{13, 3},  Point{18, 3},  Point{22, 2},
        Point{25, 0}, Point{27, -3}, Point{28, -7},
};

constexpr std::array TRAJECTORY_6_3 = {
        Point{6, 3},  Point{11, 5}, Point{15, 6},  Point{18, 6},  Point{20, 5},
        Point{21, 3}, Point{21, 0}, Point{21, -4}, Point{21, -9},
};

constexpr std::array TRAJECTORY_9_0 = {Point{9, 0}, Point{17, -1}, Point{24, -3}, Point{30, -6}};


TEST(Day17, parse_rectangle) {
  EXPECT_EQ(parse_rectangle(EXAMPLE_TARGET_DESC), EXAMPLE_TARGET);
}

TEST(Day17, rectangle_contains_point) {
  EXPECT_TRUE(EXAMPLE_TARGET.contains({25, -8}));
  EXPECT_TRUE(EXAMPLE_TARGET.contains({20, -10}));
  EXPECT_TRUE(EXAMPLE_TARGET.contains({30, -5}));
  EXPECT_TRUE(EXAMPLE_TARGET.contains({20, -5}));
  EXPECT_TRUE(EXAMPLE_TARGET.contains({30, -10}));

  EXPECT_FALSE(EXAMPLE_TARGET.contains({-8, 25}));
  EXPECT_FALSE(EXAMPLE_TARGET.contains({19, -10}));
  EXPECT_FALSE(EXAMPLE_TARGET.contains({20, -11}));
  EXPECT_FALSE(EXAMPLE_TARGET.contains({30, -4}));
  EXPECT_FALSE(EXAMPLE_TARGET.contains({31, -10}));
}

TEST(Day17, trajectory) {
  auto test = [](Point v, std::span<Point const> expected_trajectory) {
    using ::testing::ElementsAreArray;
    std::vector<Point> actual_trajectory;
    std::ranges::copy_n(trajectory(v).begin(), expected_trajectory.size(),
                        std::back_inserter(actual_trajectory));
    EXPECT_THAT(actual_trajectory, ElementsAreArray(expected_trajectory));
  };
  test(Point{7, 2}, TRAJECTORY_7_2);
  test(Point{6, 3}, TRAJECTORY_6_3);
  test(Point{9, 0}, TRAJECTORY_9_0);
}

TEST(Day17, maximum_height_of_trajectory) {
  using ::testing::Optional;
  EXPECT_THAT(maximum_height_of_trajectory(Point{7, 2}, EXAMPLE_TARGET), Optional(3));
  EXPECT_THAT(maximum_height_of_trajectory(Point{6, 3}, EXAMPLE_TARGET), Optional(6));
  EXPECT_THAT(maximum_height_of_trajectory(Point{9, 0}, EXAMPLE_TARGET), Optional(0));
  EXPECT_THAT(maximum_height_of_trajectory(Point{17, -4}, EXAMPLE_TARGET), std::nullopt);
  EXPECT_THAT(maximum_height_of_trajectory(Point{6, 9}, EXAMPLE_TARGET), Optional(45));
}

TEST(Day17, search_optimal_trajectory) {
  EXPECT_EQ(search_optimal_trajectory(EXAMPLE_TARGET), 45);
}

TEST(Day17, count_valid_trajectories) {
  EXPECT_EQ(count_valid_trajectories(EXAMPLE_TARGET), 112);
}
