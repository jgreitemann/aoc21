#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <numeric>

using namespace Day06;

constexpr std::array EXAMPLE_INITIAL_POPULATION = {3, 4, 3, 1, 2};
constexpr Census EXAMPLE_INITIAL_CENSUS = {0, 1, 1, 2, 1, 0, 0, 0, 0};
static_assert(EXAMPLE_INITIAL_POPULATION.size() == number_of_fish(EXAMPLE_INITIAL_CENSUS));

constexpr std::array EXAMPLE_18TH_DAY_POPULATION = {6, 0, 6, 4, 5, 6, 0, 1, 1, 2, 6, 0, 1,
                                                    1, 1, 2, 2, 3, 3, 4, 6, 7, 8, 8, 8, 8};
constexpr Census EXAMPLE_18TH_DAY_CENSUS = {3, 5, 3, 2, 2, 1, 5, 1, 4};
static_assert(EXAMPLE_18TH_DAY_POPULATION.size() == number_of_fish(EXAMPLE_18TH_DAY_CENSUS));

TEST(Day06, histogrammize_initial_population) {
  using ::testing::ElementsAreArray;
  EXPECT_THAT(Day06::histogrammize(EXAMPLE_INITIAL_POPULATION),
              ElementsAreArray(EXAMPLE_INITIAL_CENSUS));
}

TEST(Day06, histogrammize_population_of_18th_day) {
  using ::testing::ElementsAreArray;
  EXPECT_THAT(Day06::histogrammize(EXAMPLE_18TH_DAY_POPULATION),
              ElementsAreArray(EXAMPLE_18TH_DAY_CENSUS));
}

TEST(Day06, transition) {
  using ::testing::ElementsAreArray;
  Census census = EXAMPLE_INITIAL_CENSUS;
  // clang-format off
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{2,3,2,0,1})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{1,2,1,6,0,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{0,1,0,5,6,7,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{6,0,6,4,5,6,7,8,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{5,6,5,3,4,5,6,7,7,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{4,5,4,2,3,4,5,6,6,7})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{3,4,3,1,2,3,4,5,5,6})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{2,3,2,0,1,2,3,4,4,5})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{1,2,1,6,0,1,2,3,3,4,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{0,1,0,5,6,0,1,2,2,3,7,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{6,0,6,4,5,6,0,1,1,2,6,7,8,8,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{5,6,5,3,4,5,6,0,0,1,5,6,7,7,7,8,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{4,5,4,2,3,4,5,6,6,0,4,5,6,6,6,7,7,8,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{3,4,3,1,2,3,4,5,5,6,3,4,5,5,5,6,6,7,7,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{2,3,2,0,1,2,3,4,4,5,2,3,4,4,4,5,5,6,6,7})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{1,2,1,6,0,1,2,3,3,4,1,2,3,3,3,4,4,5,5,6,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{0,1,0,5,6,0,1,2,2,3,0,1,2,2,2,3,3,4,4,5,7,8})));
  EXPECT_THAT(census = transition(census), ElementsAreArray(histogrammize(std::array{6,0,6,4,5,6,0,1,1,2,6,0,1,1,1,2,2,3,3,4,6,7,8,8,8,8})));
  // clang-format on
}

TEST(Day06, transition_n) {
  using ::testing::ElementsAreArray;
  EXPECT_THAT(transition_n(EXAMPLE_INITIAL_CENSUS, 18), ElementsAreArray(EXAMPLE_18TH_DAY_CENSUS));
}

TEST(Day06, number_of_fish) {
  EXPECT_EQ(number_of_fish(EXAMPLE_INITIAL_CENSUS), 5);
  EXPECT_EQ(number_of_fish(EXAMPLE_18TH_DAY_CENSUS), 26);
  EXPECT_EQ(number_of_fish(transition_n(EXAMPLE_INITIAL_CENSUS, 80)), 5934);
  EXPECT_EQ(number_of_fish(transition_n(EXAMPLE_INITIAL_CENSUS, 256)), 26984457539ul);
}
