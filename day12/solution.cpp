#include "solution.h"

#include <algorithm>
#include <numeric>
#include <utility>

#include <cor3ntin/rangesnext/generator.hpp>

namespace Day12 {

  auto parse(std::istream &stream) -> Graph {
    using cor3ntin::rangesnext::to;
    return AoC::lines(stream) | std::views::transform([](std::string const &line) {
             auto sep = line.find('-');
             return GraphEdge{line.substr(0, sep), line.substr(sep + 1)};
           })
           | to<Graph>();
  }

  auto directed_graph(Graph const &graph) -> Graph {
    Graph directed_copy = graph;
    std::ranges::transform(graph, std::inserter(directed_copy, directed_copy.end()),
                           [](auto const &pair) {
                             return std::pair{pair.second, pair.first};
                           });
    return directed_copy;
  }

  auto edges(Graph const &graph, std::string const &vtx)
          -> std::ranges::subrange<Graph::const_iterator> {
    auto [begin, end] = graph.equal_range(vtx);
    return {begin, end};
  }

  auto cost(std::string_view vtx) -> int {
    if (vtx.front() >= 'A' && vtx.front() <= 'Z')
      return 0;
    else if (vtx == "start" || vtx == "end")
      return std::numeric_limits<int>::max();
    else
      return 1;
  }

  auto traversals_impl(Graph const &graph, std::vector<std::string_view> &path, int budget)
          -> cor3ntin::rangesnext::generator<std::vector<std::string_view>> {
    for (auto const &[to, cost] :
         edges(graph, std::string{path.back()}) | std::views::values
                 | std::views::transform([&path](auto const &to) {
                     return std::pair{std::string_view{to},
                                      (std::ranges::find(path, to) != path.end()) ? cost(to) : 0};
                   })
                 | std::views::filter(
                         [budget](auto const &pair) { return pair.second <= budget; })) {
      path.push_back(to);
      if (to == "end") {
        co_yield path;
      } else {
        for (auto &&traversal : traversals_impl(graph, path, budget - cost)) {
          co_yield traversal;
        }
      }
      path.pop_back();
    }
  }

  auto traversals(Graph const &directed_graph, bool has_freebie)
          -> cor3ntin::rangesnext::generator<std::vector<std::string_view>> {
    std::vector<std::string_view> path{"start"};
    for (auto &&traversal : traversals_impl(directed_graph, path, has_freebie ? 1 : 0))
      co_yield traversal;
  }

  auto number_of_traversals(Graph const &graph, bool has_freebie) -> std::size_t {
    return std::ranges::distance(traversals(graph, has_freebie));
  }

}// namespace Day12

namespace AoC {

  Solution<12>::Solution(std::istream &stream)
      : graph{Day12::directed_graph(Day12::parse(stream))} {}

  auto Solution<12>::part1() const -> std::size_t {
    return Day12::number_of_traversals(graph, false);
  }
  auto Solution<12>::part2() const -> std::size_t {
    return Day12::number_of_traversals(graph, true);
  }

}// namespace AoC
