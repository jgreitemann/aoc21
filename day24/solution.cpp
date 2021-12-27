#include "solution.h"

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <cor3ntin/rangesnext/enumerate.hpp>
#include <fstream>

#include "compute_decompiled.h"
#include "compute_simplified.h"

namespace Day24 {

  auto read_parameter(std::istream &is) -> Parameter {
    std::string token;
    is >> token;
    if (token.size() == 1 && token.front() >= 'w' && token.front() <= 'z') {
      return static_cast<Register>(token.front() - 'w');
    } else {
      return std::stoi(token);
    }
  }

  auto execute(Registers registers, Instruction const &instr, std::input_iterator auto &input)
          -> Registers {
    auto access = [](Registers &registers, Register reg) -> int & {
      return registers[static_cast<std::size_t>(reg)];
    };
    auto read_parameter = [access](Registers &registers, Parameter const &param) -> int {
      return std::visit(AoC::overload{[&](Register reg) -> int { return access(registers, reg); },
                                      [](int literal) -> int { return literal; }},
                        param);
    };
    std::visit(AoC::overload{
                       [&](Instructions::Input const &instr) -> void {
                         access(registers, instr.reg) = *(input++);
                       },
                       [&](Instructions::Addition const &instr) -> void {
                         access(registers, instr.lhs) += read_parameter(registers, instr.rhs);
                       },
                       [&](Instructions::Multiplication const &instr) -> void {
                         access(registers, instr.lhs) *= read_parameter(registers, instr.rhs);
                       },
                       [&](Instructions::Division const &instr) -> void {
                         access(registers, instr.lhs) /= read_parameter(registers, instr.rhs);
                       },
                       [&](Instructions::Modulo const &instr) -> void {
                         access(registers, instr.lhs) %= read_parameter(registers, instr.rhs);
                       },
                       [&](Instructions::Equality const &instr) -> void {
                         access(registers, instr.lhs) = (access(registers, instr.lhs)
                                                         == read_parameter(registers, instr.rhs));
                       },
               },
               instr);
    return registers;
  }

  auto run(std::span<Instruction const> program, std::span<int const> input) -> Registers {
    return AoC::accumulate(program, Registers{},
                           [it = input.begin()](Registers registers, Instruction instr) mutable {
                             return execute(registers, instr, it);
                           });
  }

  auto digitize(std::size_t number) -> std::vector<int> {
    std::vector<int> digits;
    std::ranges::transform(fmt::format("{}", number), std::back_inserter(digits),
                           [](char c) { return c - '0'; });
    return digits;
  }

  auto as_number(std::span<int const> digits) -> std::size_t {
    return AoC::accumulate(digits, 0ul,
                           [](std::size_t acc, int digit) { return 10 * acc + digit; });
  }

  auto brute_force_solution(bool reverse, auto &&function) -> std::size_t {
    std::array domain{1, 2, 3, 4, 5, 6, 7, 8, 9};
    if (reverse)
      std::ranges::reverse(domain);
    auto solution = [&] {
      for (auto const &[i, digits] :
           cor3ntin::rangesnext::enumerate(Day24::generate_model_numbers<14>(domain))) {
        if (i % 10000000 == 0)
          fmt::print("{}\n", Day24::as_number(digits));
        if (function(digits) == 0)
          return digits;
      }
      throw std::runtime_error{"no valid model number found"};
    }();
    return Day24::as_number(solution);
  }

  auto operator_symbol(Instructions::Addition const &) -> std::string_view { return " += "; }
  auto operator_symbol(Instructions::Multiplication const &) -> std::string_view { return " *= "; }
  auto operator_symbol(Instructions::Division const &) -> std::string_view { return " /= "; }
  auto operator_symbol(Instructions::Modulo const &) -> std::string_view { return " %= "; }

