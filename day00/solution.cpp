#include "solution.h"

namespace Day00 {

  auto count_characters(std::string_view str) -> std::size_t {
    return str.size();
  }

}// namespace Day00

namespace AoC {

  auto Solution<0>::part1(std::istream &stream) -> std::size_t {
    return Day00::count_characters(AoC::as_string(stream));
  }

}// namespace AoC
