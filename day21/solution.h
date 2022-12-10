#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day21 {

  struct DeterministicGame {
    explicit DeterministicGame(int player_1, int player_2);
    bool take_turn_player_1();
    bool take_turn_player_2();
    auto answer() const -> std::size_t;

  private:
    bool take_turn(int& player, int& score);
    int roll();

    int dice = 1;

  public:
    int player_1;
    int player_2;
    int player_1_score = 0;
    int player_2_score = 0;
    std::size_t number_of_rolls = 0;
  };

  template <typename Game>
  auto play(int player_1, int player_2) -> Game {
    Game game{player_1, player_2};
    while (game.take_turn_player_1() && game.take_turn_player_2())
      ;
    return game;
  }

}// namespace Day21

namespace AoC {

  template <>
  struct Solution<21> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    int player_1_starting_pos;
    int player_2_starting_pos;
  };

}// namespace AoC
