#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

using namespace Day21;

TEST(Day21, take_turn) {
  int player = 4;
  int score = 0;
  std::size_t rolls = 0;
  auto die = deterministic_die;

  take_turn(player, score, die, rolls);
  EXPECT_EQ(player, 10);
  EXPECT_EQ(score, 10);
  EXPECT_EQ(rolls, 3);

  die();
  die();
  die();

  take_turn(player, score, die, rolls);
  EXPECT_EQ(player, 4);
  EXPECT_EQ(score, 14);
  EXPECT_EQ(rolls, 6);

  die();
  die();
  die();

  take_turn(player, score, die, rolls);
  EXPECT_EQ(player, 6);
  EXPECT_EQ(score, 20);
  EXPECT_EQ(rolls, 9);

  die();
  die();
  die();

  take_turn(player, score, die, rolls);
  EXPECT_EQ(player, 6);
  EXPECT_EQ(score, 26);
  EXPECT_EQ(rolls, 12);
}

TEST(Day21, play) {
  auto die = deterministic_die;
  auto result = play(4, 8, die);
  EXPECT_EQ(result.player_1_score, 1000);
  EXPECT_EQ(result.player_2_score, 745);
  EXPECT_EQ(result.number_of_rolls, 993);
}