  auto decompile_instruction(std::ostream &os, Instruction const &instruction) -> std::ostream & {
    auto access = [](std::ostream &os, Register reg) {
      return fmt::print(os, "registers[{}]", reg);
    };
    auto read_parameter = [access](std::ostream &os, Parameter const &param) {
      std::visit(AoC::overload{[&os, access](Register reg) { access(os, reg); },
                               [&os](int literal) { os << literal; }},
                 param);
    };
    os << "    ";
    std::visit(AoC::overload{[&](Instructions::Input const &instr) {
                               access(os, instr.reg);
                               os << " = *(input_it++);\n";
                             },
                             [&](Instructions::Equality const &instr) {
                               access(os, instr.lhs);
                               os << " = (";
                               access(os, instr.lhs);
                               os << " == ";
                               read_parameter(os, instr.rhs);
                               os << ");\n";
                             },
                             [&](auto const &instr) {
                               access(os, instr.lhs);
                               os << operator_symbol(instr);
                               read_parameter(os, instr.rhs);
                               os << ";\n";
                             }},
               instruction);
    return os;
  }

  auto decompile(std::ostream &os, std::span<Instruction const> program) -> std::ostream & {
    os << R"(#pragma once
#include <array>
#include <iterator>

namespace Day24 {

  constexpr auto compute_decompiled(std::input_iterator auto input_it) -> std::array<int, 4> {
    std::array<int, 4> registers{};
)";
    AoC::accumulate(program, std::ref(os), &decompile_instruction);
    return os << R"(    return registers;
  }

}
)";
  }

}// namespace Day24

namespace std {

  std::istream &operator>>(std::istream &is, Day24::Instruction &instruction) {
    std::string mnemonic;
    if (is >> mnemonic) {
      if (mnemonic == "inp") {
        instruction =
                Day24::Instructions::Input{std::get<Day24::Register>(Day24::read_parameter(is))};
      } else if (mnemonic == "add") {
        instruction = Day24::Instructions::Addition{
                std::get<Day24::Register>(Day24::read_parameter(is)), Day24::read_parameter(is)};
      } else if (mnemonic == "mul") {
        instruction = Day24::Instructions::Multiplication{
                std::get<Day24::Register>(Day24::read_parameter(is)), Day24::read_parameter(is)};
      } else if (mnemonic == "div") {
        instruction = Day24::Instructions::Division{
                std::get<Day24::Register>(Day24::read_parameter(is)), Day24::read_parameter(is)};
      } else if (mnemonic == "mod") {
        instruction = Day24::Instructions::Modulo{
                std::get<Day24::Register>(Day24::read_parameter(is)), Day24::read_parameter(is)};
      } else if (mnemonic == "eql") {
        instruction = Day24::Instructions::Equality{
                std::get<Day24::Register>(Day24::read_parameter(is)), Day24::read_parameter(is)};
      } else {
        throw std::runtime_error{"invalid opcode mnemonic"};
      }
    }
    return is;
  }

}// namespace std

namespace AoC {

  Solution<24>::Solution(std::istream &stream)
      : mode{Day24::ComputeMode::Precomputed}
      , program{AoC::parse_vec<Day24::Instruction>(stream)} {
    std::ofstream file{"day24/compute_decompiled.h"};
    Day24::decompile(file, program);
  }

  auto Solution<24>::compute(std::span<int const> input) const -> int {
    switch (mode) {
      case Day24::ComputeMode::Precomputed:
        throw std::runtime_error{"Precomputed mode selected"};
      case Day24::ComputeMode::BruteForceEmulation:
        return Day24::run(program, input)[3];
      case Day24::ComputeMode::BruteForceDecompiled:
        return Day24::compute_decompiled(input.begin())[3];
      case Day24::ComputeMode::BruteForceSimplified:
        return Day24::compute_simplified(input.begin());
    }
    throw std::runtime_error{"Unsupported compute mode selected"};
  }

  auto Solution<24>::part1() const -> std::size_t {
    if (mode == Day24::ComputeMode::Precomputed)
      return 99893999291967ul;
    else
      return Day24::brute_force_solution(true, std::bind_front(&Solution<24>::compute, *this));
  }

  auto Solution<24>::part2() const -> std::size_t {
    if (mode == Day24::ComputeMode::Precomputed)
      return 34171911181211ul;
    else
      return Day24::brute_force_solution(false, std::bind_front(&Solution<24>::compute, *this));
  }

}// namespace AoC
