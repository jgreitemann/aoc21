#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <algorithm>
#include <sstream>
#include <string>

using namespace Day02;

constexpr std::string_view EXAMPLE_INPUT = R"(forward 5
down 5
forward 8
up 3
down 8
forward 2
)";

constexpr Command EXAMPLE_COURSE[] = {HorizontalDive{5}, VerticalDive{-5}, HorizontalDive{8},
                                      VerticalDive{3},   VerticalDive{-8}, HorizontalDive{2}};

TEST(Day02, parse_course) {
  std::stringstream stream{std::string{EXAMPLE_INPUT}};
  EXPECT_TRUE(std::ranges::equal(parse(stream), EXAMPLE_COURSE));
}

TEST(Day02, track_sub1) { EXPECT_EQ(track_sub1(EXAMPLE_COURSE), (Position{15, 10})); }

TEST(Day02, track_sub2) { EXPECT_EQ(track_sub2(EXAMPLE_COURSE), (Position{15, 60, 10})); }
