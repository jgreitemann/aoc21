#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day11;

constexpr Dyn2DExtents EXAMPLE_EXTENTS{10, 10};

// clang-format off
constexpr std::array EXAMPLE_DATA = {
        5,4,8,3,1,4,3,2,2,3,
        2,7,4,5,8,5,4,7,1,1,
        5,2,6,4,5,5,6,1,7,3,
        6,1,4,1,3,3,6,1,4,6,
        6,3,5,7,3,8,5,4,7,8,
        4,1,6,7,5,2,4,6,4,5,
        2,1,7,6,8,4,1,7,2,1,
        6,8,8,2,8,8,1,1,3,4,
        4,8,4,6,8,4,8,5,5,4,
        5,2,8,3,7,5,1,5,2,6,
};

constexpr std::array EXAMPLE_STEPS = {
        std::pair{1, std::array{
                6,5,9,4,2,5,4,3,3,4,
                3,8,5,6,9,6,5,8,2,2,
                6,3,7,5,6,6,7,2,8,4,
                7,2,5,2,4,4,7,2,5,7,
                7,4,6,8,4,9,6,5,8,9,
                5,2,7,8,6,3,5,7,5,6,
                3,2,8,7,9,5,2,8,3,2,
                7,9,9,3,9,9,2,2,4,5,
                5,9,5,7,9,5,9,6,6,5,
                6,3,9,4,8,6,2,6,3,7,
        }},

        std::pair{2, std::array{
                8,8,0,7,4,7,6,5,5,5,
                5,0,8,9,0,8,7,0,5,4,
                8,5,9,7,8,8,9,6,0,8,
                8,4,8,5,7,6,9,6,0,0,
                8,7,0,0,9,0,8,8,0,0,
                6,6,0,0,0,8,8,9,8,9,
                6,8,0,0,0,0,5,9,4,3,
                0,0,0,0,0,0,7,4,5,6,
                9,0,0,0,0,0,0,8,7,6,
                8,7,0,0,0,0,6,8,4,8,
        }},

        std::pair{3, std::array{
                0,0,5,0,9,0,0,8,6,6,
                8,5,0,0,8,0,0,5,7,5,
                9,9,0,0,0,0,0,0,3,9,
                9,7,0,0,0,0,0,0,4,1,
                9,9,3,5,0,8,0,0,6,3,
                7,7,1,2,3,0,0,0,0,0,
                7,9,1,1,2,5,0,0,0,9,
                2,2,1,1,1,3,0,0,0,0,
                0,4,2,1,1,2,5,0,0,0,
                0,0,2,1,1,1,9,0,0,0,
        }},

        std::pair{4, std::array{
                2,2,6,3,0,3,1,9,7,7,
                0,9,2,3,0,3,1,6,9,7,
                0,0,3,2,2,2,1,1,5,0,
                0,0,4,1,1,1,1,1,6,3,
                0,0,7,6,1,9,1,1,7,4,
                0,0,5,3,4,1,1,1,2,2,
                0,0,4,2,3,6,1,1,2,0,
                5,5,3,2,2,4,1,1,2,2,
                1,5,3,2,2,4,7,2,1,1,
                1,1,3,2,2,3,0,2,1,1,
        }},

        std::pair{5, std::array{
                4,4,8,4,1,4,4,0,0,0,
                2,0,4,4,1,4,4,0,0,0,
                2,2,5,3,3,3,3,4,9,3,
                1,1,5,2,3,3,3,2,7,4,
                1,1,8,7,3,0,3,2,8,5,
                1,1,6,4,6,3,3,2,3,3,
                1,1,5,3,4,7,2,2,3,1,
                6,6,4,3,3,5,2,2,3,3,
                2,6,4,3,3,5,8,3,2,2,
                2,2,4,3,3,4,1,3,2,2,
        }},

        std::pair{6, std::array{
                5,5,9,5,2,5,5,1,1,1,
                3,1,5,5,2,5,5,2,2,2,
                3,3,6,4,4,4,4,6,0,5,
                2,2,6,3,4,4,4,4,9,6,
                2,2,9,8,4,1,4,3,9,6,
                2,2,7,5,7,4,4,3,4,4,
                2,2,6,4,5,8,3,3,4,2,
                7,7,5,4,4,6,3,3,4,4,
                3,7,5,4,4,6,9,4,3,3,
                3,3,5,4,4,5,2,4,3,3,
        }},

        std::pair{7, std::array{
                6,7,0,7,3,6,6,2,2,2,
                4,3,7,7,3,6,6,3,3,3,
                4,4,7,5,5,5,5,8,2,7,
                3,4,9,6,6,5,5,7,0,9,
                3,5,0,0,6,2,5,6,0,9,
                3,5,0,9,9,5,5,5,6,6,
                3,4,8,6,6,9,4,4,5,3,
                8,8,6,5,5,8,5,5,5,5,
                4,8,6,5,5,8,0,6,4,4,
                4,4,6,5,5,7,4,6,4,4,
        }},

        std::pair{8, std::array{
                7,8,1,8,4,7,7,3,3,3,
                5,4,8,8,4,7,7,4,4,4,
                5,6,9,7,6,6,6,9,4,9,
                4,6,0,8,7,6,6,8,3,0,
                4,7,3,4,9,4,6,7,3,0,
                4,7,4,0,0,9,7,6,8,8,
                6,9,0,0,0,0,7,5,6,4,
                0,0,0,0,0,0,9,6,6,6,
                8,0,0,0,0,0,4,7,5,5,
                6,8,0,0,0,0,7,7,5,5,
        }},

        std::pair{9, std::array{
                9,0,6,0,0,0,0,6,4,4,
                7,8,0,0,0,0,0,9,7,6,
                6,9,0,0,0,0,0,0,8,0,
                5,8,4,0,0,0,0,0,8,2,
                5,8,5,8,0,0,0,0,9,3,
                6,9,6,2,4,0,0,0,0,0,
                8,0,2,1,2,5,0,0,0,9,
                2,2,2,1,1,3,0,0,0,9,
                9,1,1,1,1,2,8,0,9,7,
                7,9,1,1,1,1,9,9,7,6,
        }},

        std::pair{10, std::array{
                0,4,8,1,1,1,2,9,7,6,
                0,0,3,1,1,1,2,0,0,9,
                0,0,4,1,1,1,2,5,0,4,
                0,0,8,1,1,1,1,4,0,6,
                0,0,9,9,1,1,1,3,0,6,
                0,0,9,3,5,1,1,2,3,3,
                0,4,4,2,3,6,1,1,3,0,
                5,5,3,2,2,5,2,3,5,0,
                0,5,3,2,2,5,0,6,0,0,
                0,0,3,2,2,4,0,0,0,0,
        }},

        std::pair{20, std::array{
                3,9,3,6,5,5,6,4,5,2,
                5,6,8,6,5,5,6,8,0,6,
                4,4,9,6,5,5,5,6,9,0,
                4,4,4,8,6,5,5,5,8,0,
                4,4,5,6,8,6,5,5,7,0,
                5,6,8,0,0,8,6,5,7,7,
                7,0,0,0,0,0,9,8,9,6,
                0,0,0,0,0,0,0,3,4,4,
                6,0,0,0,0,0,0,3,6,4,
                4,6,0,0,0,0,9,5,4,3,
        }},

        std::pair{30, std::array{
                0,6,4,3,3,3,4,1,1,8,
                4,2,5,3,3,3,4,6,1,1,
                3,3,7,4,3,3,3,4,5,8,
                2,2,2,5,3,3,3,3,3,7,
                2,2,2,9,3,3,3,3,3,8,
                2,2,7,6,7,3,3,3,3,3,
                2,7,5,4,5,7,4,5,6,5,
                5,5,4,4,4,5,8,5,1,1,
                9,4,4,4,4,4,7,1,1,1,
                7,9,4,4,4,4,6,1,1,9,
        }},

        std::pair{40, std::array{
                6,2,1,1,1,1,1,9,8,1,
                0,4,2,1,1,1,1,1,1,9,
                0,0,4,2,1,1,1,1,1,5,
                0,0,0,3,1,1,1,1,1,5,
                0,0,0,3,1,1,1,1,1,6,
                0,0,6,5,6,1,1,1,1,1,
                0,5,3,2,3,5,1,1,1,1,
                3,3,2,2,2,3,4,5,9,7,
                2,2,2,2,2,2,2,9,7,6,
                2,2,2,2,2,2,2,7,6,2,
        }},

        std::pair{50, std::array{
                9,6,5,5,5,5,6,4,4,7,
                4,8,6,5,5,5,6,8,0,5,
                4,4,8,6,5,5,5,6,9,0,
                4,4,5,8,6,5,5,5,8,0,
                4,5,7,4,8,6,5,5,7,0,
                5,7,0,0,0,8,6,5,6,6,
                6,0,0,0,0,0,9,8,8,7,
                8,0,0,0,0,0,0,5,3,3,
                6,8,0,0,0,0,0,6,3,3,
                5,6,8,0,0,0,0,5,3,8,
        }},

        std::pair{60, std::array{
                2,5,3,3,3,3,4,2,0,0,
                2,7,4,3,3,3,4,6,4,0,
                2,2,6,4,3,3,3,4,5,8,
                2,2,2,5,3,3,3,3,3,7,
                2,2,2,5,3,3,3,3,3,8,
                2,2,8,7,8,3,3,3,3,3,
                3,8,5,4,5,7,3,4,5,5,
                1,8,5,4,4,5,8,6,1,1,
                1,1,7,5,4,4,7,1,1,1,
                1,1,1,5,4,4,6,1,1,1,
        }},

        std::pair{70, std::array{
                8,2,1,1,1,1,1,1,6,4,
                0,4,2,1,1,1,1,1,6,6,
                0,0,4,2,1,1,1,1,1,4,
                0,0,0,4,2,1,1,1,1,5,
                0,0,0,0,2,1,1,1,1,6,
                0,0,6,5,6,1,1,1,1,1,
                0,5,3,2,3,5,1,1,1,1,
                7,3,2,2,2,3,5,1,1,7,
                5,7,2,2,2,2,3,4,7,5,
                4,5,7,2,2,2,2,7,5,4,
        }},

        std::pair{80, std::array{
                1,7,5,5,5,5,5,6,9,7,
                5,9,6,5,5,5,5,6,0,9,
                4,4,8,6,5,5,5,6,8,0,
                4,4,5,8,6,5,5,5,8,0,
                4,5,7,0,8,6,5,5,7,0,
                5,7,0,0,0,8,6,5,6,6,
                7,0,0,0,0,0,8,6,6,6,
                0,0,0,0,0,0,0,9,9,0,
                0,0,0,0,0,0,0,8,0,0,
                0,0,0,0,0,0,0,0,0,0,
        }},

        std::pair{90, std::array{
                7,4,3,3,3,3,3,5,2,2,
                2,6,4,3,3,3,3,5,2,2,
                2,2,6,4,3,3,3,4,5,8,
                2,2,2,6,4,3,3,3,3,7,
                2,2,2,2,4,3,3,3,3,8,
                2,2,8,7,8,3,3,3,3,3,
                2,8,5,4,5,7,3,3,3,3,
                4,8,5,4,4,5,8,3,3,3,
                3,3,8,7,7,7,9,3,3,3,
                3,3,3,3,3,3,3,3,3,3,
        }},

        std::pair{100, std::array{
                0,3,9,7,6,6,6,8,6,6,
                0,7,4,9,7,6,6,9,1,8,
                0,0,5,3,9,7,6,9,3,3,
                0,0,0,4,2,9,7,8,2,2,
                0,0,0,4,2,2,9,8,9,2,
                0,0,5,3,2,2,2,8,7,7,
                0,5,3,2,2,2,2,9,6,6,
                9,3,2,2,2,2,8,9,6,6,
                7,9,2,2,2,8,6,8,6,6,
                6,7,8,9,9,9,8,7,6,6,
        }}
};
// clang-format on

