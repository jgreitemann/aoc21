#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../utils.h"
#include "solution.h"

#include <array>
#include <sstream>
#include <string>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day08;

constexpr std::string_view SINGLE_EXAMPLE_INPUT =
        "acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf";
static const Entry SINGLE_EXAMPLE_ENTRY = {
        {"abcdefg", "bcdef", "acdfg", "abcdf", "abd", "abcdef", "bcdefg", "abef", "abcdeg", "ab"},
        {"bcdef", "abcdf", "bcdef", "abcdf"}};

static const std::array<std::string, 10> SOLVED_SINGLE_EXAMPLE_PATTERNS = {
        "abcdeg", "ab", "acdfg", "abcdf", "abef", "bcdef", "bcdefg", "abd", "abcdefg", "abcdef"};

constexpr std::string_view LARGE_EXAMPLE_INPUT =
        R"(be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe
edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc
fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg
fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb
aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea
fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb
dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe
bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef
egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb
gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce
)";

constexpr std::array LARGE_EXAMPLE_UNIQUE_DIGIT_COUNTS = {2, 3, 3, 1, 3, 4, 3, 1, 4, 2};
constexpr std::array LARGE_EXAMPLE_OUTPUT_VALUES = {8394, 9781, 1197, 9361, 4873,
                                                    8418, 4548, 1625, 8717, 4315};

TEST(Day08, parse_input) {
  std::stringstream stream{std::string{SINGLE_EXAMPLE_INPUT}};
  Entry entry;
  stream >> entry;
  EXPECT_EQ(entry, SINGLE_EXAMPLE_ENTRY);
}

TEST(Day08, number_of_unique_output_digits) {
  EXPECT_EQ(number_of_unique_output_digits(SINGLE_EXAMPLE_ENTRY), 0);

  std::stringstream stream{std::string{LARGE_EXAMPLE_INPUT}};
  auto entries = AoC::parse_vec<Entry>(stream);

  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  auto counts = entries | std::views::transform(number_of_unique_output_digits) | to<std::vector>();
  EXPECT_THAT(counts, ElementsAreArray(LARGE_EXAMPLE_UNIQUE_DIGIT_COUNTS));
}

TEST(Day08, solve_single_example) {
  auto patterns = SINGLE_EXAMPLE_ENTRY.patterns;
  solve(patterns);

  using ::testing::ElementsAreArray;
  EXPECT_THAT(patterns, ElementsAreArray(SOLVED_SINGLE_EXAMPLE_PATTERNS));
}

TEST(Day08, solve_and_decode_output) {
  std::stringstream stream{std::string{LARGE_EXAMPLE_INPUT}};
  auto entries = AoC::parse_vec<Entry>(stream);

  std::ranges::for_each(entries | std::views::transform(&Entry::patterns), solve);

  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(entries | std::views::transform(std::mem_fn(&Entry::output)) | to<std::vector>(),
              ElementsAreArray(LARGE_EXAMPLE_OUTPUT_VALUES));
}