#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <span>
#include <string_view>

#include <cor3ntin/rangesnext/to.hpp>

using namespace Day12;
using namespace std::string_view_literals;

using ConstexprGraphEdge = std::pair<std::string_view, std::string_view>;

constexpr std::string_view SMALL_EXAMPLE_INPUT = R"(start-A
start-b
A-c
A-b
b-d
A-end
b-end
)";

constexpr std::array SMALL_EXAMPLE_GRAPH = {
        ConstexprGraphEdge{"start", "A"}, ConstexprGraphEdge{"start", "b"},
        ConstexprGraphEdge{"A", "c"},     ConstexprGraphEdge{"A", "b"},
        ConstexprGraphEdge{"b", "d"},     ConstexprGraphEdge{"A", "end"},
        ConstexprGraphEdge{"b", "end"},
};

constexpr std::string_view MEDIUM_EXAMPLE_INPUT = R"(dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc
)";

constexpr std::array MEDIUM_EXAMPLE_GRAPH = {
        ConstexprGraphEdge{"dc", "end"},   ConstexprGraphEdge{"HN", "start"},
        ConstexprGraphEdge{"start", "kj"}, ConstexprGraphEdge{"dc", "start"},
        ConstexprGraphEdge{"dc", "HN"},    ConstexprGraphEdge{"LN", "dc"},
        ConstexprGraphEdge{"HN", "end"},   ConstexprGraphEdge{"kj", "sa"},
        ConstexprGraphEdge{"kj", "HN"},    ConstexprGraphEdge{"kj", "dc"},
};

constexpr std::string_view LARGE_EXAMPLE_INPUT = R"(fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW
)";

constexpr std::array LARGE_EXAMPLE_GRAPH = {
        ConstexprGraphEdge{"fs", "end"}, ConstexprGraphEdge{"he", "DX"},
        ConstexprGraphEdge{"fs", "he"},  ConstexprGraphEdge{"start", "DX"},
        ConstexprGraphEdge{"pj", "DX"},  ConstexprGraphEdge{"end", "zg"},
        ConstexprGraphEdge{"zg", "sl"},  ConstexprGraphEdge{"zg", "pj"},
        ConstexprGraphEdge{"pj", "he"},  ConstexprGraphEdge{"RW", "he"},
        ConstexprGraphEdge{"fs", "DX"},  ConstexprGraphEdge{"pj", "RW"},
        ConstexprGraphEdge{"zg", "RW"},  ConstexprGraphEdge{"start", "pj"},
        ConstexprGraphEdge{"he", "WI"},  ConstexprGraphEdge{"zg", "he"},
        ConstexprGraphEdge{"pj", "fs"},  ConstexprGraphEdge{"start", "RW"},
};

MATCHER_P(IsGraph, graph, "") {
  using ::testing::Contains;
  using ::testing::ExplainMatchResult;
  using ::testing::Pair;
  using ::testing::SizeIs;
  return ExplainMatchResult(SizeIs(graph.size()), arg, result_listener)
         && std::ranges::all_of(graph, [&arg, result_listener](auto const &edge) {
              return ExplainMatchResult(Contains(Pair(edge.first, edge.second)), arg,
                                        result_listener);
            });
}

TEST(Day12, parse_input) {
  auto test = [](std::string_view input, std::span<ConstexprGraphEdge const> graph) {
    std::stringstream stream{std::string{input}};
    EXPECT_THAT(parse(stream), IsGraph(graph));
  };

  test(SMALL_EXAMPLE_INPUT, SMALL_EXAMPLE_GRAPH);
  test(MEDIUM_EXAMPLE_INPUT, MEDIUM_EXAMPLE_GRAPH);
  test(LARGE_EXAMPLE_INPUT, LARGE_EXAMPLE_GRAPH);
}

TEST(Day12, small_example_traversals_without_freebie) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAre;
  using ::testing::UnorderedElementsAre;
  auto graph = directed_graph(Graph{SMALL_EXAMPLE_GRAPH.begin(), SMALL_EXAMPLE_GRAPH.end()});
  EXPECT_THAT(
          traversals(graph, false) | to<std::vector>(),
          UnorderedElementsAre(ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "b"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "b"sv, "A"sv, "end"sv),
                               ElementsAre("start"sv, "b"sv, "end"sv)));
}

TEST(Day12, medium_example_traversals_without_freebie) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAre;
  using ::testing::UnorderedElementsAre;
  auto graph = directed_graph(Graph{MEDIUM_EXAMPLE_GRAPH.begin(), MEDIUM_EXAMPLE_GRAPH.end()});
  EXPECT_THAT(traversals(graph, false) | to<std::vector>(),
              UnorderedElementsAre(
                      ElementsAre("start"sv, "HN"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "dc"sv, "HN"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "dc"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "dc"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "kj"sv, "HN"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "kj"sv, "HN"sv, "dc"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "kj"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "HN"sv, "kj"sv, "dc"sv, "end"sv),
                      ElementsAre("start"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "dc"sv, "HN"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "dc"sv, "end"sv),
                      ElementsAre("start"sv, "dc"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "kj"sv, "HN"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "kj"sv, "HN"sv, "dc"sv, "end"sv),
                      ElementsAre("start"sv, "kj"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "kj"sv, "dc"sv, "HN"sv, "end"sv),
                      ElementsAre("start"sv, "kj"sv, "dc"sv, "end"sv)));
}

TEST(Day12, number_of_traversals_without_freebie) {
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{SMALL_EXAMPLE_GRAPH.begin(), SMALL_EXAMPLE_GRAPH.end()}),
                    false),
            10);
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{MEDIUM_EXAMPLE_GRAPH.begin(), MEDIUM_EXAMPLE_GRAPH.end()}),
                    false),
            19);
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{LARGE_EXAMPLE_GRAPH.begin(), LARGE_EXAMPLE_GRAPH.end()}),
                    false),
            226);
}

TEST(Day12, small_example_traversals_with_freebie) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAre;
  using ::testing::UnorderedElementsAre;
  auto graph = directed_graph(Graph{SMALL_EXAMPLE_GRAPH.begin(), SMALL_EXAMPLE_GRAPH.end()});
  EXPECT_THAT(
          traversals(graph, true) | to<std::vector>(),
          UnorderedElementsAre(
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "d"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "d"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "d"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "d"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "d"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "c"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "c"sv, "A"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "c"sv, "A"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "c"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "d"sv, "b"sv, "A"sv, "c"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "d"sv, "b"sv, "A"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "d"sv, "b"sv, "end"sv),
                  ElementsAre("start"sv, "b"sv, "end"sv)));
}

TEST(Day12, number_of_traversals_with_freebie) {
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{SMALL_EXAMPLE_GRAPH.begin(), SMALL_EXAMPLE_GRAPH.end()}),
                    true),
            36);
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{MEDIUM_EXAMPLE_GRAPH.begin(), MEDIUM_EXAMPLE_GRAPH.end()}),
                    true),
            103);
  EXPECT_EQ(number_of_traversals(
                    directed_graph(Graph{LARGE_EXAMPLE_GRAPH.begin(), LARGE_EXAMPLE_GRAPH.end()}),
                    true),
            3509);
}
