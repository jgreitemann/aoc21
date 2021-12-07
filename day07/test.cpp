#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>

using namespace Day07;

constexpr std::array EXAMPLE_CRABS = {16, 1, 2, 0, 4, 2, 7, 1, 2, 14};

TEST(Day07, linear_cost_to_align) {
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 1, identity), 41);
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 2, identity), 37);
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 3, identity), 39);
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 10, identity), 71);
}

TEST(Day07, lineally_cheapest_aligned_position) {
  auto cheapest_alignment = cheapest_aligned_position(EXAMPLE_CRABS, identity);
  EXPECT_EQ(cheapest_alignment.pos, 2);
  EXPECT_EQ(cheapest_alignment.cost, 37);
}

TEST(Day07, quadratic_cost_to_align) {
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 2, gauss), 206);
  EXPECT_EQ(cost_to_align(EXAMPLE_CRABS, 5, gauss), 168);
}

TEST(Day07, quadratically_cheapest_aligned_position) {
  auto cheapest_alignment = cheapest_aligned_position(EXAMPLE_CRABS, gauss);
  EXPECT_EQ(cheapest_alignment.pos, 5);
  EXPECT_EQ(cheapest_alignment.cost, 168);
}
