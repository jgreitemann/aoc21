#pragma once

#include <iosfwd>
#include <ranges>
#include <vector>

#include <cor3ntin/rangesnext/generator.hpp>
#include <cor3ntin/rangesnext/to.hpp>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string;

  template <typename T>
  auto parse_vec(std::istream &stream) -> std::vector<T> {
    using cor3ntin::rangesnext::to;
    return std::ranges::istream_view<T>(stream) | to<std::vector>();
  }

  auto parse_comma_separated_ints_on_line(std::istream &stream) -> std::vector<int>;

  auto lines(std::istream &stream) -> cor3ntin::rangesnext::generator<std::string>;

  template <typename... Bases>
  struct overload : Bases... {
    using Bases::operator()...;
  };

  template <typename... Bases>
  overload(Bases &&...) -> overload<Bases...>;

  template <typename T>
  struct Point {
    T x, y;
    constexpr Point &operator+=(Point p) {
      x += p.x;
      y += p.y;
      return *this;
    }
    constexpr Point &operator-=(Point p) {
      x -= p.x;
      y -= p.y;
      return *this;
    }
    constexpr Point &operator*=(T s) {
      x *= s;
      y *= s;
      return *this;
    }
    constexpr Point &operator*=(Point p) {
      x *= p.x;
      y *= p.y;
      return *this;
    }
    constexpr Point &operator/=(T s) {
      x /= s;
      y /= s;
      return *this;
    }
    constexpr Point &operator/=(Point p) {
      x /= p.x;
      y /= p.y;
      return *this;
    }
    constexpr bool operator==(Point const &) const noexcept = default;
    [[nodiscard]] constexpr Point abs() const { return {std::abs(x), std::abs(y)}; }
    [[nodiscard]] constexpr int norm1() const { return std::max(std::abs(x), std::abs(y)); }
  };

  template <typename T>
  constexpr Point<T> operator+(Point<T> lhs, Point<T> rhs) {
    return lhs += rhs;
  }
  template <typename T>
  constexpr Point<T> operator-(Point<T> lhs, Point<T> rhs) {
    return lhs -= rhs;
  }
  template <typename T>
  constexpr Point<T> operator*(Point<T> lhs, int rhs) {
    return lhs *= rhs;
  }
  template <typename T>
  constexpr Point<T> operator*(int lhs, Point<T> rhs) {
    return rhs *= lhs;
  }
  template <typename T>
  constexpr Point<T> operator*(Point<T> lhs, Point<T> rhs) {
    return lhs *= rhs;
  }
  template <typename T>
  constexpr Point<T> operator/(Point<T> lhs, int rhs) {
    return lhs /= rhs;
  }
  template <typename T>
  constexpr Point<T> operator/(int lhs, Point<T> rhs) {
    return rhs /= lhs;
  }
  template <typename T>
  constexpr Point<T> operator/(Point<T> lhs, Point<T> rhs) {
    return rhs /= lhs;
  }

}// namespace AoC
