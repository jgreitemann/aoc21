#include <gtest/gtest.h>

#include "solution.h"

TEST(Day00, count_characters) {
  EXPECT_EQ(Day00::count_characters("Hello, world!"), 13);
}