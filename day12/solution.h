#pragma once

#include "../solution.h"
#include "../utils.h"

#include <string>
#include <unordered_map>
#include <utility>

namespace Day12 {

  using GraphEdge = std::pair<std::string, std::string>;
  using Graph = std::unordered_multimap<std::string, std::string>;

  auto parse(std::istream &stream) -> Graph;
  auto directed_graph(Graph const &graph) -> Graph;
  auto traversals(Graph const &graph, bool has_freebie)
          -> cor3ntin::rangesnext::generator<std::vector<std::string_view>>;
  auto number_of_traversals(Graph const &graph, bool has_freebie) -> std::size_t;

}// namespace Day12

namespace AoC {

  template <>
  struct Solution<12> {
    explicit Solution(std::istream &);
    auto part1() const -> std::size_t;
    auto part2() const -> std::size_t;

  private:
    Day12::Graph graph;
  };

}// namespace AoC
