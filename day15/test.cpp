#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day15;

// clang-format off
constexpr std::array EXAMPLE_MAP_DATA = {
        1,1,6,3,7,5,1,7,4,2,
        1,3,8,1,3,7,3,6,7,2,
        2,1,3,6,5,1,1,3,2,8,
        3,6,9,4,9,3,1,5,6,9,
        7,4,6,3,4,1,7,1,1,1,
        1,3,1,9,1,2,8,1,3,7,
        1,3,5,9,9,1,2,4,2,1,
        3,1,2,5,4,2,1,6,3,9,
        1,2,9,3,1,3,8,5,2,1,
        2,3,1,1,9,4,4,5,8,1,
};

constexpr std::array EXAMPLE_RISK_DATA = {
         0, 1, 7,10,17,22,23,30,34,36,
         1, 4,12,11,14,21,23,29,32,34,
         3, 4, 7,13,18,19,20,23,25,33,
         6,10,16,17,26,22,21,26,31,38,
        13,14,20,20,24,23,28,27,28,29,
        14,17,18,27,25,25,33,28,31,36,
        15,18,23,32,34,26,28,32,33,34,
        18,19,21,26,30,28,29,35,36,43,
        19,21,30,29,30,31,37,40,38,39,
        21,24,25,26,35,35,39,44,46,40,
};
// clang-format on

constexpr MapConstView EXAMPLE_MAP{EXAMPLE_MAP_DATA.data(), AoC::Dyn2DExtents{10, 10}};

TEST(Day15, least_risk_level_map) {
  using ::testing::ElementsAreArray;
  EXPECT_THAT(least_risk_level_map(EXAMPLE_MAP), ElementsAreArray(EXAMPLE_RISK_DATA));
}
