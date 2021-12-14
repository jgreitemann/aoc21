#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <sstream>
#include <string>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day14;

constexpr std::string_view EXAMPLE_POLYMER_TEMPLATE = "NNCB";

constexpr std::string_view EXAMPLE_RULES_INPUT = R"(CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C
)";

constexpr std::array EXAMPLE_RULES = {
        Rule{{'C', 'H'}, 'B'}, Rule{{'H', 'H'}, 'N'}, Rule{{'C', 'B'}, 'H'}, Rule{{'N', 'H'}, 'C'},
        Rule{{'H', 'B'}, 'C'}, Rule{{'H', 'C'}, 'B'}, Rule{{'H', 'N'}, 'C'}, Rule{{'N', 'N'}, 'C'},
        Rule{{'B', 'H'}, 'H'}, Rule{{'N', 'C'}, 'B'}, Rule{{'N', 'B'}, 'B'}, Rule{{'B', 'N'}, 'B'},
        Rule{{'B', 'B'}, 'N'}, Rule{{'B', 'C'}, 'B'}, Rule{{'C', 'C'}, 'N'}, Rule{{'C', 'N'}, 'C'}};

TEST(Day14, parse_rules) {
  using ::testing::ElementsAreArray;
  std::stringstream stream{std::string{EXAMPLE_RULES_INPUT}};
  EXPECT_THAT(parse_rules(stream), ElementsAreArray(EXAMPLE_RULES));
}

TEST(Day14, react) {
  std::string polymer{EXAMPLE_POLYMER_TEMPLATE};
  EXPECT_EQ(polymer = react(std::move(polymer), EXAMPLE_RULES), "NCNBCHB");
  EXPECT_EQ(polymer = react(std::move(polymer), EXAMPLE_RULES), "NBCCNBBBCBHCB");
  EXPECT_EQ(polymer = react(std::move(polymer), EXAMPLE_RULES), "NBBBCNCCNBBNBNBBCHBHHBCHB");
  EXPECT_EQ(polymer = react(std::move(polymer), EXAMPLE_RULES),
            "NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB");
}

TEST(Day14, polymer_growth) {
  std::string polymer{EXAMPLE_POLYMER_TEMPLATE};
  using ::testing::SizeIs;
  EXPECT_THAT(chain_react(polymer, EXAMPLE_RULES, 5), SizeIs(97));
  EXPECT_THAT(chain_react(polymer, EXAMPLE_RULES, 10), SizeIs(3073));
}

TEST(Day14, polymer_histogram) {
  std::string polymer{EXAMPLE_POLYMER_TEMPLATE};
  auto histogram = histogrammize(chain_react(polymer, EXAMPLE_RULES, 10));
  EXPECT_EQ(histogram['B'], 1749);
  EXPECT_EQ(histogram['C'], 298);
  EXPECT_EQ(histogram['H'], 161);
  EXPECT_EQ(histogram['N'], 865);

  EXPECT_EQ(minmax_diff(histogram), 1588);
}
