#pragma once

#include "m4c0/espresso/constant.hpp"
#include "m4c0/io/ce_reader.hpp"

namespace m4c0::espresso {
  static constexpr auto read_utf8_bytes(m4c0::io::reader * r) {
    auto count = read_u16(r, "Missing UTF8 length");
    auto bytes = containers::unique_array<uint8_t> { count };
    if (!r->read(bytes.begin(), count)) {
      throw std::runtime_error("Truncated UTF8 chars");
    }
    return bytes;
  }
  static constexpr constant::item read_item(m4c0::io::reader * r) {
    switch (static_cast<constant::tag>(unwrap(r->read_u8(), "Missing constant tag"))) {
    case constant::tag::k_class:
      return constant::item { new constant::cls {
          read_u16(r, "Missing name index in class"),
      } };
    case constant::tag::k_double:
      throw std::runtime_error("Double not supported");
    case constant::tag::k_dynamic:
      throw std::runtime_error("Dynamic not supported");
    case constant::tag::k_fieldref:
      throw std::runtime_error("Fieldref not supported");
    case constant::tag::k_float:
      throw std::runtime_error("Float not supported");
    case constant::tag::k_integer:
      throw std::runtime_error("Integer not supported");
    case constant::tag::k_interface_methodref:
      throw std::runtime_error("Interface-methodref not supported");
    case constant::tag::k_invoke_dynamic:
      throw std::runtime_error("Invoke dynamic not supported");
    case constant::tag::k_long:
      throw std::runtime_error("Long not supported");
    case constant::tag::k_method_handle:
      throw std::runtime_error("Method handle not supported");
    case constant::tag::k_method_type:
      throw std::runtime_error("Method type not supported");
    case constant::tag::k_methodref:
      return constant::item { new constant::methodref {
          read_u16(r, "Missing class index in methodref"),
          read_u16(r, "Missing name/type index in methodref"),
      } };
    case constant::tag::k_module:
      throw std::runtime_error("Module not supported");
    case constant::tag::k_name_and_type:
      return constant::item { new constant::name_and_type {
          read_u16(r, "Missing name index in name/type"),
          read_u16(r, "Missing descriptor index in name/type"),
      } };
    case constant::tag::k_null:
      throw std::runtime_error("Invalid constant tag");
    case constant::tag::k_package:
      throw std::runtime_error("Package not supported");
    case constant::tag::k_string:
      throw std::runtime_error("String not supported");
    case constant::tag::k_utf8:
      return constant::item { new constant::utf8 {
          std::move(read_utf8_bytes(r)),
      } };
    default:
      throw std::runtime_error("Unsupported constant tag");
    }
  }

  static constexpr constant::pool read_cpool(m4c0::io::reader * r) {
    constant::pool res { read_u16(r, "Truncated constant pool count") - 1U };
    for (auto & item : res) {
      item = read_item(r);
    }
    for (const auto & item : res) {
      item->validate(res);
    }
    return res;
  }
}
