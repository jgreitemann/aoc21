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

  void solve(std::array<std::string, 10> &patterns) {
    using namespace std::ranges;
    sort(patterns, std::less<>{}, std::mem_fn(&std::string::size));

    char a, f, g, d;
    set_difference(patterns[1], patterns[0], &a);

    partition(subrange{patterns.begin() + 6, patterns.begin() + 9},
              [&s1 = patterns[0]](std::string const &s) { return !includes(s, s1); });

    set_intersection(patterns[0], patterns[6], &f);

    char c = *find_if_not(patterns[0], [f](char x) { return x == f; });

    std::array<char, 2> bd;
    set_difference(patterns[2], patterns[0], bd.begin());

    std::array<char, 4> bdaf = {bd[0], bd[1], a, f};
    sort(bdaf);

    partition(subrange{patterns.begin() + 3, patterns.begin() + 6},
              [bd](std::string const &s) { return includes(s, bd); });

    set_difference(patterns[3], bdaf, &g);

    std::array acfg{a, c, f, g};
    sort(acfg);
    partition(subrange{patterns.begin() + 4, patterns.begin() + 6},
              [acfg](std::string const &s) { return includes(s, acfg); });

    set_difference(patterns[4], acfg, &d);

    partition(subrange{patterns.begin() + 7, patterns.begin() + 9},
              [d](std::string const &s) { return includes(s, std::views::single(d)); });

    std::swap(patterns[8], patterns[9]);
    std::swap(patterns[0], patterns[1]);
    std::swap(patterns[0], patterns[7]);
    std::swap(patterns[0], patterns[9]);
    std::swap(patterns[2], patterns[4]);
    std::swap(patterns[2], patterns[5]);
    std::swap(patterns[3], patterns[5]);
  }

  auto Entry::output() const -> std::size_t {
    auto get_digit = [this](std::string const &s) -> std::size_t {
      return std::distance(patterns.begin(), std::ranges::find(patterns, s));
    };

    return std::accumulate(
            output_digits.begin(), output_digits.end(), 0ul,
            [&](std::size_t acc, std::string const &s) { return acc * 10 + get_digit(s); });
  }

}// namespace Day08

namespace AoC {

  Solution<8>::Solution(std::istream &stream)
      : entries{AoC::parse_vec<Day08::Entry>(stream)} {}

  auto Solution<8>::part1() const -> std::size_t {
    auto counts = entries | std::views::transform(Day08::number_of_unique_output_digits);
    return std::accumulate(counts.begin(), counts.end(), 0ul);
  }

  auto Solution<8>::part2() const -> std::size_t {
    auto local_entries = entries;
    std::ranges::for_each(local_entries | std::views::transform(&Day08::Entry::patterns),
                          Day08::solve);

    auto outputs = local_entries | std::views::transform(std::mem_fn(&Day08::Entry::output))
                   | std::views::common;
    return std::accumulate(outputs.begin(), outputs.end(), 0ul);
  }

}// namespace AoC
