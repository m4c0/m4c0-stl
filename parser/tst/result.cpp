#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

static_assert(success('X') == success('X'));
static_assert(success('X') != success('O'));

static_assert(failure<char>("failure") == failure<char>("failure"));
static_assert(failure<char>("other failure") != failure<char>("failure"));

static_assert(success('X').value() == 'X');
static_assert(success('X').value() != 'O');

static constexpr result<char> polymorphic(bool b) {
  return b ? result { success('!') } : result { failure<char>("failed") };
}
static_assert(polymorphic(true) == polymorphic(true));
static_assert(polymorphic(false) == polymorphic(false));
static_assert(polymorphic(true) != polymorphic(false));

static_assert(polymorphic(true).value() == '!');
static_assert(!polymorphic(false).value().has_value());

static_assert(!polymorphic(true).error().has_value());
static_assert(polymorphic(false).error() == "failed");

int main() {
}
