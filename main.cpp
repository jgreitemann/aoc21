#include <iostream>
#include <cpr/cpr.h>

#include "day00/solution.h"

int main() {
  std::string session{std::getenv("SESSION")};
  cpr::Response r = cpr::Get(cpr::Url{"https://adventofcode.com/2020/day/18/input"},
                             cpr::Cookies{{"session", std::move(session)}});
  std::cout << r.text << '\n';
  std::cout << r.status_code << '\n';
  std::cout << Day00::foo() << '\n';
}
