#include <gtest/gtest.h>

#include "solution.h"

#include <sstream>
#include <string>
#include <vector>

static const std::string EXAMPLE_REPORT[] = {"00100", "11110", "10110", "10111", "10101", "01111",
                                             "00111", "11100", "10000", "11001", "00010", "01010"};

TEST(Day03, most_common_bits) { EXPECT_EQ(Day03::most_common_bits(EXAMPLE_REPORT), "10110"); }

TEST(Day03, binary_to_decimal) {
  EXPECT_EQ(Day03::binary_to_decimal("1"), 1);
  EXPECT_EQ(Day03::binary_to_decimal("10"), 2);
  EXPECT_EQ(Day03::binary_to_decimal("10011"), 19);
}

TEST(Day03, binary_complement) {
  EXPECT_EQ(Day03::binary_complement(1, 1), 0);
  EXPECT_EQ(Day03::binary_complement(4, 3), 3);
  EXPECT_EQ(Day03::binary_complement(22, 5), 9);
}

TEST(Day03, part1) {
  std::stringstream report{R"(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010)"};
  AoC::Solution<3> solution(report);
  EXPECT_EQ(solution.part1(), 198);
}

TEST(Day03, calculate_oxygen_generator_rating) {
  EXPECT_EQ(Day03::calculate_oxygen_generator_rating(EXAMPLE_REPORT), "10111");
}

TEST(Day03, calculate_CO2_scrubber_rating) {
  EXPECT_EQ(Day03::calculate_CO2_scrubber_rating(EXAMPLE_REPORT), "01010");
}
