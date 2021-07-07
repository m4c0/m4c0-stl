#include "m4c0/riff/istr_reader.hpp"
#include "m4c0/riff/subreader.hpp"
#include "m4c0/test.hpp"

#include <sstream>

using namespace m4c0::riff;

class holder {
  std::istringstream m_str;
  istr_reader m_reader;
  std::optional<subreader> m_sub;

public:
  static constexpr auto start_pos = 5; // "is a"
  static constexpr auto len = 4;

  holder() : holder("this is a test", start_pos, len) {
  }
  holder(const char * text, unsigned start, unsigned len)
    : m_str(text)
    , m_reader(m_str)
    , m_sub(subreader::seek_and_create(&m_reader, start, len)) {
  }

  [[nodiscard]] constexpr explicit operator bool() const noexcept {
    return m_sub.has_value();
  }
  [[nodiscard]] constexpr auto * operator->() noexcept {
    return &m_sub.value();
  }

  [[nodiscard]] constexpr auto & strstream() noexcept {
    return m_str;
  }
};

static void assert_position(holder & h, bool eof, unsigned pos) {
  AssertThat(static_cast<bool>(h), Is().True());
  AssertThat(h->tellg(), Is().EqualTo(pos));
  AssertThat(h->eof(), Is().EqualTo(eof));
}
static void assert_position(bool result, holder & h, bool eof, unsigned pos) {
  AssertThat(result, Is().True());
  assert_position(h, eof, pos);
}

go_bandit([] { // NOLINT
  describe("m4c0::riff::reader", [] {
    it("seeks stream in ctor", [] {
      holder h { "test", 2, 1 };
      AssertThat(static_cast<bool>(h), Is().True());
      AssertThat(static_cast<unsigned>(h.strstream().tellg()), Is().EqualTo(2));
    });
    it("creates an invalid instance if ctor can't seek", [] {
      holder h { "test", holder::len + 1, 1 };
      AssertThat(static_cast<bool>(h), Is().False());
    });
    it("can tell current position from start", [] {
      holder h;
      assert_position(h, false, 0);
    });
    it("doesn't seek before limit", [] {
      holder h;
      assert_position(!h->seekg(-1), h, false, 0);
    });
    it("doesn't seek past limit", [] {
      holder h;
      assert_position(!h->seekg(holder::len + 1), h, false, 0);
    });
    it("seeks properly", [] {
      holder h;
      assert_position(h->seekg(2), h, false, 2);
    });
    it("seeks to current pos", [] {
      holder h;
      assert_position(h->seekg(0), h, false, 0);
    });
  });
});
