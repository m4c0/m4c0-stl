#pragma once

class AAssetManager;

namespace m4c0::assets {
  class native_provider {
  public:
    [[nodiscard]] virtual AAssetManager * asset_manager() const noexcept = 0;
  };
}
