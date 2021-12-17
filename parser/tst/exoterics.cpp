#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/str.hpp"

#include <vector>

using namespace m4c0::parser;

///////////////////////////////////////////////////////////////////////////////
// Exoteric usages
///////////////////////////////////////////////////////////////////////////////

// ---------------------------------------
// Using custom classes instead of lambdas
// ---------------------------------------
class parser_cls {
  int m_r;

public:
  constexpr explicit parser_cls(int r) noexcept : m_r(r) {
  }
  // Let's sprinkle a forward-declaration
  constexpr result<int> operator()(input_t rem) const noexcept;
};

static constexpr const auto parser_multi_cls = parser_cls { 0 } & parser_cls { 1 };

constexpr result<int> parser_cls::operator()(input_t rem) const noexcept {
  return result { success { m_r }, rem };
}

static_assert(parser_multi_cls("yeah") == m4c0::parser::result { m4c0::parser::success { 1 }, "yeah" });
static_assert(skip(parser_cls { 0 })(""));

// ---------------------------------------
// Using non-trivial classes as result
// ---------------------------------------
class non_trivial {
  int m_count = 0;

public:
  constexpr non_trivial() = default;
  constexpr ~non_trivial() { // NOLINT we want a non-trivial destructor
    m_count = 0;
  }

  non_trivial(const non_trivial &) = delete;
  non_trivial & operator=(const non_trivial &) = delete;

  constexpr non_trivial(non_trivial && o) noexcept : m_count(o.m_count) {
    o.m_count = 0;
  }
  constexpr non_trivial & operator=(non_trivial && o) noexcept {
    m_count = o.m_count;
    o.m_count = 0;
    return *this;
  }

  constexpr auto operator+(char /*c*/) noexcept {
    m_count++;
    return std::move(*this);
  }
  constexpr auto operator+(non_trivial c) noexcept {
    m_count += c.m_count;
    return std::move(*this);
  }

  [[nodiscard]] constexpr int count() const noexcept {
    return m_count;
  }
};
static constexpr auto operator+(char c, non_trivial n) noexcept {
  return n + c;
}
static constexpr const auto non_trivial_p = producer_of<non_trivial>();
static constexpr const auto passthru = [](auto in) {
  return std::move(in);
};
static_assert((non_trivial_p << any_char())("yeah")->count() == 4);
static_assert((non_trivial_p << (any_char() + non_trivial_p))("yeah")->count() == 4);
static constexpr const auto parser_non_trivial = (producer_of<non_trivial>() | producer_of<non_trivial>() & passthru)
                                              << (any_char() + producer_of<non_trivial>() + skip(any_char()));
static_assert(parser_non_trivial("yeah")->count() == 2);
