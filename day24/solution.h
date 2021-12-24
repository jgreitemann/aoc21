#pragma once

#include "../solution.h"
#include "../utils.h"

#include <array>
#include <span>
#include <variant>

namespace Day24 {

  enum class Register { W, X, Y, Z };

  using Registers = std::array<int, 4>;

  using Parameter = std::variant<Register, int>;

  namespace Instructions {
    struct Input {
      Register reg{};
      constexpr bool operator==(Input const &) const noexcept = default;
    };

    struct Addition {
      Register lhs{};
      Parameter rhs{};
      constexpr bool operator==(Addition const &) const noexcept = default;
    };

    struct Multiplication {
      Register lhs{};
      Parameter rhs{};
      constexpr bool operator==(Multiplication const &) const noexcept = default;
    };

    struct Division {
      Register lhs{};
      Parameter rhs{};
      constexpr bool operator==(Division const &) const noexcept = default;
    };

    struct Modulo {
      Register lhs{};
      Parameter rhs{};
      constexpr bool operator==(Modulo const &) const noexcept = default;
    };

    struct Equality {
      Register lhs{};
      Parameter rhs{};
      constexpr bool operator==(Equality const &) const noexcept = default;
    };

  }// namespace Instructions

  using Instruction =
          std::variant<Instructions::Input, Instructions::Addition, Instructions::Multiplication,
                       Instructions::Division, Instructions::Modulo, Instructions::Equality>;

  auto run(std::span<Instruction const> program, std::span<int const> input) -> Registers;

  auto as_number(std::span<int const> digits) -> std::size_t;

  template <std::size_t len>
  auto generate_model_numbers() -> cor3ntin::rangesnext::generator<std::array<int, len>> {
    constexpr std::array digits = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    auto tuples = [&digits]<std::size_t... I>(std::index_sequence<I...>) {
      using cor3ntin::rangesnext::product;
      return product((I, digits)...);
    }
    (std::make_index_sequence<len>{});
    for (auto const &tuple : tuples) {
      co_yield[&tuple]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array{std::get<I>(tuple)...};
      }
      (std::make_index_sequence<len>{});
    }
  }

}// namespace Day24

namespace std {
  std::istream &operator>>(std::istream &is, Day24::Instruction &instruction);
}

namespace AoC {

  template <>
  struct Solution<24> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;

  private:
    std::vector<Day24::Instruction> program;
  };

}// namespace AoC
