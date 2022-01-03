#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <string_view>

using namespace Day25;

constexpr std::string_view EXAMPLE_DATA = "v...>>.vv>"
                                          ".vv>>.vv.."
                                          ">>.>v>...v"
                                          ">>v>>.>.v."
                                          "v>v.vv.v.."
                                          ">.>>..v..."
                                          ".vv..>.>v."
                                          "v.v..>>v.v"
                                          "....v..v.>";

constexpr MapConstView EXAMPLE_MAP{EXAMPLE_DATA.data(), AoC::Dyn2DExtents{9, 10}};

constexpr std::array<std::pair<std::size_t, std::string_view>, 14> EXAMPLE_MULTI_STEP_RESULTS = {
        std::pair{1, "....>.>v.>"
                     "v.v>.>v.v."
                     ">v>>..>v.."
                     ">>v>v>.>.v"
                     ".>v.v...v."
                     "v>>.>vvv.."
                     "..v...>>.."
                     "vv...>>vv."
                     ">.v.v..v.v"},
        std::pair{2, ">.v.v>>..v"
                     "v.v.>>vv.."
                     ">v>.>.>.v."
                     ">>v>v.>v>."
                     ".>..v....v"
                     ".>v>>.v.v."
                     "v....v>v>."
                     ".vv..>>v.."
                     "v>.....vv."},
        std::pair{3, "v>v.v>.>v."
                     "v...>>.v.v"
                     ">vv>.>v>.."
                     ">>v>v.>.v>"
                     "..>....v.."
                     ".>.>v>v..v"
                     "..v..v>vv>"
                     "v.v..>>v.."
                     ".v>....v.."},
        std::pair{4, "v>..v.>>.."
                     "v.v.>.>.v."
                     ">vv.>>.v>v"
                     ">>.>..v>.>"
                     "..v>v...v."
                     "..>>.>vv.."
                     ">.v.vv>v.v"
                     ".....>>vv."
                     "vvv>...v.."},
        std::pair{5, "vv>...>v>."
                     "v.v.v>.>v."
                     ">.v.>.>.>v"
                     ">v>.>..v>>"
                     "..v>v.v..."
                     "..>.>>vvv."
                     ".>...v>v.."
                     "..v.v>>v.v"
                     "v.v.>...v."},
        std::pair{10, "..>..>>vv."
                      "v.....>>.v"
                      "..v.v>>>v>"
                      "v>.>v.>>>."
                      "..v>v.vv.v"
                      ".v.>>>.v.."
                      "v.v..>v>.."
                      "..v...>v.>"
                      ".vv..v>vv."},
        std::pair{20, "v>.....>>."
                      ">vv>.....v"
                      ".>v>v.vv>>"
                      "v>>>v.>v.>"
                      "....vv>v.."
                      ".v.>>>vvv."
                      "..v..>>vv."
                      "v.v...>>.v"
                      "..v.....v>"},
        std::pair{30, ".vv.v..>>>"
                      "v>...v...>"
                      ">.v>.>vv.>"
                      ">v>.>.>v.>"
                      ".>..v.vv.."
                      "..v>..>>v."
                      "....v>..>v"
                      "v.v...>vv>"
                      "v.v...>vvv"},
        std::pair{40, ">>v>v..v.."
                      "..>>v..vv."
                      "..>>>v.>.v"
                      "..>>>>vvv>"
                      "v.....>..."
                      "v.v...>v>>"
                      ">vv.....v>"
                      ".>v...v.>v"
                      "vvv.v..v.>"},
        std::pair{50, "..>>v>vv.v"
                      "..v.>>vv.."
                      "v.>>v>>v.."
                      "..>>>>>vv."
                      "vvv....>vv"
                      "..v....>>>"
                      "v>.......>"
                      ".vv>....v>"
                      ".>v.vv.v.."},
        std::pair{55, "..>>v>vv.."
                      "..v.>>vv.."
                      "..>>v>>vv."
                      "..>>>>>vv."
                      "v......>vv"
                      "v>v....>>v"
                      "vvv...>..>"
                      ">vv.....>."
                      ".>v.vv.v.."},
        std::pair{56, "..>>v>vv.."
                      "..v.>>vv.."
                      "..>>v>>vv."
                      "..>>>>>vv."
                      "v......>vv"
                      "v>v....>>v"
                      "vvv....>.>"
                      ">vv......>"
                      ".>v.vv.v.."},
        std::pair{57, "..>>v>vv.."
                      "..v.>>vv.."
                      "..>>v>>vv."
                      "..>>>>>vv."
                      "v......>vv"
                      "v>v....>>v"
                      "vvv.....>>"
                      ">vv......>"
                      ".>v.vv.v.."},
        std::pair{58, "..>>v>vv.."
                      "..v.>>vv.."
                      "..>>v>>vv."
                      "..>>>>>vv."
                      "v......>vv"
                      "v>v....>>v"
                      "vvv.....>>"
                      ">vv......>"
                      ".>v.vv.v.."},
};

