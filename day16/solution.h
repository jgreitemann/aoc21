#pragma once

#include "../solution.h"
#include "../utils.h"

#include <functional>
#include <iterator>
#include <span>
#include <variant>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day16 {

  struct minimum {
    template <typename T>
    constexpr auto operator()(T &&lhs, T &&rhs) const noexcept -> T {
      return std::min(lhs, rhs);
    }
  };

  struct maximum {
    template <typename T>
    constexpr auto operator()(T &&lhs, T &&rhs) const noexcept -> T {
      return std::max(lhs, rhs);
    }
  };

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

    constexpr auto value() -> std::size_t { return number; }

    std::size_t number;
  };

  template <std::invocable<std::size_t, std::size_t> Operation>
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

    explicit OperatorPayload(std::vector<Packet> subpackets)
        : subpackets{std::move(subpackets)} {}

    bool operator==(OperatorPayload const &) const = default;

    std::vector<Packet> subpackets;
  };

  struct Packet {
    using PayloadVariant =
            std::variant<LiteralPayload, OperatorPayload<std::plus<>>,
                         OperatorPayload<std::multiplies<>>, OperatorPayload<minimum>,
                         OperatorPayload<maximum>, OperatorPayload<std::greater<>>,
                         OperatorPayload<std::less<>>, OperatorPayload<std::equal_to<>>>;

    template <typename InputIt>
    explicit Packet(InputIt &&bits) requires std::input_iterator<std::remove_reference_t<InputIt>>
        : version{read_number(bits, 3)}, payload{[&]() -> PayloadVariant {
          switch (read_number(bits, 3)) {
            case 0:
              return OperatorPayload<std::plus<>>{bits};
            case 1:
              return OperatorPayload<std::multiplies<>>{bits};
            case 2:
              return OperatorPayload<minimum>{bits};
            case 3:
              return OperatorPayload<maximum>{bits};
            case 4:
              return LiteralPayload{bits};
            case 5:
              return OperatorPayload<std::greater<>>{bits};
            case 6:
              return OperatorPayload<std::less<>>{bits};
            case 7:
              return OperatorPayload<std::equal_to<>>{bits};
            default:
              throw std::runtime_error{"Unsupported packet type"};
          }
        }()} {}

    Packet(std::uint8_t version, PayloadVariant payload);

    bool operator==(Packet const &) const = default;

    auto version_sum() const -> std::size_t;

    auto eval() const noexcept -> std::size_t;

    std::size_t version;
    PayloadVariant payload;
  };

  constexpr auto operator_symbol(std::plus<>) noexcept -> std::string_view { return "+"; }
  constexpr auto operator_symbol(std::multiplies<>) noexcept -> std::string_view { return "*"; }
  constexpr auto operator_symbol(minimum) noexcept -> std::string_view { return "min"; }
  constexpr auto operator_symbol(maximum) noexcept -> std::string_view { return "max"; }
  constexpr auto operator_symbol(std::greater<>) noexcept -> std::string_view { return ">"; }
  constexpr auto operator_symbol(std::less<>) noexcept -> std::string_view { return "<"; }
  constexpr auto operator_symbol(std::equal_to<>) noexcept -> std::string_view { return "=="; }

  std::ostream &operator<<(std::ostream &os, LiteralPayload const &literal);

  std::ostream &operator<<(std::ostream &os, Packet const &p);

  template <typename Operation>
  std::ostream &operator<<(std::ostream &os, OperatorPayload<Operation> const &op) {
    os << "(";
    if (!op.subpackets.empty()) {
      os << op.subpackets.front();
      for (auto const &x : std::ranges::subrange{op.subpackets.begin() + 1, op.subpackets.end()})
        os << ' ' << operator_symbol(Operation{}) << ' ' << x;
      if (op.subpackets.size() == 1)
        os << '[' << operator_symbol(Operation{}) << ']';
    }
    return os << ")";
  }


}// namespace Day16

namespace AoC {

  template <>
  struct Solution<16> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    Day16::Packet root;
  };

}// namespace AoC
