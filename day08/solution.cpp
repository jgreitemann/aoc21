#include "solution.h"
#include "../utils.h"

#include <algorithm>
#include <numeric>
#include <ranges>

namespace Day08 {

  std::istream &operator>>(std::istream &stream, Entry &e) {
    std::copy_n(std::istream_iterator<std::string>(stream), 10, e.patterns.begin());
    std::string pipe;
    stream >> pipe;
    std::copy_n(std::istream_iterator<std::string>(stream), 4, e.output_digits.begin());
    std::ranges::for_each(e.patterns, std::ranges::sort);
    std::ranges::for_each(e.output_digits, std::ranges::sort);
    return stream;
  }

  auto number_of_unique_output_digits(Entry const &e) -> std::size_t {
    constexpr std::array unique_digits_segment_counts = {2ul, 4ul, 3ul, 7ul};
    return std::ranges::count_if(e.output_digits, [=](std::string const &d) {
      return std::ranges::any_of(unique_digits_segment_counts,
                                 [len = d.size()](std::size_t n) { return n == len; });
    });
  }

}// namespace Day08

namespace AoC {

  Solution<8>::Solution(std::istream &stream)
      : entries{AoC::parse_vec<Day08::Entry>(stream)} {}

  auto Solution<8>::part1() const -> std::size_t {
    auto counts = entries | std::views::transform(Day08::number_of_unique_output_digits);
    return std::accumulate(counts.begin(), counts.end(), 0ul);
  }

}// namespace AoC
