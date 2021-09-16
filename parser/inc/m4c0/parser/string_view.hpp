#pragma once

namespace m4c0::parser {
  // constexpr-noexcept version of std::string_view
  // Since we are ditching a STL class, we can ditch all of it here. This should improve compilation time for complex
  // parsers
  class string_view {
    const char * m_chars;
    unsigned long m_length;

  public:
    constexpr string_view(const char * c, unsigned long len) noexcept : m_chars { c }, m_length { len } {
    }
    template<unsigned N>
    constexpr string_view(const char (&c)[N]) noexcept : string_view { c, N - 1 } { // NOLINT
    }

    [[nodiscard]] constexpr bool operator==(const string_view & o) const noexcept {
      if (m_length != o.m_length) return false;

      const auto * a = m_chars;
      const auto * b = o.m_chars;
      for (unsigned i = 0; i < m_length; i++) {
        if (*a++ != *b++) return false; // NOLINT
      }
      return true;
    }

    [[nodiscard]] constexpr char at(unsigned index) const noexcept {
      return index >= 0 && index < m_length ? m_chars[index] : '\0'; // NOLINT
    }
    [[nodiscard]] constexpr const char * begin() const noexcept {
      return m_chars;
    }
    [[nodiscard]] constexpr const char * end() const noexcept {
      return m_chars + m_length; // NOLINT
    }

    [[nodiscard]] constexpr bool contains(char c) const noexcept {
      const auto * p = m_chars;
      for (unsigned i = 0; i < m_length; i++) {
        if (*p++ == c) return true; // NOLINT
      }
      return false;
    }

    [[nodiscard]] constexpr bool empty() const noexcept {
      return m_length == 0;
    }

    [[nodiscard]] constexpr unsigned length() const noexcept {
      return m_length;
    }

    [[nodiscard]] constexpr bool starts_with(const string_view & prefix) const noexcept {
      if (m_length < prefix.m_length) return false;
      return prefix == string_view { m_chars, prefix.m_length };
    }
    [[nodiscard]] constexpr string_view substr(unsigned index) const noexcept {
      if (index < 0) return { "" };
      if (index >= m_length) return { "" };
      return string_view { m_chars + index, m_length - index }; // NOLINT
    }

    // Returns a substring if they intersect in memory
    [[nodiscard]] constexpr string_view up_to(const string_view & o) const noexcept {
      auto len = o.begin() - begin();
      if (len <= 0 || len > m_length) return { "" };
      return string_view { begin(), static_cast<unsigned int>(len) };
    }
  };
}
