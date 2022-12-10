#pragma once

#include <concepts>
#include <iosfwd>
#include <ranges>
#include <utility>
#include <vector>

#include <cor3ntin/rangesnext/generator.hpp>
#include <cor3ntin/rangesnext/product.hpp>
#include <cor3ntin/rangesnext/to.hpp>
#include <experimental/mdspan>

namespace AoC {

  auto as_string(std::istream &stream) -> std::string;

  template <typename T>
  auto parse_vec(std::istream &stream) -> std::vector<T> {
    using cor3ntin::rangesnext::to;
    return std::ranges::istream_view<T>(stream) | to<std::vector>();
  }

  auto parse_comma_separated_ints_on_line(std::istream &stream) -> std::vector<int>;

  auto lines(std::istream &stream) -> cor3ntin::rangesnext::generator<std::string>;

  using Dyn2DExtents = std::experimental::extents<std::experimental::dynamic_extent,
                                                  std::experimental::dynamic_extent>;

  template <typename T>
  using View2D = std::experimental::mdspan<T, Dyn2DExtents>;

  auto parse_matrix(std::istream &stream) -> std::pair<std::vector<int>, View2D<int const>>;

  auto parse_char_image(std::istream &) -> std::pair<std::vector<char>, View2D<char>>;

  template <typename... Bases>
  struct overload : Bases... {
    using Bases::operator()...;
  };

  template <typename... Bases>
  overload(Bases &&...) -> overload<Bases...>;

  template <typename G>
  struct Y {
    template <typename... X>
    decltype(auto) operator()(X &&...x) const & {
      return std::invoke(g, *this, std::forward<X>(x)...);
    }
    G g;
  };

  template <typename G>
  Y(G) -> Y<G>;

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
    constexpr auto operator<=>(Point const &) const noexcept = default;
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

  constexpr auto all_points(Dyn2DExtents ext) {
    using cor3ntin::rangesnext::product;
    return cor3ntin::rangesnext::product(std::views::iota(0ul, ext.extent(0)),
                                         std::views::iota(0ul, ext.extent(1)))
           | std::views::transform([](auto pair) {
               auto [x, y] = pair;
               return Point{x, y};
             });
  }

  template <std::integral T>
  auto neighboring_points(Point<T> center, Dyn2DExtents ext)
          -> cor3ntin::rangesnext::generator<Point<T>> {
    if (center.x + 1 < ext.extent(0))
      co_yield Point{center.x + 1, center.y};
    if (center.y + 1 < ext.extent(1))
      co_yield Point{center.x, center.y + 1};
    if (center.x > 0)
      co_yield Point{center.x - 1, center.y};
    if (center.y > 0)
      co_yield Point{center.x, center.y - 1};
  }

  template <std::integral T>
  auto surrounding_points(Point<T> center, Dyn2DExtents ext)
          -> cor3ntin::rangesnext::generator<Point<T>> {
    if (center.x + 1 < ext.extent(0))
      co_yield Point{center.x + 1, center.y};
    if (center.x + 1 < ext.extent(0) && center.y + 1 < ext.extent(1))
      co_yield Point{center.x + 1, center.y + 1};
    if (center.y + 1 < ext.extent(1))
      co_yield Point{center.x, center.y + 1};
    if (center.x > 0 && center.y + 1 < ext.extent(1))
      co_yield Point{center.x - 1, center.y + 1};
    if (center.x > 0)
      co_yield Point{center.x - 1, center.y};
    if (center.x > 0 && center.y > 0)
      co_yield Point{center.x - 1, center.y - 1};
    if (center.y > 0)
      co_yield Point{center.x, center.y - 1};
    if (center.x + 1 < ext.extent(0) && center.y > 0)
      co_yield Point{center.x + 1, center.y - 1};
  }

  template <std::integral T>
  auto nearby_points(Point<T> center, Dyn2DExtents ext)
          -> cor3ntin::rangesnext::generator<Point<T>> {
    co_yield center;
    for (auto q : surrounding_points(center, ext))
      co_yield q;
  }

  template <std::size_t N, typename R>
  auto chunks(R &&rng) -> cor3ntin::rangesnext::generator<
          std::array<typename std::remove_reference_t<R>::value_type, N>>
  requires std::ranges::input_range<std::remove_reference_t<R>> {
    std::array<typename std::remove_reference_t<R>::value_type, N> chunk;
    std::ranges::subrange rest{rng};
    while (rest.size() >= N) {
      std::ranges::copy_n(rest.begin(), N, chunk.begin());
      rest.advance(N);
      co_yield chunk;
    }
  }

  template <std::size_t N, typename InputIt>
  auto chunks(InputIt &&it) -> cor3ntin::rangesnext::generator<std::array<
          typename std::iterator_traits<std::remove_reference_t<InputIt>>::value_type, N>>
  requires std::input_iterator<std::remove_reference_t<InputIt>> {
    std::array<typename std::iterator_traits<std::remove_reference_t<InputIt>>::value_type, N>
            chunk;
    while (true) {
      std::ranges::copy_n(it, N, chunk.begin());
      std::advance(it, N);
      co_yield chunk;
    }
  }

  template <typename T, std::ranges::input_range R,
            std::invocable<T, std::ranges::range_value_t<R>> F>
  auto accumulate(R &&rng, T &&init, F &&f) -> std::remove_reference_t<T> {
    auto common = rng | std::views::common;
    return std::accumulate(common.begin(), common.end(), std::forward<T>(init), std::forward<F>(f));
  }

  template <std::ranges::input_range Rng>
  auto pairs(Rng &&rng) -> cor3ntin::rangesnext::generator<
          std::tuple<std::ranges::range_reference_t<Rng>, std::ranges::range_reference_t<Rng>>> {
    auto end = rng.end();
    for (auto lhs_it = rng.begin(); lhs_it != end; ++lhs_it)
      for (auto rhs_it = lhs_it + 1; rhs_it != end; ++rhs_it)
        co_yield std::tie(*lhs_it, *rhs_it);
  }


}// namespace AoC
