#include "solution.h"

namespace Day16 {

  auto bits_from_hex_stream(std::istream &is) -> BitsGenerator {
    char hex_digit;
    while (is >> hex_digit) {
      auto binary = [hex_digit]() -> std::array<std::uint8_t, 4> {
        switch (hex_digit) {
          case '0':
            return {0, 0, 0, 0};
          case '1':
            return {0, 0, 0, 1};
          case '2':
            return {0, 0, 1, 0};
          case '3':
            return {0, 0, 1, 1};
          case '4':
            return {0, 1, 0, 0};
          case '5':
            return {0, 1, 0, 1};
          case '6':
            return {0, 1, 1, 0};
          case '7':
            return {0, 1, 1, 1};
          case '8':
            return {1, 0, 0, 0};
          case '9':
            return {1, 0, 0, 1};
          case 'A':
            return {1, 0, 1, 0};
          case 'B':
            return {1, 0, 1, 1};
          case 'C':
            return {1, 1, 0, 0};
          case 'D':
            return {1, 1, 0, 1};
          case 'E':
            return {1, 1, 1, 0};
          case 'F':
            return {1, 1, 1, 1};
          default:
            throw std::runtime_error("Invalid hex digit");
        }
      }();
      for (auto binary_digit : binary)
        co_yield binary_digit;
    }
  }

  std::ostream &operator<<(std::ostream &os, const LiteralPayload &literal) {
    return os << "Literal(" << literal.number << ')';
  }

  std::ostream &operator<<(std::ostream &os, const OperatorPayload &op) {
    os << "Operator[";
    if (!op.subpackets.empty()) {
      os << op.subpackets.front();
      for (auto const &x : std::ranges::subrange{op.subpackets.begin() + 1, op.subpackets.end()})
        os << ", " << x;
    }
    return os << "]";
  }

  std::ostream &operator<<(std::ostream &os, const Packet &p) {
    os << 'v' << p.version << ':';
    std::visit([&os](auto const &payload) { os << payload; }, p.payload);
    return os;
  }

  OperatorPayload::OperatorPayload(std::vector<Packet> subpackets)
      : subpackets{std::move(subpackets)} {}

  Packet::Packet(std::uint8_t version, Packet::PayloadVariant payload)
      : version{version}
      , payload{std::move(payload)} {}

  auto Packet::version_sum() const -> std::size_t {
    return version
           + std::visit(AoC::overload{[](LiteralPayload const &) { return 0ul; },
                                      [](OperatorPayload const &payload) {
                                        return AoC::accumulate(
                                                payload.subpackets, 0ul,
                                                [](std::size_t acc, Packet const &p) {
                                                  return acc + p.version_sum();
                                                });
                                      }},
                        payload);
  }

}// namespace Day16

namespace AoC {

  Solution<16>::Solution(std::istream &stream)
      : root{[&] {
        using cor3ntin::rangesnext::to;
        auto bits = Day16::bits_from_hex_stream(stream) | to<std::vector>();
        return Day16::Packet{bits.begin()};
      }()} {}

  auto Solution<16>::part1() const -> std::size_t { return root.version_sum(); }

}// namespace AoC
