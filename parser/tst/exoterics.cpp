#include "m4c0/parser/combiners.hpp"
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
  // FIXME: Currently, this might perform way too many copies
  std::vector<char> m_data {};

public:
  auto operator+(char c) const noexcept {
    return *this;
  }
};
static constexpr const auto const_non_trivial = producer([] {
  return non_trivial {};
});

// Can't destroy as constexpr, so let's make them non-constexpr
static const auto parser_non_trivial = many(any_char(), non_trivial {});
const bool non_trivial_stuff = static_cast<bool>(parser_non_trivial("yeah"));
