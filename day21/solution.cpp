#include "solution.h"

namespace Day21 {

  auto read_number_at_end_of_line(std::istream &is) -> int {
    std::string line;
    std::getline(is, line);
    auto first_digit = line.find_last_not_of("0123456789") + 1;
    return std::stoi(line.substr(first_digit));
  }

  DeterministicGame::DeterministicGame(int player_1, int player_2)
      : player_1(player_1)
      , player_2(player_2) {}

  bool DeterministicGame::take_turn_player_1() {
    return take_turn(player_1, player_1_score);
  }
  bool DeterministicGame::take_turn_player_2() {
    return take_turn(player_2, player_2_score);
  }

  bool DeterministicGame::take_turn(int &player, int &score) {
    player = (player - 1 + roll() + roll() + roll()) % 10 + 1;
    score += player;
    number_of_rolls += 3;
    return score < 1000;
  }

  int DeterministicGame::roll() {
    return std::exchange(dice, dice % 100 + 1);
  }

  auto DeterministicGame::answer() const -> std::size_t {
    return std::min(player_1_score, player_2_score) * number_of_rolls;
  }

}// namespace Day21

namespace AoC {

  Solution<21>::Solution(std::istream &stream)
      : player_1_starting_pos(Day21::read_number_at_end_of_line(stream))
      , player_2_starting_pos(Day21::read_number_at_end_of_line(stream)) {}

  auto Solution<21>::part1() const -> std::size_t {
    auto const game =
            Day21::play<Day21::DeterministicGame>(player_1_starting_pos, player_2_starting_pos);
    return game.answer();
  }

}// namespace AoC
