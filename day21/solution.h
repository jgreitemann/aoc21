#pragma once

#include "../solution.h"
#include "../utils.h"

namespace Day21 {

  struct PlayResult {
    std::size_t number_of_rolls;
    int player_1_score;
    int player_2_score;
  };

  bool take_turn(int &player, int &score, auto &die, std::size_t &number_of_rolls) {
    player = (player - 1 + die() + die() + die()) % 10 + 1;
    score += player;
    number_of_rolls += 3;
    return score < 1000;
  }

  auto play(int player_1, int player_2, auto &&die) -> PlayResult {
    PlayResult result{};
    while (take_turn(player_1, result.player_1_score, die, result.number_of_rolls)
           && take_turn(player_2, result.player_2_score, die, result.number_of_rolls))
      ;
    return result;
  }

  constexpr auto deterministic_die = [x = 0]() mutable { return x = x % 100 + 1; };

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
