#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <algorithm>
#include <array>

#include <cor3ntin/rangesnext/to.hpp>

constexpr std::array<int, 10> MEASUREMENTS = {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
constexpr std::array<int, 8> SLIDING_SUMS = {607, 618, 618, 617, 647, 716, 769, 792};

TEST(Day01, number_of_increases) {
  EXPECT_EQ(Day01::number_of_increases(MEASUREMENTS), 7);
  EXPECT_EQ(Day01::number_of_increases(SLIDING_SUMS), 5);
}

template <std::size_t N>
auto sliding_vec(std::vector<int> const &v) {
  using cor3ntin::rangesnext::to;
  return Day01::sliding_window<N>(v)
         | std::views::transform([](auto &&window) { return window | to<std::vector>(); })
         | to<std::vector>();
}

TEST(Day01, sliding_window) {
  using Res = std::vector<std::vector<int>>;
  EXPECT_EQ(sliding_vec<3>({}), Res{});
  EXPECT_EQ(sliding_vec<3>({1}), Res{});
  EXPECT_EQ(sliding_vec<3>({1, 2}), Res{});
  EXPECT_EQ(sliding_vec<3>({1, 2, 3}), (Res{{1, 2, 3}}));
  EXPECT_EQ(sliding_vec<3>({1, 2, 3, 4}), (Res{{1, 2, 3}, {2, 3, 4}}));
  EXPECT_EQ(sliding_vec<3>({1, 2, 3, 4, 5}), (Res{{1, 2, 3}, {2, 3, 4}, {3, 4, 5}}));
}

TEST(Day01, sliding_window_sums) {
  auto sums = Day01::sliding_window_sums(MEASUREMENTS);
  EXPECT_TRUE(std::ranges::equal(sums, SLIDING_SUMS));
}