TEST(Day11, intermediate_steps) {
  for (auto &&[steps, expected_energies] : EXAMPLE_STEPS) {
    auto actual_energies = EXAMPLE_DATA;
    EnergyView actual_energies_view{actual_energies.data(), EXAMPLE_EXTENTS};
    multi_step(actual_energies_view, steps);
    EXPECT_EQ(actual_energies, expected_energies) << "failed at steps=" << steps;
  }
}

TEST(Day11, number_of_flashes_in_single_steps) {
  auto energies = EXAMPLE_DATA;
  EnergyView energies_view{energies.data(), EXAMPLE_EXTENTS};
  EXPECT_EQ(step(energies_view), 0);
  EXPECT_EQ(step(energies_view), 35);
  EXPECT_EQ(step(energies_view), 45);
  EXPECT_EQ(step(energies_view), 16);
  EXPECT_EQ(step(energies_view), 8);
  EXPECT_EQ(step(energies_view), 1);
  EXPECT_EQ(step(energies_view), 7);
  EXPECT_EQ(step(energies_view), 24);
  EXPECT_EQ(step(energies_view), 39);
  EXPECT_EQ(step(energies_view), 29);
}

TEST(Day11, number_of_flashes_in_multi_steps) {
  auto energies = EXAMPLE_DATA;
  EnergyView energies_view{energies.data(), EXAMPLE_EXTENTS};
  EXPECT_EQ(multi_step(energies_view, 10), 204);
  EXPECT_EQ(multi_step(energies_view, 100 - 10), 1656 - 204);
}

TEST(Day11, second_order_flashes) {
  // clang-format off
  std::array energies {
    1,1,1,1,1,
    1,9,9,9,1,
    1,9,1,9,1,
    1,9,9,9,1,
    1,1,1,1,1,
  };
  std::array energies_after_one_step {
    3,4,5,4,3,
    4,0,0,0,4,
    5,0,0,0,5,
    4,0,0,0,4,
    3,4,5,4,3,
  };
  std::array energies_after_two_steps {
    4,5,6,5,4,
    5,1,1,1,5,
    6,1,1,1,6,
    5,1,1,1,5,
    4,5,6,5,4,
  };
  // clang-format on
  EnergyView energies_view{energies.data(), Dyn2DExtents{5, 5}};
  EXPECT_EQ(step(energies_view), 9);
  EXPECT_EQ(energies, energies_after_one_step);
  EXPECT_EQ(step(energies_view), 0);
  EXPECT_EQ(energies, energies_after_two_steps);
}

TEST(Day11, steps_until_sync) {
  auto energies = EXAMPLE_DATA;
  EnergyView energies_view{energies.data(), EXAMPLE_EXTENTS};
  EXPECT_EQ(steps_until_sync(energies_view), 195);
}