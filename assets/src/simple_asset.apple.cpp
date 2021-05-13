#include "m4c0/assets/simple_asset.hpp"
#include "m4c0/native_handles.metal.hpp"

#include <CoreFoundation/CoreFoundation.h>
#include <stdexcept>
#include <string>

using namespace m4c0::assets;

template<class Ptr>
using ptr = std::unique_ptr<std::remove_pointer_t<Ptr>, void (*)(CFTypeRef)>;
template<class Ptr>
static auto ref(Ptr p) {
  return ptr<Ptr> { p, CFRelease };
}

static auto to_string_ref(const char * cstr) {
  return ref(CFStringCreateWithCString(kCFAllocatorDefault, cstr, kCFStringEncodingASCII));
}

template<size_t N>
static auto read(const ptr<CFReadStreamRef> & stream, std::array<uint8_t, N> & data) {
  return CFReadStreamRead(stream.get(), data.data(), data.size());
}

static CFDataRef read_cfdata(const char * name, const char * ext) {
  auto name_s = to_string_ref(name);
  auto ext_s = to_string_ref(ext);

  CFBundleRef bundle = CFBundleGetMainBundle();

  auto url = ref(CFBundleCopyResourceURL(bundle, name_s.get(), ext_s.get(), nullptr));
  if (!url) {
    using namespace std::string_literals;
    throw std::runtime_error("Failed to get URL for resource: "s + name);
  }

  auto stream = ref(CFReadStreamCreateWithFile(kCFAllocatorDefault, url.get()));
  if (!stream) {
    using namespace std::string_literals;
    throw std::runtime_error("Failed to create stream for resource: "s + name);
  }

  if (CFReadStreamOpen(stream.get()) == 0U) {
    using namespace std::string_literals;
    throw std::runtime_error("Failed to open stream for resource: "s + name);
  }

  CFMutableDataRef data = CFDataCreateMutable(kCFAllocatorDefault, 0);

  static constexpr const auto buffer_size = 1024;
  std::array<uint8_t, buffer_size> buffer {};
  for (auto count = read(stream, buffer); count > 0; count = read(stream, buffer)) {
    CFDataAppendBytes(data, buffer.data(), count);
  }

  CFReadStreamClose(stream.get());
  return data;
}

namespace m4c0::assets {
  class concrete_simple_asset : public simple_asset {
    CFDataRef m_data;

  public:
    concrete_simple_asset(const char * name, const char * ext) : m_data(read_cfdata(name, ext)) {
    }
    ~concrete_simple_asset() override {
      CFRelease(m_data);
    }

    concrete_simple_asset(concrete_simple_asset &&) = delete;
    concrete_simple_asset(const concrete_simple_asset &) = delete;
    concrete_simple_asset & operator=(concrete_simple_asset &&) = delete;
    concrete_simple_asset & operator=(const concrete_simple_asset &) = delete;

    [[nodiscard]] const void * data() const noexcept override {
      return CFDataGetBytePtr(m_data);
    }
    [[nodiscard]] unsigned size() const noexcept override {
      return CFDataGetLength(m_data);
    }
  };
}

std::unique_ptr<simple_asset> simple_asset::load(const native_handles * /*nptr*/, const char * name, const char * ext) {
  return std::make_unique<concrete_simple_asset>(name, ext);
}
