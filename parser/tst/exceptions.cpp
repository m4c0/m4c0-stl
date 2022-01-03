#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"
#include "m4c0/parser/traits.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <type_traits>

using namespace m4c0::parser;

struct example_exception : std::exception {};

// This tests two things at once: in constexpr, it makes sure we have "noexcept" in our parsers, while in runtime it
// confirms we can catch an exception thrown by our parser.
//
// Such technique can be used to short-circuit semantic errors
template<typename P>
static void assert_throws(const std::string & test_name, P && p) {
  try {
    std::cerr << "Test [" << test_name << "] ";
    p("");
    throw std::runtime_error(test_name);
  } catch (const example_exception & /**/) {
    std::cerr << "passed\n";
  }
}

template<typename In, typename Out>
static constexpr const auto thrower = [](In /**/) -> Out {
  throw example_exception {};
};
static constexpr const auto thrower_plus = [](auto, auto) -> int {
  throw example_exception {};
};
static constexpr const auto thrower_p = thrower<input_t, result<int>>;

static constexpr const auto ok = eof();
int main() {
  try {
    assert_throws("ok & mapper", ok & thrower<nil, int>);
    assert_throws("ok & parser", ok & thrower_p);
    assert_throws("ok && bool", ok && thrower<nil, bool>);
    assert_throws("combine(fail, ok, ok)", combine(thrower_p, ok, std::plus<>()));
    assert_throws("combine(ok, fail, ok)", combine(ok, thrower_p, std::plus<>()));
    assert_throws("combine(ok, ok,fail)", combine(ok, ok, thrower_plus));
  } catch (const std::runtime_error & err) {
    std::cerr << "failed\n";
  }
}
