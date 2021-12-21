#include "solution.h"

namespace Day21 {

  auto read_number_at_end_of_line(std::istream &is) -> int {
    std::string line;
    std::getline(is, line);
    auto first_digit = line.find_last_not_of("0123456789") + 1;
    return std::stoi(line.substr(first_digit));
  }

}// namespace Day21

namespace AoC {

  Solution<21>::Solution(std::istream &stream)
      : player_1_starting_pos(Day21::read_number_at_end_of_line(stream))
      , player_2_starting_pos(Day21::read_number_at_end_of_line(stream)) {}

  auto Solution<21>::part1() const -> std::size_t {
    auto die = Day21::deterministic_die;
    auto result = Day21::play(player_1_starting_pos, player_2_starting_pos, die);
    return std::min(result.player_1_score, result.player_2_score) * result.number_of_rolls;
  }

}// namespace AoC
