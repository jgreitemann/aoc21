#include "solution.h"

#include <fmt/core.h>

namespace Day18 {

  auto magnitude(std::string_view number) -> std::size_t {
    return AoC::accumulate(number, std::pair{0ul, 1ul},
                           [](auto pair, char c) {
                             auto [mag, factor] = pair;
                             switch (c) {
                               case '[':
                                 return std::pair{mag, factor * 3};
                               case ',':
                                 return std::pair{mag, factor / 3 * 2};
                               case ']':
                                 return std::pair{mag, factor / 2};
                               default:
                                 return std::pair{mag + factor * (c - '0'), factor};
                             }
                           })
            .first;
  }

  auto try_explode(std::string &number) -> bool {
    if (auto match = std::ranges::find_if(number,
                                          [brackets = 0ul](char c) mutable {
                                            if (c == '[')
                                              ++brackets;
                                            if (c == ']')
                                              --brackets;
                                            return brackets == 5;
                                          });
        match != number.end()) {
      auto const match_pos = match - number.begin();
      auto const match_comma_pos = number.find(',', match_pos);
      auto const match_end_pos = number.find(']', match_pos) + 1;
      auto const match_size = match_end_pos - match_pos;
      int const left_match_num =
              std::stoi(number.substr(match_pos + 1, match_comma_pos - match_pos - 1));
      int const right_match_num =
              std::stoi(number.substr(match_comma_pos + 1, match_end_pos - match_comma_pos - 1));

      if (auto right_begin_pos = number.find_first_not_of("[,]", match_end_pos);
          right_begin_pos != std::string::npos) {
        auto const right_end_pos = number.find_first_of("[,]", right_begin_pos);
        number.replace(right_begin_pos, right_end_pos - right_begin_pos,
                       std::to_string(std::stoi(number.substr(right_begin_pos,
                                                              right_end_pos - right_begin_pos))
                                      + right_match_num));
      }

      number.replace(match_pos, match_size, "0");

      if (auto left_end_pos = number.find_last_not_of("[,]", match_pos - 1);
          left_end_pos != std::string::npos) {
        auto const left_begin_pos = number.find_last_of("[,]", left_end_pos) + 1;
        left_end_pos += 1;
        number.replace(left_begin_pos, left_end_pos - left_begin_pos,
                       std::to_string(std::stoi(number.substr(left_begin_pos,
                                                              left_end_pos - left_begin_pos))
                                      + left_match_num));
      }

      return true;
    } else {
      return false;
    }
  }

  auto try_split(std::string &number) -> bool {
    auto [match_begin, match_size] = [&] {
      for (auto i = number.find_first_not_of("[,]"); i != std::string::npos;
           i = number.find_first_not_of("[,]", i + 1)) {
        if (auto j = number.find_first_of("[,]", i); j != std::string::npos) {
          if (j - i > 1)
            return std::pair{i, j - i};
        } else {
          if (number.size() - i > 1)
            return std::pair{i, number.size() - i};
          else
            break;
        }
      }
      return std::pair{std::string::npos, 0ul};
    }();

    if (match_begin != std::string::npos) {
      int val = std::stoi(number.substr(match_begin, match_size));
      number.replace(
              match_begin, match_size,
              fmt::format("[{},{}]", std::to_string(val / 2), std::to_string((val + 1) / 2)));
      return true;
    } else {
      return false;
    }
  }

  void reduce(std::string &number) {
    while (try_explode(number) || try_split(number))
      ;
  }

  auto add(std::string_view lhs, std::string_view rhs) -> std::string {
    auto result = fmt::format("[{},{}]", lhs, rhs);
    reduce(result);
    return result;
  }

}// namespace Day18

namespace AoC {

  Solution<18>::Solution(std::istream &stream)
      : summands{AoC::lines(stream) | cor3ntin::rangesnext::to<std::vector>()} {}

  auto Solution<18>::part1() const -> std::size_t {
    return Day18::magnitude(Day18::add_all(summands));
  }

  auto Solution<18>::part2() const -> std::size_t {
    return Day18::largest_magnitude_for_single_addition(summands);
  }

}// namespace AoC
