#pragma once

#include "m4c0/containers/unique_array.hpp"
#include "m4c0/containers/unique_ptr.hpp"
#include "m4c0/espresso/common.hpp"

#include <stdexcept>

namespace m4c0::espresso::constant {
  enum class tag : uint8_t {
    k_null = 0,
    k_class = 7,
    k_fieldref = 9,
    k_methodref = 10,
    k_interface_methodref = 11,
    k_string = 8,
    k_integer = 3,
    k_float = 4,
    k_long = 5,
    k_double = 6,
    k_name_and_type = 12,
    k_utf8 = 1,
    k_method_handle = 15,
    k_method_type = 16,
    k_dynamic = 17,
    k_invoke_dynamic = 18,
    k_module = 19,
    k_package = 20,
  };

  template<tag Tag>
  class base;

  using item = containers::unique_ptr<base<tag::k_null>>;
  using pool = containers::unique_array<constant::item>;

  template<>
  class base<tag::k_null> {
  public:
    constexpr base() noexcept = default;
    constexpr base(const base &) = default;
    constexpr base(base &&) = default;
    constexpr base & operator=(const base &) noexcept = default;
    constexpr base & operator=(base &&) noexcept = default;
    constexpr virtual ~base() = default;

    constexpr virtual void assert_type(tag t) const {
    }
    constexpr virtual void validate(const pool & p) const {
    }
  };
  template<tag Tag>
  class base : public base<tag::k_null> {
  public:
    constexpr void assert_type(tag t) const final {
      if (t != Tag) throw std::runtime_error("Class name does not point to a name");
    }
  };

  class cls : public base<tag::k_class> {
    uint16_t m_name_index;

  public:
    constexpr explicit cls(uint16_t n) : m_name_index { n } {
    }

    constexpr void validate(const pool & p) const final {
      p.at(m_name_index - 1)->assert_type(tag::k_utf8);
    }
  };
  class methodref : public base<tag::k_methodref> {
    uint16_t m_class_index;
    uint16_t m_name_and_type_index;

  public:
    constexpr methodref(uint16_t c, uint16_t nt) : m_class_index { c }, m_name_and_type_index { nt } { // NOLINT
    }

    constexpr void validate(const pool & p) const final {
      p.at(m_class_index - 1)->assert_type(tag::k_class);
      p.at(m_name_and_type_index - 1)->assert_type(tag::k_name_and_type);
    }
  };
  class name_and_type : public base<tag::k_name_and_type> {
    uint16_t m_name_index;
    uint16_t m_descriptor_index;

  public:
    constexpr name_and_type(uint16_t n, uint16_t d) : m_name_index { n }, m_descriptor_index { d } { // NOLINT
    }

    constexpr void validate(const pool & p) const final {
      p.at(m_name_index - 1)->assert_type(tag::k_utf8);
      p.at(m_descriptor_index - 1)->assert_type(tag::k_utf8);
    }
  };
  class utf8 : public base<tag::k_utf8> {
    containers::unique_array<uint8_t> m_bytes;

  public:
    constexpr explicit utf8(decltype(m_bytes) b) : m_bytes { std::move(b) } {
    }
  };
}
