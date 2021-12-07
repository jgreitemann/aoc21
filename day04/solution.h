#pragma once

#include "../solution.h"

#include <array>
#include <ranges>
#include <span>
#include <vector>

#include <experimental/mdspan>

namespace Day04 {

  constexpr int MK = -1;// read "mark"

  using AllBoardsExtents = std::experimental::extents<std::experimental::dynamic_extent, 5, 5>;
  using BoardExtents = std::experimental::extents<5, 5>;
  using AllBoardsConstView = std::experimental::mdspan<int const, AllBoardsExtents>;
  using AllBoardsView = std::experimental::mdspan<int, AllBoardsExtents>;
  using BoardConstView = std::experimental::mdspan<int const, BoardExtents>;
  using BoardView = std::experimental::mdspan<int, BoardExtents>;

  constexpr auto get_board(AllBoardsConstView boards, std::size_t i) -> BoardConstView {
    return std::experimental::submdspan(boards, i, std::experimental::full_extent,
                                        std::experimental::full_extent);
  }

  constexpr auto get_board(AllBoardsView boards, std::size_t i) -> BoardView {
    return std::experimental::submdspan(boards, i, std::experimental::full_extent,
                                        std::experimental::full_extent);
  }

  constexpr auto iter_boards(AllBoardsView boards) {
    return std::views::iota(0ul, boards.extent(0))
           | std::views::transform([boards](std::size_t i) { return get_board(boards, i); });
  }

  auto is_bingo(BoardConstView board) -> bool;
  auto sum_of_unmarked_numbers(BoardConstView board) -> int;
  void mark(BoardView board, int number);
  auto get_winning_score(AllBoardsView boards, std::span<int const> numbers) -> int;
  auto get_losing_score(AllBoardsView boards, std::span<int const> numbers) -> int;

}// namespace Day04

namespace AoC {

  template <>
  struct Solution<4> {
    explicit Solution(std::istream &);
    auto part1() const -> int;
    auto part2() const -> int;

  private:
    std::vector<int> numbers;
    std::vector<int> boards_storage;
  };

}// namespace AoC
