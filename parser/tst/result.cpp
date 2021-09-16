#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

static_assert(success('X') == success('X'));
static_assert(success('X') != success('O'));

static_assert(failure<char>("failure") == failure<char>("failure"));
static_assert(failure<char>("other failure") != failure<char>("failure"));

static constexpr result<char> polymorphic(bool b) {
  return b ? result { success('!'), "X" } : result { failure<char>("failed"), "Y" };
}
static_assert(polymorphic(true) == polymorphic(true));
static_assert(polymorphic(false) == polymorphic(false));
static_assert(polymorphic(true) != polymorphic(false));

static_assert(result<char>(success('1'), "") == result<char>(success('1'), ""));
static_assert(result<char>(success('1'), "") != result<char>(success('1'), "A"));
static_assert(result<char>(success('1'), "") != result<char>(success('2'), ""));
static_assert(result<int>(failure<char>("test"), "") == result { failure<int>("test"), "" });

static_assert((polymorphic(true) | success { '@' }) == result { success('!'), "X" });
static_assert((polymorphic(false) | success { '@' }) == result { success('@'), "Y" });

static_assert((polymorphic(true) & success { '@' }) == result { success('@'), "X" });
static_assert(!(polymorphic(false) & success { '@' }));

static_assert((polymorphic(true) | failure { "OK" }) == result { success('!'), "X" });
static_assert((polymorphic(false) | failure { "OK" }) == result { failure<char>("OK"), "Y" });

static_assert((polymorphic(true) & failure { "OK" }) == result { failure<char>("OK"), "X" });
static_assert((polymorphic(false) & failure { "OK" }) == result { failure<char>("failed"), "Y" });

static_assert((polymorphic(true) | result { success { '@' }, "A" }) == result { success('!'), "X" });
static_assert((polymorphic(false) | result { success { '@' }, "A" }) == result { success('@'), "A" });

static_assert((polymorphic(true) & result { success { '@' }, "A" }) == result { success('@'), "A" });
static_assert(!(polymorphic(false) & result { success { '@' }, "A" }));

static constexpr result<int> parse_int(char c, input_t v) {
  return { success { c == '!' ? 1 : 0 }, v };
}
static_assert(!(polymorphic(false) & parse_int));
static_assert((polymorphic(true) & parse_int) == result { success { 1 }, "X" });

static constexpr int to_int(char c) {
  return c == '!' ? 1 : 0;
}
static_assert(!(polymorphic(false) & to_int));
static_assert((polymorphic(true) & to_int) == result { success { 1 }, "X" });

static_assert(*polymorphic(true) == '!');

static_assert(polymorphic(true) % [](auto msg) {
  if constexpr (std::is_same_v<decltype(msg), input_t>) {
    return false;
  } else {
    return msg == '!';
  }
});
static_assert(polymorphic(false) % [](auto msg) {
  if constexpr (std::is_same_v<decltype(msg), input_t>) {
    return msg == "failed";
  } else {
    return false;
  }
});
static_assert(polymorphic(true) % [](auto msg, auto rem) {
  if constexpr (std::is_same_v<decltype(msg), input_t>) {
    return false;
  } else {
    return msg == '!' && rem == "X";
  }
});
static_assert(polymorphic(false) % [](auto msg, auto rem) {
  if constexpr (std::is_same_v<decltype(msg), input_t>) {
    return msg == "failed" && rem == "Y";
  } else {
    return false;
  }
});

static_assert([] {
  class val {
    bool m_result { true };

  public:
    [[nodiscard]] constexpr bool test() const noexcept {
      return m_result;
    }
  };
  return result { success { val {} }, "" } & &val::test;
}());

int main() {
}
