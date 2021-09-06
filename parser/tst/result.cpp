#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

static_assert(success('X', "B") == success('X', "B"));
static_assert(success('X', "B") != success('O', "B"));
static_assert(success('X', "B") != success('X', "_"));

static_assert(failure<char>("failure") == failure<char>("failure"));
static_assert(failure<char>("other failure") != failure<char>("failure"));

static constexpr result<char> polymorphic(bool b) {
  return b ? result { success('!', "") } : result { failure<char>("failed") };
}
static_assert(polymorphic(true) == polymorphic(true));
static_assert(polymorphic(false) == polymorphic(false));
static_assert(polymorphic(true) != polymorphic(false));

static constexpr int to_int(char /*c*/) {
  return 1;
}
static_assert(!polymorphic(false).map(to_int));
static_assert(polymorphic(true).map(to_int) == success(1, ""));

int main() {
}
