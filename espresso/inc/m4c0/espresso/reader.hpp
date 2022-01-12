#pragma once

#include "m4c0/espresso/constant.hpp"
#include "m4c0/espresso/raw_class.hpp"
#include "m4c0/io/reader.hpp"

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

  static constexpr containers::unique_array<raw::attribute> read_attributes(io::reader * r, const constant::pool & pool) {
    auto res = containers::unique_array<raw::attribute> { read_u16(r, "Truncated attribute list count") };
    for (auto & a : res) {
      a.name = read_u16(r, "Truncated attribute name");
      pool.at(a.name - 1)->assert_type(constant::utf8::type);

      a.info = containers::unique_array<uint8_t> { read_u32(r, "Truncated attribute info size") };
      if (!r->read(a.info.begin(), a.info.size())) {
        throw std::runtime_error("Truncated attribute info");
      }
    }
    return res;
  }

  static constexpr containers::unique_array<raw::member> read_members(io::reader * r, const constant::pool & pool) {
    auto res = containers::unique_array<raw::member> { read_u16(r, "Truncated member list count") };
    for (auto & m : res) {
      m.flags = read_u16(r, "Truncated member access flags");
      m.name = read_u16(r, "Truncated member name");
      pool.at(m.name - 1)->assert_type(constant::utf8::type);

      m.descriptor = read_u16(r, "Truncated member descriptor");
      pool.at(m.name - 1)->assert_type(constant::utf8::type);

      m.attributes = read_attributes(r, pool);
    }
    return res;
  }

  static constexpr raw::cls_header read_header(io::reader * r) {
    constexpr const auto class_magic_number = 0xCAFEBABE;
    constexpr const auto min_version = 45.0;
    constexpr const auto max_version = 55.0;

    raw::cls_header res {};
    res.magic = read_u32(r, "Truncated magic number");
    if (res.magic != class_magic_number) throw std::runtime_error("Invalid magic number");

    res.minor_version = read_u16(r, "Truncated minor version");
    res.major_version = read_u16(r, "Truncated major version");
    if (res.major_version < min_version || res.major_version > max_version) {
      throw std::runtime_error("Unsupported version");
    }

    res.cpool = read_cpool(r);
    res.flags = read_u16(r, "Truncated access flags");

    res.this_class = read_u16(r, "Truncated 'this' class ref");
    res.cpool.at(res.this_class - 1)->assert_type(constant::cls::type);

    res.super_class = read_u16(r, "Truncated 'super' class ref");
    res.cpool.at(res.super_class - 1)->assert_type(constant::cls::type);

    res.ifaces = containers::unique_array<uint16_t> { read_u16(r, "Truncated interface list count") };
    for (auto & iface : res.ifaces) {
      iface = read_u16(r, "Truncated interface list");
      res.cpool.at(iface - 1)->assert_type(constant::cls::type);
    }

    res.fields = read_members(r, res.cpool);
    res.methods = read_members(r, res.cpool);
    res.attributes = read_attributes(r, res.cpool);
    return res;
  }
}
