#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <span>
#include <string_view>
#include <type_traits>
#include <variant>

using namespace m4c0::parser;

// This is far from a "compliant" BrainF compiler. It does not ignore non-command characters, etc.
// Remember: this is only a compile-time test for the parsing library

// Super-lazy way to do input.
static constexpr input_t hardcoded_input = "I'm lazy";
struct state {
  unsigned in_ptr { 0 };

  static constexpr const auto bf_magic_buffer_size = 30000;

  std::array<char, bf_magic_buffer_size> data {};
  unsigned data_ptr { 0 };

  std::array<char, bf_magic_buffer_size> output {};
  unsigned output_ptr { 0 };
};

template<typename OpFn>
requires std::is_invocable_r_v<state, OpFn, state>
static constexpr auto operator+(const state & s, OpFn && b) {
  return b(s);
}
static constexpr bool operator==(const state & s, std::string_view str) {
  return std::equal(str.begin(), str.end(), s.output.begin(), s.output.begin() + s.output_ptr);
}

using op_fn = state (*)(state);

using opcode = std::variant<op_fn, input_t>;

static constexpr auto symbol(char c, op_fn && fn) {
  return match(c) & opcode { fn };
}

static constexpr auto gt = symbol('>', [](state s) {
  s.data_ptr++;
  return s;
});
static constexpr auto lt = symbol('<', [](state s) {
  s.data_ptr--;
  return s;
});
static constexpr auto plus = symbol('+', [](state s) {
  s.data.at(s.data_ptr)++;
  return s;
});
static constexpr auto minus = symbol('-', [](state s) {
  s.data.at(s.data_ptr)--;
  return s;
});
static constexpr auto dot = symbol('.', [](state s) {
  s.output.at(s.output_ptr++) = s.data.at(s.data_ptr);
  return s;
});
static constexpr auto comma = symbol(',', [](state s) {
  s.data.at(s.data_ptr) = hardcoded_input.at(s.in_ptr++);
  return s;
});

static constexpr auto lbr = skip(match('['));
static constexpr auto rbr = skip(match(']'));

static constexpr auto ops = gt | lt | plus | minus | dot | comma;

static constexpr auto block() -> result<opcode> (*)(input_t) {
  return [](input_t in) -> result<opcode> {
    const auto p = lbr + many(skip(block()) | skip(ops)) + rbr;
    return (p & opcode { in })(in);
  };
}
static constexpr auto expr = ops | block();

static constexpr state operator+(const state & s, opcode o) {
  return std::visit(
      [s](auto v) -> state {
        if constexpr (std::is_same_v<decltype(v), input_t>) {
          state res = s;
          while (res.data.at(s.data_ptr) > 0) {
            const auto p = lbr + many(expr, res) + rbr;
            // It doesn't matter for this example, but in real life we should deal with failures - otherwise, we might
            // face issues that are valid from a parser perspective, but invalid from a semantic perspective
            res = *p(v);
          }
          return res;
        } else {
          return v(s);
        }
      },
      o);
}

static constexpr auto brainf = many(expr, state {}) + eof();

// Real BF parsers must support non-command characters. This is a test, therefore, we don't. Let's use it to test if the
// parser can parse the whole string
static_assert(!brainf("+++.nope"));

// Very simple examples to confirm we can do a constexpr recursive parser
// Spoiler: we can
//
// Beep (aka output ASCII 7 (BEL) - aka "something without loops")
// Taken from Daniel Christofani's website: http://www.brainfuck.org/short.b
static constexpr const auto BEL = *brainf("+++++++.");
static_assert(BEL == "\7");
// Sum two numbers, then convert to ASCII - checks if loops work
// Taken from Wikipedia: https://en.wikipedia.org/wiki/Brainfuck
static constexpr const auto SEVEN = *brainf("++>+++++[<+>-]++++++++[<++++++>-]<.");
static_assert(SEVEN == "7");
// Copy input to output - check if nested loops work (i.e. even more recursiveness needed for this)
// Taken from Daniel Christofani's website: http://www.brainfuck.org/short.b
static constexpr const auto COPY_FROM_LAZY_INPUT = *brainf(",[.[-],]");
static_assert(COPY_FROM_LAZY_INPUT == "I'm lazy");
