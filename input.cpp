#include "input.h"
#include <cpr/cpr.h>
#include <fmt/core.h>

#include <filesystem>

namespace AoC {

  namespace {

    static const auto session =
            std::string{std::getenv("SESSION")};

    auto input_tmp_path(int day) -> std::filesystem::path
    {
      return std::filesystem::temp_directory_path() / fmt::format("aoc21-day{:02}.txt", day);
    }

    auto download_input(int day) -> std::string
    {
      cpr::Response r = cpr::Get(cpr::Url{fmt::format("https://adventofcode.com/2020/day/{}/input", day)},
                                 cpr::Cookies{{"session", session}});
      if (r.status_code == 200) {
        return r.text;
      } else {
        throw std::runtime_error{fmt::format("Failed to download puzzle input: Status {}", r.status_code)};
      }
    }
  }

  auto input_stream(int day) -> std::ifstream
  {
    auto path = input_tmp_path(day);

    if (!std::filesystem::is_regular_file(path)) {
      std::ofstream os{path};
      os << download_input(day);
    }

    return std::ifstream{path};
  }

}
