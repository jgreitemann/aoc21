#include "solution.h"

#include <fmt/format.h>

#include <cor3ntin/rangesnext/enumerate.hpp>

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
      : program{AoC::parse_vec<Day24::Instruction>(stream)} {}

  auto Solution<24>::part1() const -> std::size_t {
    auto solution = [&] {
      for (auto const &[i, digits] :
           cor3ntin::rangesnext::enumerate(Day24::generate_model_numbers<14>())) {
        if (Day24::run(program, digits)[3] == 0)
          return digits;
      }
      return std::array<int, 14>{};
      throw std::runtime_error{"no valid model number found"};
    }();
    return Day24::as_number(solution);
  }

}// namespace AoC
