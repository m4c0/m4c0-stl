#pragma once

#include "m4c0/containers/unique_array.hpp"
#include "m4c0/containers/unique_ptr.hpp"
#include "m4c0/espresso/common.hpp"

namespace m4c0::espresso::constant {
  class base {
  public:
    constexpr base() noexcept = default;
    constexpr base(const base &) = default;
    constexpr base(base &&) = default;
    constexpr base & operator=(const base &) noexcept = default;
    constexpr base & operator=(base &&) noexcept = default;
    constexpr virtual ~base() = default;
  };

  class cls : public base {
    uint16_t m_name_index;

  public:
    constexpr explicit cls(uint16_t n) : m_name_index { n } {
    }
  };
  class methodref : public base {
    uint16_t m_class_index;
    uint16_t m_name_and_type_index;

  public:
    constexpr methodref(uint16_t c, uint16_t nt) : m_class_index { c }, m_name_and_type_index { nt } { // NOLINT
    }
  };
  class name_and_type : public base {
    uint16_t m_name_index;
    uint16_t m_descriptor_index;

  public:
    constexpr name_and_type(uint16_t n, uint16_t d) : m_name_index { n }, m_descriptor_index { d } { // NOLINT
    }
  };
  class utf8 : public base {
    containers::unique_array<uint8_t> m_bytes;

  public:
    constexpr explicit utf8(decltype(m_bytes) b) : m_bytes { std::move(b) } {
    }
  };

  using item = containers::unique_ptr<base>;

  class pool {
    containers::unique_array<constant::item> m_data {};

  public:
    constexpr pool() = default;
    constexpr explicit pool(size_t n) noexcept : m_data { n } {
    }
    [[nodiscard]] constexpr auto & operator*() noexcept {
      return m_data;
    }
    [[nodiscard]] constexpr const auto & operator*() const noexcept {
      return m_data;
    }
  };
}
