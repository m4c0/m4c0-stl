#include "m4c0/assets/simple_asset.hpp"

#include <android/asset_manager.h>

static auto load_resource(AAssetManager * amgr, const char * name, const char * ext) {
  auto name_ext = std::string { name } + "." + ext;
  return AAssetManager_open(amgr, name_ext.c_str(), AASSET_MODE_BUFFER);
}

namespace m4c0::assets {
  class concrete_simple_asset : public simple_asset {
    AAsset m_data;

  public:
    concrete_simple_asset(AAssetManager * amgr, const char * name, const char * ext)
      : m_data(load_resource(amgr, name, ext)) {
    }
    ~concrete_simple_asset() override {
      AAsset_close(m_data);
    }

    [[nodiscard]] const void * data() const noexcept override {
      return AAsset_getBuffer(m_data);
    }
    [[nodiscard]] unsigned size() const noexcept override {
      return AAsset_getLength(m_data);
    }
  };

  std::unique_ptr<simple_asset> simple_asset::load(native_ptr_t nptr, const char * name, const char * ext) {
    return std::make_unique<concrete_simple_asset>(static_cast<AAssetManager>(nptr), name, ext);
  }
}
