#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <span>
#include <string_view>

#include <fmt/core.h>

using namespace Day24;

constexpr std::string_view EXAMPLE_PROG1_INPUT = R"(inp x
mul x -1
)";

constexpr std::array<Instruction, 2> EXAMPLE_PROG1 = {
        Instructions::Input{Register::X},
        Instructions::Multiplication{Register::X, -1},
};

constexpr std::string_view EXAMPLE_PROG2_INPUT = R"(inp z
inp x
mul z 3
eql z x
)";

constexpr std::array<Instruction, 4> EXAMPLE_PROG2 = {
        Instructions::Input{Register::Z},
        Instructions::Input{Register::X},
        Instructions::Multiplication{Register::Z, 3},
        Instructions::Equality{Register::Z, Register::X},
};

constexpr std::string_view EXAMPLE_PROG3_INPUT = R"(inp w
add z w
mod z 2
div w 2
add y w
mod y 2
div w 2
add x w
mod x 2
div w 2
mod w 2
)";

constexpr std::array<Instruction, 11> EXAMPLE_PROG3 = {
        Instructions::Input{Register::W},
        Instructions::Addition{Register::Z, Register::W},
        Instructions::Modulo{Register::Z, 2},
        Instructions::Division{Register::W, 2},
        Instructions::Addition{Register::Y, Register::W},
        Instructions::Modulo{Register::Y, 2},
        Instructions::Division{Register::W, 2},
        Instructions::Addition{Register::X, Register::W},
        Instructions::Modulo{Register::X, 2},
        Instructions::Division{Register::W, 2},
        Instructions::Modulo{Register::W, 2},
};

TEST(Day24, parse_program) {
  auto test = [](std::string_view input, std::span<Instruction const> expected) {
    using ::testing::ElementsAreArray;
    std::stringstream stream{std::string{input}};
    EXPECT_THAT(AoC::parse_vec<Instruction>(stream), ElementsAreArray(expected));
  };
  test(EXAMPLE_PROG1_INPUT, EXAMPLE_PROG1);
  test(EXAMPLE_PROG2_INPUT, EXAMPLE_PROG2);
  test(EXAMPLE_PROG3_INPUT, EXAMPLE_PROG3);
}

TEST(Day24, run_program) {
  EXPECT_EQ(run(EXAMPLE_PROG1, std::array{42}), (std::array{0, -42, 0, 0}));
  EXPECT_EQ(run(EXAMPLE_PROG1, std::array{-42}), (std::array{0, 42, 0, 0}));
  EXPECT_EQ(run(EXAMPLE_PROG1, std::array{7}), (std::array{0, -7, 0, 0}));

  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{1, 3}), (std::array{0, 3, 0, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{3, 9}), (std::array{0, 9, 0, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{1000, 3000}), (std::array{0, 3000, 0, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{1, 2}), (std::array{0, 2, 0, 0}));
  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{0, 1}), (std::array{0, 1, 0, 0}));
  EXPECT_EQ(run(EXAMPLE_PROG2, std::array{1, 0}), (std::array{0, 0, 0, 0}));

  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{0}), (std::array{0, 0, 0, 0}));
  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{1}), (std::array{0, 0, 0, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{5}), (std::array{0, 1, 0, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{11}), (std::array{1, 0, 1, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{15}), (std::array{1, 1, 1, 1}));
  EXPECT_EQ(run(EXAMPLE_PROG3, std::array{21}), (std::array{0, 1, 0, 1}));
}

TEST(Day24, generate_model_numbers) {
  using cor3ntin::rangesnext::to;
  auto nums = std::views::iota(0ul, 1000ul) | std::views::filter([](std::size_t n) {
                auto str = fmt::format("{:03}", n);
                return std::ranges::none_of(str, [](char c) { return c == '0'; });
              })
              | to<std::vector>();
  std::ranges::sort(nums, std::greater<>{});

  using ::testing::ElementsAreArray;
  EXPECT_THAT(generate_model_numbers<3>() | std::views::transform(&as_number) | to<std::vector>(),
              ElementsAreArray(nums));
}
