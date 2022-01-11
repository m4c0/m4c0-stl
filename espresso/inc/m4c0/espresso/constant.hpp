#pragma once

#include "m4c0/containers/unique_array.hpp"
#include "m4c0/containers/unique_ptr.hpp"
#include "m4c0/espresso/common.hpp"
#include "m4c0/io/ce_reader.hpp"

#include <variant>

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

  static constexpr auto read_utf8_bytes(m4c0::io::reader * r) {
    auto count = unwrap(r->read_u16_be(), "Missing UTF8 length");
    auto bytes = containers::unique_array<uint8_t> { count };
    for (auto & b : bytes) {
      b = unwrap(r->read_u8(), "Missing UTF8 char");
    }
    return bytes;
  }
  static constexpr constant::item read(m4c0::io::reader * r) {
    enum {
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
    switch (unwrap(r->read_u8(), "Missing constant tag")) {
    case k_class:
      return item { new constant::cls {
          unwrap(r->read_u16_be(), "Missing name index in class"),
      } };
    case k_double:
      throw std::runtime_error("Double not supported");
    case k_dynamic:
      throw std::runtime_error("Dynamic not supported");
    case k_fieldref:
      throw std::runtime_error("Fieldref not supported");
    case k_float:
      throw std::runtime_error("Float not supported");
    case k_integer:
      throw std::runtime_error("Integer not supported");
    case k_interface_methodref:
      throw std::runtime_error("Interface-methodref not supported");
    case k_invoke_dynamic:
      throw std::runtime_error("Invoke dynamic not supported");
    case k_long:
      throw std::runtime_error("Long not supported");
    case k_method_handle:
      throw std::runtime_error("Method handle not supported");
    case k_method_type:
      throw std::runtime_error("Method type not supported");
    case k_methodref:
      return item { new constant::methodref {
          unwrap(r->read_u16_be(), "Missing class index in methodref"),
          unwrap(r->read_u16_be(), "Missing name/type index in methodref"),
      } };
    case k_module:
      throw std::runtime_error("Module not supported");
    case k_name_and_type:
      return item { new constant::name_and_type {
          unwrap(r->read_u16_be(), "Missing name index in name/type"),
          unwrap(r->read_u16_be(), "Missing descriptor index in name/type"),
      } };
    case k_null:
      throw std::runtime_error("Invalid constant tag");
    case k_package:
      throw std::runtime_error("Package not supported");
    case k_string:
      throw std::runtime_error("String not supported");
    case k_utf8:
      return item { new constant::utf8 {
          std::move(read_utf8_bytes(r)),
      } };
    default:
      throw std::runtime_error("Unsupported constant tag");
    }
  }
}
