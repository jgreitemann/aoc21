#include <iostream>
#include <cpr/cpr.h>

int main() {
  std::ifstream session_stream{".session"};
  std::string session{std::istreambuf_iterator<char>{session_stream}, std::istreambuf_iterator<char>{}};
  std::cout << session << '\n';
  cpr::Response r = cpr::Get(cpr::Url{"https://adventofcode.com/2020/day/18/input"},
                             cpr::Cookies{{"session", std::move(session)}});
  std::cout << r.text << '\n';
  std::cout << r.status_code << '\n';
}
