#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../utils.h"
#include "solution.h"

#include <span>
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

constexpr std::array EXAMPLE_BINGO_BOARD = {
        MK, MK, MK, MK, MK,
        10, 16, 15, MK, 19,
        18,  8, MK, 26, 20,
        22, MK, 13,  6, MK,
        MK, MK, 12,  3, MK,
};
// clang-format on

TEST(Day04, parse_numbers_and_boards) {
  std::stringstream stream{std::string{EXAMPLE}};
  auto numbers = AoC::parse_comma_separated_ints_on_line(stream);
  auto boards = AoC::parse_vec<int>(stream);

  using ::testing::ElementsAreArray;
  EXPECT_THAT(numbers, ElementsAreArray(EXAMPLE_NUMBERS));
  EXPECT_THAT(boards, ElementsAreArray(EXAMPLE_BOARDS));
}

TEST(Day04, view_into_bingo_boards) {
  AllBoardsConstView boards{EXAMPLE_BOARDS.data()};
  //           board row column
  //               |  |  |
  EXPECT_EQ(boards(1, 1, 1), 18);
  EXPECT_EQ(boards(0, 0, 1), 13);
  EXPECT_EQ(boards(1, 3, 4), 4);
  EXPECT_EQ(boards(2, 4, 4), 7);
}

TEST(Day04, get_board) {
  AllBoardsConstView boards{EXAMPLE_BOARDS.data()};
  auto second_board = get_board(boards, 1);
  EXPECT_EQ(second_board(0, 0), 3);
  EXPECT_EQ(second_board(0, 1), 15);
  EXPECT_EQ(second_board(1, 0), 9);
  EXPECT_EQ(second_board(4, 4), 6);
}

TEST(Day04, is_bingo) {
  AllBoardsConstView boards{EXAMPLE_BOARDS.data()};
  BoardConstView bingo_board{EXAMPLE_BINGO_BOARD.data()};
  EXPECT_FALSE(is_bingo(get_board(boards, 0)));
  EXPECT_FALSE(is_bingo(get_board(boards, 1)));
  EXPECT_FALSE(is_bingo(get_board(boards, 2)));
  EXPECT_TRUE(is_bingo(bingo_board));
}

TEST(Day04, sum_of_unmarked_numbers) {
  BoardConstView bingo_board{EXAMPLE_BINGO_BOARD.data()};
  EXPECT_EQ(sum_of_unmarked_numbers(bingo_board), 188);
}

TEST(Day04, marking_numbers) {
  auto boards_data = EXAMPLE_BOARDS;
  AllBoardsView boards{boards_data.data(), boards_data.size() / 25};

  // marking the first few numbers: no winners at this point
  for (BoardView this_board : iter_boards(boards)) {
    for (int num : EXAMPLE_NUMBERS | std::views::take(11))
      mark(this_board, num);
    EXPECT_FALSE(is_bingo(this_board));
  }

  // mark the final number: board #2 has bingo!
  for (BoardView this_board : iter_boards(boards))
    mark(this_board, 24);
  EXPECT_FALSE(is_bingo(get_board(boards, 0)));
  EXPECT_FALSE(is_bingo(get_board(boards, 1)));
  EXPECT_TRUE(is_bingo(get_board(boards, 2)));

  auto winner = get_board(boards, 2);
  auto winner_span = std::span<int const>{winner.data(), winner.data() + winner.size()};
  EXPECT_THAT(EXAMPLE_BINGO_BOARD, ::testing::ElementsAreArray(winner_span));
}

TEST(Day04, get_winning_score) {
  auto boards_data = EXAMPLE_BOARDS;
  AllBoardsView boards{boards_data.data(), boards_data.size() / 25};
  EXPECT_EQ(get_winning_score(boards, EXAMPLE_NUMBERS), 4512);
}

TEST(Day04, get_losing_score) {
  auto boards_data = EXAMPLE_BOARDS;
  AllBoardsView boards{boards_data.data(), boards_data.size() / 25};
  EXPECT_EQ(get_losing_score(boards, EXAMPLE_NUMBERS), 1924);
}
