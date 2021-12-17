#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day16;

constexpr std::string_view EXAMPLE_LITERAL_HEX = "D2FE28";
constexpr std::array<std::uint8_t, 24> EXAMPLE_LITERAL_BINARY = {
        1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0};

constexpr std::string_view EXAMPLE_OPERATOR_LEN0_HEX = "38006F45291200";
constexpr std::array<std::uint8_t, 56> EXAMPLE_OPERATOR_LEN0_BINARY = {
        0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0,
        0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

constexpr std::string_view EXAMPLE_OPERATOR_LEN1_HEX = "EE00D40C823060";
constexpr std::array<std::uint8_t, 56> EXAMPLE_OPERATOR_LEN1_BINARY = {
        1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0};

constexpr std::string_view ANOTHER_EXAMPLE_1_HEX = "8A004A801A8002F478";
constexpr std::string_view ANOTHER_EXAMPLE_2_HEX = "620080001611562C8802118E34";
constexpr std::string_view ANOTHER_EXAMPLE_3_HEX = "C0015000016115A2E0802F182340";
constexpr std::string_view ANOTHER_EXAMPLE_4_HEX = "A0016C880162017C3686B18A3D4780";

TEST(Day16, bits_are_decoded_from_hex_stream) {
  auto test_example = [](auto const &hex, auto const &binary) {
    using cor3ntin::rangesnext::to;
    using ::testing::ElementsAreArray;
    std::stringstream stream{std::string{hex}};
    auto bits = Day16::bits_from_hex_stream(stream);
    EXPECT_THAT(bits | to<std::vector>(), ElementsAreArray(binary));
  };

  test_example(EXAMPLE_LITERAL_HEX, EXAMPLE_LITERAL_BINARY);
  test_example(EXAMPLE_OPERATOR_LEN0_HEX, EXAMPLE_OPERATOR_LEN0_BINARY);
  test_example(EXAMPLE_OPERATOR_LEN1_HEX, EXAMPLE_OPERATOR_LEN1_BINARY);
}

TEST(Day16, literal_payload_is_decoded) {
  using cor3ntin::rangesnext::to;
  std::stringstream stream{std::string{EXAMPLE_LITERAL_HEX}};
  auto bits = Day16::bits_from_hex_stream(stream) | to<std::vector>();
  EXPECT_EQ(LiteralPayload{bits.begin() + 6}.number, 2021);
}

TEST(Day16, literal_packet_is_decoded) {
  auto packet = Packet{EXAMPLE_LITERAL_BINARY.begin()};
  EXPECT_EQ(packet.version, 6);
  EXPECT_EQ(std::get<LiteralPayload>(packet.payload).number, 2021);
}

TEST(Day16, operator_packet_with_length_type_0_is_decoded) {
  auto packet = Packet{EXAMPLE_OPERATOR_LEN0_BINARY.begin()};
  EXPECT_EQ(packet.version, 1);
  auto const &subpackets = std::get<OperatorPayload>(packet.payload).subpackets;
  EXPECT_THAT(subpackets, ::testing::SizeIs(2));
  EXPECT_EQ(subpackets[0].version, 6);
  EXPECT_EQ(std::get<LiteralPayload>(subpackets[0].payload).number, 10);
  EXPECT_EQ(subpackets[1].version, 2);
  EXPECT_EQ(std::get<LiteralPayload>(subpackets[1].payload).number, 20);
}

TEST(Day16, operator_packet_with_length_type_1_is_decoded) {
  auto packet = Packet{EXAMPLE_OPERATOR_LEN1_BINARY.begin()};
  EXPECT_EQ(packet.version, 7);
  auto const &subpackets = std::get<OperatorPayload>(packet.payload).subpackets;
  EXPECT_THAT(subpackets, ::testing::SizeIs(3));
  EXPECT_EQ(subpackets[0].version, 2);
  EXPECT_EQ(std::get<LiteralPayload>(subpackets[0].payload).number, 1);
  EXPECT_EQ(subpackets[1].version, 4);
  EXPECT_EQ(std::get<LiteralPayload>(subpackets[1].payload).number, 2);
  EXPECT_EQ(subpackets[2].version, 1);
  EXPECT_EQ(std::get<LiteralPayload>(subpackets[2].payload).number, 3);
}

TEST(Day16, more_examples_are_decoded) {
  auto test = [](std::string_view hex, Packet const &expected) {
    using cor3ntin::rangesnext::to;
    std::stringstream stream{std::string{hex}};
    auto bits = Day16::bits_from_hex_stream(stream) | to<std::vector>();
    auto actual = Packet{bits.begin()};
    EXPECT_EQ(actual, expected);
  };

  test(ANOTHER_EXAMPLE_1_HEX,
       Packet{4, OperatorPayload{{Packet{
                         1, OperatorPayload{{Packet{
                                    5, OperatorPayload{{Packet{6, LiteralPayload{15}}}}}}}}}}});
  test(ANOTHER_EXAMPLE_2_HEX,
       Packet{3, OperatorPayload{{Packet{0, OperatorPayload{{Packet{0, LiteralPayload{10}},
                                                             Packet{5, LiteralPayload{11}}}}},
                                  Packet{1, OperatorPayload{{Packet{0, LiteralPayload{12}},
                                                             Packet{3, LiteralPayload{13}}}}}}}});
}

TEST(Day16, version_sums) {
  auto test = [](std::string_view hex, std::size_t expected_sum) {
    using cor3ntin::rangesnext::to;
    std::stringstream stream{std::string{hex}};
    auto bits = Day16::bits_from_hex_stream(stream) | to<std::vector>();
    auto actual = Packet{bits.begin()};
    EXPECT_EQ(actual.version_sum(), expected_sum);
  };

  test(ANOTHER_EXAMPLE_1_HEX, 16);
  test(ANOTHER_EXAMPLE_2_HEX, 12);
  test(ANOTHER_EXAMPLE_3_HEX, 23);
  test(ANOTHER_EXAMPLE_4_HEX, 31);
}
