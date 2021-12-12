#include "solution.h"

#include <algorithm>
#include <numeric>

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

  auto edges(Graph const &graph, std::string const &vtx)
          -> std::ranges::subrange<Graph::const_iterator> {
    auto [begin, end] = graph.equal_range(vtx);
    return {begin, end};
  }

  bool is_upper(std::string_view vtx) { return vtx.front() >= 'A' && vtx.front() <= 'Z'; }

  auto traversals_impl(Graph const &graph, std::vector<std::string_view> &path)
          -> cor3ntin::rangesnext::generator<std::vector<std::string_view>> {
    for (auto const &to : edges(graph, std::string{path.back()}) | std::views::values
                                  | std::views::filter([&path](auto const &to) {
                                      return is_upper(to)
                                             || std::ranges::find(path, to) == path.end();
                                    })) {
      path.push_back(to);
      if (to == "end") {
        co_yield path;
      } else {
        for (auto &&traversal : traversals_impl(graph, path)) {
          co_yield traversal;
        }
      }
      path.pop_back();
    }
  }

  auto traversals(Graph const &graph)
          -> cor3ntin::rangesnext::generator<std::vector<std::string_view>> {
    std::vector<std::string_view> path{"start"};
    Graph directed_copy = graph;
    std::ranges::transform(graph, std::inserter(directed_copy, directed_copy.end()),
                           [](auto const &pair) {
                             return std::pair{pair.second, pair.first};
                           });
    for (auto &&traversal : traversals_impl(directed_copy, path))
      co_yield traversal;
  }

  auto number_of_traversals(Graph const &graph) -> std::size_t {
    return std::ranges::distance(traversals(graph));
  }

}// namespace Day12

namespace AoC {

  Solution<12>::Solution(std::istream &stream)
      : graph{Day12::parse(stream)} {}

  auto Solution<12>::part1() const -> std::size_t { return Day12::number_of_traversals(graph); }

}// namespace AoC
