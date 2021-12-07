#include "solution.h"
#include "../utils.h"

#include <string_view>

#include <cor3ntin/rangesnext/enumerate.hpp>
#include <cor3ntin/rangesnext/to.hpp>

namespace Day04 {

  constexpr auto row(BoardConstView board, std::size_t i) {
    auto row_view = std::experimental::submdspan(board, i, std::experimental::full_extent);
    return std::views::iota(0ul, row_view.extent(0))
           | std::views::transform([row_view](std::size_t j) { return row_view(j); });
  }

  constexpr auto rows(BoardConstView board) {
    return std::views::iota(0ul, board.extent(0))
           | std::views::transform([board](std::size_t i) { return row(board, i); });
  }

  constexpr auto column(BoardConstView board, std::size_t j) {
    auto column_view = std::experimental::submdspan(board, std::experimental::full_extent, j);
    return std::views::iota(0ul, column_view.extent(0))
           | std::views::transform([column_view](std::size_t i) { return column_view(i); });
  }

  constexpr auto columns(BoardConstView board) {
    return std::views::iota(0ul, board.extent(1))
           | std::views::transform([board](std::size_t j) { return column(board, j); });
  }

  auto is_bingo(BoardConstView board) -> bool {
    using std::ranges::all_of;
    using std::ranges::any_of;
    constexpr auto is_marked = [](int field) { return field == MK; };
    return any_of(rows(board), [](auto row) { return all_of(row, is_marked); })
           || any_of(columns(board), [](auto column) { return all_of(column, is_marked); });
  }

  auto sum_of_unmarked_numbers(BoardConstView board) -> int {
    auto unmarked_numbers = std::span{board.data(), board.data() + board.size()}
                            | std::views::filter([](int field) { return field != MK; })
                            | std::views::common;

    return std::accumulate(unmarked_numbers.begin(), unmarked_numbers.end(), 0);
  }

  void mark(BoardView board, int number) {
    for (int &field :
         std::span{board.data(), board.data() + board.size()}
                 | std::views::filter([number](int &field) { return field == number; })) {
      field = MK;
    }
  }

  auto get_winning_score(AllBoardsView boards, std::span<int const> numbers) -> int {
    auto const all_boards = iter_boards(boards);
    for (int n : numbers) {
      for (auto board : all_boards)
        mark(board, n);

      if (auto winner_it = std::ranges::find_if(all_boards, is_bingo);
          winner_it != all_boards.end())
        return n * sum_of_unmarked_numbers(*winner_it);
    }
    return -1;
  }

  auto get_losing_score(AllBoardsView boards, std::span<int const> numbers) -> int {
    using cor3ntin::rangesnext::enumerate;
    using cor3ntin::rangesnext::to;
    auto remaining_boards = iter_boards(boards) | to<std::vector>();
    for (int n : numbers) {
      // mark n on all boards, detecting boards which got bingo this turn
      std::vector<std::size_t> finishers;
      for (auto [i, board] : remaining_boards | enumerate) {
        mark(board, n);
        if (is_bingo(board))
          finishers.push_back(i);
      }

      // last board(s) finished?
      if (finishers.size() == remaining_boards.size())
        return n * sum_of_unmarked_numbers(remaining_boards.back());

      // eliminate finishers (in reverse order as to not shift indices)
      for (auto i : finishers | std::views::reverse)
        remaining_boards.erase(remaining_boards.begin() + i);
    }
    return -1;
  }

}// namespace Day04

namespace AoC {

  Solution<4>::Solution(std::istream &stream)
      : numbers{AoC::parse_comma_separated_ints_on_line(stream)}
      , boards_storage{AoC::parse_vec<int>(stream)} {}

  auto Solution<4>::part1() const -> int {
    auto local_boards_storage = boards_storage;
    Day04::AllBoardsView boards{local_boards_storage.data(), local_boards_storage.size() / 25};
    return Day04::get_winning_score(boards, numbers);
  }

  auto Solution<4>::part2() const -> int {
    auto local_boards_storage = boards_storage;
    Day04::AllBoardsView boards{local_boards_storage.data(), local_boards_storage.size() / 25};
    return Day04::get_losing_score(boards, numbers);
  }

}// namespace AoC
