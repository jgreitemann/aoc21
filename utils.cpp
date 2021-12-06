#include "utils.h"

#include <iostream>
#include <iterator>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string {
    return {std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};
  }

  auto lines(std::istream &stream) -> cor3ntin::rangesnext::generator<std::string> {
    std::string line;
    while (std::getline(stream, line))
      co_yield std::move(line);
  }

}// namespace AoC
