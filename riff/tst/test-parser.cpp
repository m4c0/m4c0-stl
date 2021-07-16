#include "m4c0/io/ce_reader.hpp"
#include "m4c0/io/istr_reader.hpp"
#include "m4c0/io/subreader.hpp"
#include "m4c0/riff/parser.hpp"

#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using namespace m4c0::io;
using namespace m4c0::riff;
using namespace std::string_literals;
using namespace std::string_view_literals;

class callback {
public:
  constexpr bool success(reader * r) { // NOLINT
    return true;
  }
  constexpr bool failure(reader * r) { // NOLINT
    return false;
  }
  constexpr bool echo(reader * r) { // NOLINT
    return r->read_u32().value_or(0) == 'OHCE';
  }
  constexpr bool half_echo(reader * r) { // NOLINT
    // Must read !
    if (r->read_u8().value_or(0) != '!') return false;
    // And nothing else
    return r->read_u8().value_or(1) == 1;
  }
};

template<auto N>
static constexpr auto parse(const char (&data)[N], unsigned size = N - 1) { // NOLINT
  riff_parser<callback, 4> rp {
    'TSET',
    {
        { 'liaf', &callback::failure },
        { 'eurt', &callback::success },
        { 'ohce', &callback::echo },
        { 'flah', &callback::half_echo },
    },
  };

  callback cb {};

  m4c0::io::ce_reader r { data };

  auto sub = m4c0::io::subreader::seek_and_create(&r, 0, size).value();
  return rp.parse(&sub, &cb);
}

// Fails if empty or smaller than header
static_assert(!parse(" ", 0)); // We can't use an empty string since this creates an 0-len array
static_assert(!parse("RI"));
static_assert(!parse("RIFF"));
static_assert(!parse("RIFF\0\0"));
static_assert(!parse("RIFF\0\0\0\0"));
// Fails if RIFF chunk is truncated
static_assert(!parse("RIFF\x2\0\0\0TE"));
// Fails if RIFF chunk has different type
static_assert(!parse("RIFF\x4\0\0\0WAVE"));
// Test if it can read an valid empty file
static_assert(parse("RIFF\x4\0\0\0TEST"));
// Test if it ignores unknown chunk types
static_assert(parse("RIFF\x14\0\0\0TESTlist\0\0\0\0m4c0\0\0\0\0"));
// Fails if last chunk is truncated"
static_assert(!parse("RIFF\x10\0\0\0TESTlist\x8\0\0\0m4c0"));
// Fails if a chunk parse fails
static_assert(!parse("RIFF\x14\0\0\0TESTfail\0\0\0\0true\0\0\0\0"));
static_assert(parse("RIFF\x14\0\0\0TESTtrue\0\0\0\0true\0\0\0\0"));
// Test if passes data to subparsers"
static_assert(parse("RIFF\x18\0\0\0TESTecho\4\0\0\0ECHOtrue\0\0\0\0"));
static_assert(!parse("RIFF\x18\0\0\0TESTecho\4\0\0\0ECHOfail\0\0\0\0"));
// Test if parses word-aligned
static_assert(parse("RIFF\x16\0\0\0TESThalf\1\0\0\0!$true\0\0\0\0"));
static_assert(!parse("RIFF\x16\0\0\0TESThalf\1\0\0\0!$fail\0\0\0\0"));

int main() {
}
