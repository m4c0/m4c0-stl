#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

static_assert(success('X', "B") == success('X', "B"));
static_assert(success('X', "B") != success('O', "B"));
static_assert(success('X', "B") != success('X', "_"));

static_assert(failure<char>("failure") == failure<char>("failure"));
static_assert(failure<char>("other failure") != failure<char>("failure"));

static_assert(result<int>(failure<char>("test")) == failure<>("test"));

static constexpr result<char> polymorphic(bool b) {
  return b ? result { success('!', "") } : result { failure<char>("failed") };
}
static_assert(polymorphic(true) == polymorphic(true));
static_assert(polymorphic(false) == polymorphic(false));
static_assert(polymorphic(true) != polymorphic(false));

static constexpr int to_int(char c) {
  return c == '!' ? 1 : 0;
}
static_assert(!polymorphic(false).fmap(to_int));
static_assert(polymorphic(true).fmap(to_int) == success(1, ""));

static_assert((polymorphic(true) | success { '@', "a" }) == success('!', ""));
static_assert((polymorphic(false) | success { '@', "a" }) == success('@', "a"));

static_assert((polymorphic(true) & success { '@', "a" }) == success('@', "a"));
static_assert(!(polymorphic(false) & success { '@', "a" }));

int main() {
}
