#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day18;

constexpr std::array<std::string_view, 10> EXAMPLE_HOMEWORK = {
        "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
        "[[[5,[2,8]],4],[5,[[9,9],0]]]",
        "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
        "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
        "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
        "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
        "[[[[5,4],[7,7]],8],[[8,3],8]]",
        "[[9,3],[[9,9],[6,[4,9]]]]",
        "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
        "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"};

TEST(Day18, magnitude) {
  EXPECT_EQ(magnitude("[9,1]"), 29);
  EXPECT_EQ(magnitude("[1,9]"), 21);
  EXPECT_EQ(magnitude("[[9,1],[1,9]]"), 129);
  EXPECT_EQ(magnitude("[[1,2],[[3,4],5]]"), 143);
  EXPECT_EQ(magnitude("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]"), 1384);
  EXPECT_EQ(magnitude("[[[[1,1],[2,2]],[3,3]],[4,4]]"), 445);
  EXPECT_EQ(magnitude("[[[[3,0],[5,3]],[4,4]],[5,5]]"), 791);
  EXPECT_EQ(magnitude("[[[[5,0],[7,4]],[5,5]],[6,6]]"), 1137);
  EXPECT_EQ(magnitude("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]"), 3488);
  EXPECT_EQ(magnitude("[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]"), 4140);
}

TEST(Day18, try_explode_modifies_explodable_numbers_and_returns_true) {
  auto test = [](std::string input, std::string_view expected) {
    EXPECT_TRUE(try_explode(input));
    EXPECT_EQ(input, expected);
  };
  test("[[[[[9,8],1],2],3],4]", "[[[[0,9],2],3],4]");
  test("[7,[6,[5,[4,[3,2]]]]]", "[7,[6,[5,[7,0]]]]");
  test("[[6,[5,[4,[3,2]]]],1]", "[[6,[5,[7,0]]],3]");
  test("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
  test("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]");
}

TEST(Day18, try_split_modifies_splittable_numbers_and_returns_true) {
  auto test = [](std::string input, std::string_view expected) {
    EXPECT_TRUE(try_split(input));
    EXPECT_EQ(input, expected);
  };
  test("10", "[5,5]");
  test("11", "[5,6]");
  test("12", "[6,6]");
  test("[[[[0,7],4],[15,[0,13]]],[1,1]]", "[[[[0,7],4],[[7,8],[0,13]]],[1,1]]");
  test("[[[[0,7],4],[[7,8],[0,13]]],[1,1]]", "[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]");
}

TEST(Day18, reduce_applies_multiple_explosions_and_splits_in_the_correct_order) {
  auto test = [](std::string input, std::string_view expected) {
    reduce(input);
    EXPECT_EQ(input, expected);
  };
  test("[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]", "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
}

TEST(Day18, addition_yields_reduced_result) {
  EXPECT_EQ(add("[1,2]", "[[3,4],5]"), "[[1,2],[[3,4],5]]");
  EXPECT_EQ(add("[[[[4,3],4],4],[7,[[8,4],9]]]", "[1,1]"), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
  EXPECT_EQ(add("[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]", "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]"),
            "[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]");
  EXPECT_EQ(add("[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]",
                "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]"),
            "[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]");
  EXPECT_EQ(add("[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]",
                "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]"),
            "[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]");
  EXPECT_EQ(add("[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]",
                "[7,[5,[[3,8],[1,4]]]]"),
            "[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]");
  EXPECT_EQ(add("[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]",
                "[[2,[2,2]],[8,[8,1]]]"),
            "[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]");
  EXPECT_EQ(add("[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]", "[2,9]"),
            "[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]");
  EXPECT_EQ(
          add("[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]", "[1,[[[9,3],9],[[9,0],[0,7]]]]"),
          "[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]");
  EXPECT_EQ(
          add("[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]", "[[[5,[7,4]],7],1]"),
          "[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]");
  EXPECT_EQ(add("[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]", "[[[[4,2],2],6],[8,7]]"),
            "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]");
}

TEST(Day18, summing_doublets) {
  constexpr std::array<std::string_view, 4> list = {"[1,1]", "[2,2]", "[3,3]", "[4,4]"};
  auto sum = add_all(list);
  EXPECT_EQ(sum, "[[[[1,1],[2,2]],[3,3]],[4,4]]");
  sum = add(sum, "[5,5]");
  EXPECT_EQ(sum, "[[[[3,0],[5,3]],[4,4]],[5,5]]");
  sum = add(sum, "[6,6]");
  EXPECT_EQ(sum, "[[[[5,0],[7,4]],[5,5]],[6,6]]");
}

TEST(Day18, full_example_1) {
  constexpr std::array<std::string_view, 10> list = {
          "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
          "[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
          "[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
          "[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
          "[7,[5,[[3,8],[1,4]]]]",
          "[[2,[2,2]],[8,[8,1]]]",
          "[2,9]",
          "[1,[[[9,3],9],[[9,0],[0,7]]]]",
          "[[[5,[7,4]],7],1]",
          "[[[[4,2],2],6],[8,7]]"};
  EXPECT_EQ(add_all(list), "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]");
}

TEST(Day18, full_example_2) {
  EXPECT_EQ(add_all(EXAMPLE_HOMEWORK),
            "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]");
}

TEST(Day18, largest_magnitude_for_single_addition) {
  EXPECT_EQ(largest_magnitude_for_single_addition(EXAMPLE_HOMEWORK), 3993);
}
