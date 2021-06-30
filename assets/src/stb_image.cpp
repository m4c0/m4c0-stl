#include "m4c0/assets/simple_asset.hpp"
#include "m4c0/assets/stb_image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace m4c0::assets;

static auto load(const simple_asset * r, int * w, int * h) {
  auto span = r->span<stbi_uc>();
  auto len = static_cast<int>(span.size());

  int n = 0;
  return stbi_load_from_memory(span.data(), len, w, h, &n, 4);
}

stb_image::stb_image(const simple_asset * r) : m_width(0), m_height(0), m_data(load(r, &m_width, &m_height)) {
}

stb_image::~stb_image() {
  stbi_image_free(m_data);
}

stb_image stb_image::load_from_asset(const m4c0::native_handles * nptr, const char * name, const char * ext) {
  auto asset = simple_asset::load(nptr, name, ext);
  return stb_image(asset.get());
}
