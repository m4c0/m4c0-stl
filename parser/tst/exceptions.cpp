#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"
#include "m4c0/parser/traits.hpp"

#include <exception>
#include <iostream>
#include <type_traits>

using namespace m4c0::parser;

template<typename P>
concept nothrow = std::is_nothrow_invocable_v<P, input_t>;

struct example_exception : std::exception {};

// This tests two things at once: in constexpr, it makes sure we have "noexcept" in our parsers, while in runtime it
// confirms we can catch an exception thrown by our parser.
//
// Such technique can be used to short-circuit semantic errors
template<nothrow P>
static bool test(P && p, input_t in) noexcept {
  try {
    (p & [](type_of_t<P> /**/) -> int {
      throw example_exception {};
    })(in);
    std::cerr << "Parser succeeded without throwing exceptions\n";
    return false;
  } catch (const example_exception & /**/) {
    return true;
  }
}

int main() {
  if (!test(match('.'), ".")) return 1;
  return 0;
}
