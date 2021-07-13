#include "m4c0/io/istr_reader.hpp"
#include "m4c0/riff/parser.hpp"
#include "m4c0/test.hpp"

#include <sstream>
#include <string>

using namespace m4c0::io;
using namespace m4c0::riff;
using namespace std::string_literals;

class callback {
public:
  bool success(reader * r) { // NOLINT
    return true;
  }
  bool failure(reader * r) { // NOLINT
    return false;
  }
  bool echo(reader * r) { // NOLINT
    return r->read<unsigned>().value_or(0) == 'OHCE';
  }
  bool half_echo(reader * r) { // NOLINT
    // Must read !
    if (r->read<char>().value_or(0) != '!') return false;
    // And nothing else
    return r->read<char>().value_or(1) == 1;
  }
};

class test_data {
  std::stringstream m_str;
  istr_reader m_reader;
  riff_parser<callback> m_rp { 'TSET' };

public:
  explicit test_data(const std::string & s) : m_str { s }, m_reader { m_str } {
    m_rp.emplace('liaf', &callback::failure);
    m_rp.emplace('eurt', &callback::success);
    m_rp.emplace('ohce', &callback::echo);
    m_rp.emplace('flah', &callback::half_echo);
  }

  void assert_parses(bool result) {
    callback cb {};

    AssertThat(m_rp.parse(&m_reader, &cb), Is().EqualTo(result));
  }
};

go_bandit([] { // NOLINT
  describe("m4c0::riff::riff_parser", [] {
    it("has a chance of working on this platform", [] {
      static constexpr const auto expected_len = 8;
      const auto str = "RIFF\0\0\0\0"s;
      AssertThat(str.length(), Is().EqualTo(expected_len));
    });
    it("fails if RIFF chunk is truncated", [] {
      test_data("RIFF\x4\0\0\0TE"s).assert_parses(false);
    });
    it("fails if RIFF chunk has different type", [] {
      test_data("RIFF\x4\0\0\0WAVE"s).assert_parses(false);
    });
    it("can read an empty file of the correct type", [] {
      test_data("RIFF\x4\0\0\0TEST"s).assert_parses(true);
    });
    it("ignores unknown chunk types", [] {
      test_data("RIFF\x14\0\0\0TESTlist\0\0\0\0m4c0\0\0\0\0"s).assert_parses(true);
    });
    it("fails if last chunk is truncated", [] {
      test_data("RIFF\x10\0\0\0TESTlist\x8\0\0\0m4c0"s).assert_parses(false);
    });
    it("fails if a chunk parse fails", [] {
      test_data("RIFF\x14\0\0\0TESTfail\0\0\0\0true\0\0\0\0"s).assert_parses(false);
      test_data("RIFF\x14\0\0\0TESTtrue\0\0\0\0true\0\0\0\0"s).assert_parses(true);
    });
    it("passes data to subparsers", [] {
      test_data("RIFF\x18\0\0\0TESTecho\4\0\0\0ECHOtrue\0\0\0\0"s).assert_parses(true);
      test_data("RIFF\x18\0\0\0TESTecho\4\0\0\0ECHOfail\0\0\0\0"s).assert_parses(false);
    });
    it("word-aligns", [] {
      test_data("RIFF\x16\0\0\0TESThalf\1\0\0\0!$true\0\0\0\0"s).assert_parses(true);
      test_data("RIFF\x16\0\0\0TESThalf\1\0\0\0!$fail\0\0\0\0"s).assert_parses(false);
    });
  });
});
