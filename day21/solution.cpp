#include "solution.h"

#include <cor3ntin/rangesnext/product.hpp>

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

  QuantumGame::QuantumGame(int player_1, int player_2)
      : universes_data(22 * 22 * 10 * 10)
      , universes_view(universes_data.data(), Extents{}) {
    universes_view(0, 0, player_1 - 1, player_2 - 1) = 1;
  }

  bool QuantumGame::take_turn_player_1() {
    return take_turn(universes_view);
  }

  bool QuantumGame::take_turn_player_2() {
    using namespace std::placeholders;
    return take_turn(std::bind(universes_view, _2, _1, _4, _3));
  }

  static constexpr auto desc_scores = std::views::iota(0, 21) | std::views::reverse;
  static constexpr auto positions = std::views::iota(0, 10);
  static constexpr auto rolls = std::views::iota(1, 4);

  bool QuantumGame::take_turn(auto &&access_fn) {
    using cor3ntin::rangesnext::product;
    return AoC::accumulate<bool>(
            product(desc_scores, desc_scores, positions, positions)
                    | std::views::transform([&access_fn](auto tuple) {
                        auto [score_1, score_2, player_1, player_2] = tuple;
                        auto population =
                                std::exchange(access_fn(score_1, score_2, player_1, player_2), 0);
                        return population
                               && AoC::accumulate<bool>(
                                       product(rolls, rolls, rolls)
                                               | std::views::transform([&](auto three_rolls) {
                                                   auto [roll_1, roll_2, roll_3] = three_rolls;
                                                   auto new_pos =
                                                           (player_1 + roll_1 + roll_2 + roll_3)
                                                           % 10;
                                                   auto new_score =
                                                           std::min(score_1 + new_pos + 1, 21);
                                                   access_fn(new_score, score_2, new_pos,
                                                             player_2) += population;
                                                   return new_score < 21;
                                                 }),
                                       false, std::logical_or{});
                      }),
            false, std::logical_or{});
  }

  auto QuantumGame::answer() const -> std::size_t {
    using cor3ntin::rangesnext::product;
    constexpr auto rng = product(desc_scores, positions, positions);
    auto const player_1_wins =
            AoC::accumulate<std::size_t>(rng | std::views::transform([this](auto tuple) {
                                           auto [score, player_1, player_2] = tuple;
                                           return universes_view(21, score, player_1, player_2);
                                         }));
    auto const player_2_wins =
            AoC::accumulate<std::size_t>(rng | std::views::transform([this](auto tuple) {
                                           auto [score, player_1, player_2] = tuple;
                                           return universes_view(score, 21, player_1, player_2);
                                         }));

    return std::max(player_1_wins, player_2_wins);
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

  auto Solution<21>::part2() const -> std::size_t {
    auto const game = Day21::play<Day21::QuantumGame>(player_1_starting_pos, player_2_starting_pos);
    return game.answer();
  }

}// namespace AoC
