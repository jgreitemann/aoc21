#pragma once

#include "../solution.h"
#include "../utils.h"

#include <iterator>
#include <span>
#include <variant>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day16 {

  using BitsGenerator = cor3ntin::rangesnext::generator<std::uint8_t>;

  auto bits_from_hex_stream(std::istream &is) -> BitsGenerator;

  template <typename InputIt>
  auto read_number(InputIt &&it, std::size_t n)
          -> std::size_t requires std::input_iterator<std::remove_reference_t<InputIt>> {
    auto begin = it;
    std::advance(it, n);
    return std::accumulate(begin, it, 0ul,
                           [](std::size_t acc, std::uint8_t digit) { return (acc << 1) + digit; });
  }

  struct Packet;

  struct LiteralPayload {
    template <typename InputIt>
    explicit LiteralPayload(
            InputIt &&bits_it) requires std::input_iterator<std::remove_reference_t<InputIt>>
        : number{[&] {
          using Chunk = std::array<std::uint8_t, 5>;
          std::vector<Chunk> chunks;
          for (auto chunk : AoC::chunks<Chunk{}.size()>(bits_it)) {
            chunks.push_back(std::move(chunk));
            if (chunks.back()[0] == 0)
              break;
          }
          return AoC::accumulate(chunks, 0ul, [](std::size_t acc, Chunk const &digits) {
            return (acc << 4) + read_number(digits.begin() + 1, 4);
          });
        }()} {}

    constexpr explicit LiteralPayload(std::size_t number)
        : number{number} {}

    bool operator==(LiteralPayload const &) const = default;

    std::size_t number;
  };

  struct OperatorPayload {
    template <typename InputIt>
    explicit OperatorPayload(
            InputIt &&bits_it) requires std::input_iterator<std::remove_reference_t<InputIt>>
        : subpackets{[&] {
          auto mode = read_number(bits_it, 1);
          std::vector<Packet> pkg;
          if (mode == 0) {
            auto length = read_number(bits_it, 15);
            auto begin_it = bits_it;
            while (std::distance(begin_it, bits_it) < length)
              pkg.emplace_back(bits_it);
          } else {
            auto num_subpackets = read_number(bits_it, 11);
            for (auto _ : std::views::iota(0ul, num_subpackets))
              pkg.emplace_back(bits_it);
          }
          return pkg;
        }()} {}
    explicit OperatorPayload(std::vector<Packet> subpackets);

    bool operator==(OperatorPayload const &) const = default;

    std::vector<Packet> subpackets;
  };

  struct Packet {
    using PayloadVariant = std::variant<LiteralPayload, OperatorPayload>;

    template <typename InputIt>
    explicit Packet(InputIt &&bits) requires std::input_iterator<std::remove_reference_t<InputIt>>
        : version{read_number(bits, 3)}, payload{[&]() -> PayloadVariant {
          if (read_number(bits, 3) == 4)
            return LiteralPayload{bits};
          else
            return OperatorPayload{bits};
        }()} {}

    Packet(std::uint8_t version, PayloadVariant payload);

    bool operator==(Packet const &) const = default;

    auto version_sum() const -> std::size_t;

    std::size_t version;
    std::variant<LiteralPayload, OperatorPayload> payload;
  };

  std::ostream &operator<<(std::ostream &os, LiteralPayload const &literal);

  std::ostream &operator<<(std::ostream &os, OperatorPayload const &op);

  std::ostream &operator<<(std::ostream &os, Packet const &p);


}// namespace Day16

namespace AoC {

  template <>
  struct Solution<16> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    Day16::Packet root;
  };

}// namespace AoC
