#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

using namespace Day21;

TEST(Day21, take_deterministic_turn) {
  DeterministicGame game{4, 8};

  game.take_turn_player_1();
  EXPECT_EQ(game.player_1, 10);
  EXPECT_EQ(game.player_1_score, 10);
  EXPECT_EQ(game.number_of_rolls, 3);

  game.take_turn_player_2();
  EXPECT_EQ(game.player_2, 3);
  EXPECT_EQ(game.player_2_score, 3);
  EXPECT_EQ(game.number_of_rolls, 6);

  game.take_turn_player_1();
  EXPECT_EQ(game.player_1, 4);
  EXPECT_EQ(game.player_1_score, 14);
  EXPECT_EQ(game.number_of_rolls, 9);

  game.take_turn_player_2();
  EXPECT_EQ(game.player_2, 6);
  EXPECT_EQ(game.player_2_score, 9);
  EXPECT_EQ(game.number_of_rolls, 12);

  game.take_turn_player_1();
  EXPECT_EQ(game.player_1, 6);
  EXPECT_EQ(game.player_1_score, 20);
  EXPECT_EQ(game.number_of_rolls, 15);

  game.take_turn_player_2();
  EXPECT_EQ(game.player_2, 7);
  EXPECT_EQ(game.player_2_score, 16);
  EXPECT_EQ(game.number_of_rolls, 18);

  game.take_turn_player_1();
  EXPECT_EQ(game.player_1, 6);
  EXPECT_EQ(game.player_1_score, 26);
  EXPECT_EQ(game.number_of_rolls, 21);

  game.take_turn_player_2();
  EXPECT_EQ(game.player_2, 6);
  EXPECT_EQ(game.player_2_score, 22);
  EXPECT_EQ(game.number_of_rolls, 24);
}

TEST(Day21, play_deterministically) {
  auto result = play<DeterministicGame>(4, 8);
  EXPECT_EQ(result.player_1_score, 1000);
  EXPECT_EQ(result.player_2_score, 745);
  EXPECT_EQ(result.number_of_rolls, 993);
}
