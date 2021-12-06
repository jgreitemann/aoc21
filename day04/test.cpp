#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <sstream>
#include <string>
#include <string_view>

using namespace Day04;

constexpr std::string_view EXAMPLE =
        R"(7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7
)";

constexpr std::array EXAMPLE_NUMBERS = {7,  4, 9,  5,  11, 17, 23, 2,  0, 14, 21, 24, 10, 16,
                                        13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3,  26, 1};

// clang-format off
constexpr std::array EXAMPLE_BOARDS = {
        22, 13, 17, 11,  0,
         8,  2, 23,  4, 24,
        21,  9, 14, 16,  7,
         6, 10,  3, 18,  5,
         1, 12, 20, 15, 19,

         3, 15,  0,  2, 22,
         9, 18, 13, 17,  5,
        19,  8,  7, 25, 23,
        20, 11, 10, 24,  4,
        14, 21, 16, 12,  6,

        14, 21, 17, 24,  4,
        10, 16, 15,  9, 19,
        18,  8, 23, 26, 20,
        22, 11, 13,  6,  5,
         2,  0, 12,  3,  7,
};
// clang-format on

TEST(Day04, parse_numbers_and_boards) {
  std::stringstream stream{std::string{EXAMPLE}};
  auto numbers = parse_numbers(stream);
  auto boards = parse_boards(stream);

  using ::testing::ElementsAreArray;
  EXPECT_THAT(numbers, ElementsAreArray(EXAMPLE_NUMBERS));
  EXPECT_THAT(boards, ElementsAreArray(EXAMPLE_BOARDS));
}

TEST(Day04, view_into_bingo_boards) {
  BoardsConstView boards{EXAMPLE_BOARDS.data()};
  //           board row column
  //               |  |  |
  EXPECT_EQ(boards(1, 1, 1), 18);
  EXPECT_EQ(boards(0, 0, 1), 13);
  EXPECT_EQ(boards(1, 3, 4), 4);
  EXPECT_EQ(boards(2, 4, 4), 7);
}