static auto single_step(MapConstView input_map) -> std::pair<std::vector<char>, MapConstView> {
  std::vector<char> new_data(input_map.size(), '.');
  MapView new_map{new_data.data(), input_map.extents()};
  step(input_map, new_map);
  return {std::move(new_data), new_map};
}

static auto multi_step(MapConstView input_map, std::size_t num_steps)
        -> std::pair<std::vector<char>, MapConstView> {
  std::vector<char> first_data(input_map.size(), '.');
  MapView first_map{first_data.data(), input_map.extents()};

  std::vector<char> second_data(input_map.size(), '.');
  MapView second_map{second_data.data(), input_map.extents()};

  for (auto p : AoC::all_points(input_map.extents()))
    first_map(p.x, p.y) = input_map(p.x, p.y);

  for (auto _ : std::views::iota(0ul, num_steps / 2)) {
    step(first_map, second_map);
    step(second_map, first_map);
  }

  if (num_steps % 2 == 0) {
    return {std::move(first_data), first_map};
  } else {
    step(first_map, second_map);
    return {std::move(second_data), second_map};
  }
}

TEST(Day25, cucumbers_move_only_into_free_spaces) {
  constexpr std::string_view initial_data = "...>>>>>...";
  MapConstView initial_map{initial_data.data(), AoC::Dyn2DExtents{1, 11}};

  auto [one_step_data, one_step_map] = single_step(initial_map);
  EXPECT_EQ(std::string(one_step_data.begin(), one_step_data.end()), "...>>>>.>..");

  auto [two_steps_data, two_steps_map] = single_step(one_step_map);
  EXPECT_EQ(std::string(two_steps_data.begin(), two_steps_data.end()), "...>>>.>.>.");
}

TEST(Day25, east_facing_herd_moves_first_followed_by_south_facing_herd) {
  constexpr std::string_view initial_data = ".........."
                                            ".>v....v.."
                                            ".......>.."
                                            "..........";
  MapConstView initial_map{initial_data.data(), AoC::Dyn2DExtents{4, 10}};

  auto [one_step_data, one_step_map] = single_step(initial_map);
  EXPECT_EQ(std::string(one_step_data.begin(), one_step_data.end()), ".........."
                                                                     ".>........"
                                                                     "..v....v>."
                                                                     "..........");
}

TEST(Day25, periodic_boundaries) {
  constexpr std::string_view initial_data = "...>..."
                                            "......."
                                            "......>"
                                            "v.....>"
                                            "......>"
                                            "......."
                                            "..vvv..";
  MapConstView initial_map{initial_data.data(), AoC::Dyn2DExtents{7, 7}};

  auto [one_step_data, one_step_map] = single_step(initial_map);
  EXPECT_EQ(std::string(one_step_data.begin(), one_step_data.end()), "..vv>.."
                                                                     "......."
                                                                     ">......"
                                                                     "v.....>"
                                                                     ">......"
                                                                     "......."
                                                                     "....v..");

  auto [two_steps_data, two_steps_map] = single_step(one_step_map);
  EXPECT_EQ(std::string(two_steps_data.begin(), two_steps_data.end()), "....v>."
                                                                       "..vv..."
                                                                       ".>....."
                                                                       "......>"
                                                                       "v>....."
                                                                       "......."
                                                                       ".......");

  auto [three_steps_data, three_steps_map] = single_step(two_steps_map);
  EXPECT_EQ(std::string(three_steps_data.begin(), three_steps_data.end()), "......>"
                                                                           "..v.v.."
                                                                           "..>v..."
                                                                           ">......"
                                                                           "..>...."
                                                                           "v......"
                                                                           ".......");

  auto [four_steps_data, four_steps_map] = single_step(three_steps_map);
  EXPECT_EQ(std::string(four_steps_data.begin(), four_steps_data.end()), ">......"
                                                                         "..v...."
                                                                         "..>.v.."
                                                                         ".>.v..."
                                                                         "...>..."
                                                                         "......."
                                                                         "v......");
}

TEST(Day25, multiple_steps) {
  for (auto &&[num_steps, expected_result] : EXAMPLE_MULTI_STEP_RESULTS) {
    auto [data, map] = multi_step(EXAMPLE_MAP, num_steps);
    EXPECT_EQ(std::string(data.begin(), data.end()), expected_result)
            << "Failure for " << num_steps << " steps.";
  }
}

TEST(Day25, steps_until_converged) {
  EXPECT_EQ(steps_until_converged(EXAMPLE_MAP), 58);
}
