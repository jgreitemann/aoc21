#include <gtest/gtest.h>

#include "solution.h"

#include <vector>

TEST(Day01, number_of_increases) {
  std::vector measurements = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  EXPECT_EQ(Day01::number_of_increases(measurements), 7);
}
