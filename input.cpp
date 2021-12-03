#include "input.h"

#include <fmt/core.h>
#include <httplib.h>

#include <filesystem>

namespace AoC {

  namespace {

    static const auto session =
            std::string{std::getenv("SESSION")};

    auto input_tmp_path(int day) -> std::filesystem::path {
      return std::filesystem::temp_directory_path() / fmt::format("aoc21-day{:02}.txt", day);
    }

    auto download_input(int day) -> std::string {
      httplib::Client client{"https://adventofcode.com"};
      client.enable_server_certificate_verification(false);

      httplib::Headers cookie{{"Cookie", fmt::format("session={}", session)}};
      if (auto res = client.Get(fmt::format("/2021/day/{}/input", day).c_str(), cookie)) {
        if (res->status == 200) {
          return res->body;
        } else {
          throw std::runtime_error{fmt::format("Failed to download puzzle input: Status {}", res->status)};
        }
      } else {
        throw std::runtime_error{"Failed to download puzzle input: Error sending GET request."};
      }
    }

  }// namespace

  auto input_stream(int day) -> std::ifstream {
    auto path = input_tmp_path(day);

    if (!std::filesystem::is_regular_file(path)) {
      if (auto downloaded_input = download_input(day); !downloaded_input.empty()) {
        std::ofstream os{path};
        os << download_input(day);
      }
    }

    return std::ifstream{path};
  }

}// namespace AoC
