#pragma once

class AAssetManager;
class ANativeWindow;

namespace m4c0 {
  class native_handles {
  public:
    [[nodiscard]] virtual AAssetManager * asset_manager() const noexcept = 0;
    [[nodiscard]] virtual ANativeWindow * window() const noexcept = 0;
  };
}
