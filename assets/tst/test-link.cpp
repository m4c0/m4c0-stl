#include "m4c0/assets/simple_asset.hpp"
#include "m4c0/assets/stb_image.hpp"
#include "m4c0/native_handles.metal.hpp"

int main() {
  m4c0::native_handles * nh {};

  auto res = m4c0::assets::simple_asset::load(nh, "my-asset", "jpg");
  auto img = m4c0::assets::typed_stb_image<>::load_from_asset(nh, "my-asset", "jpg");
}
