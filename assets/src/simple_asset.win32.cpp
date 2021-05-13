#include "m4c0/assets/simple_asset.hpp"
#include "m4c0/native_handles.win32.hpp"

#include <filesystem>
#include <fstream>
#include <tchar.h>
#include <vector>
#include <windows.h>

namespace m4c0::assets {
  class concrete_simple_asset : public simple_asset {
    std::vector<char> m_data {};

  public:
    concrete_simple_asset(const char * name, const char * ext) {
      std::string fn = std::string(name) + "." + ext;

      TCHAR cpath[MAX_PATH + 1];
      if (GetModuleFileName(0, cpath, MAX_PATH) == 0) {
        throw std::runtime_error("Failed to get EXE filename");
      }

      std::filesystem::path exe_path { cpath };
      std::ifstream ifs { exe_path.parent_path() / "assets" / fn, std::ios::ate | std::ios::binary };
      if (!ifs.is_open()) {
        using namespace std::string_literals;
        throw std::runtime_error("Failed to open resource: "s + fn);
      }

      m_data.resize(ifs.tellg());
      ifs.seekg(0);
      std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), std::begin(m_data));
    }

    [[nodiscard]] const void * data() const noexcept override {
      return m_data.data();
    }
    [[nodiscard]] unsigned size() const noexcept override {
      return m_data.size();
    }
  };

  std::unique_ptr<simple_asset> simple_asset::load(
      const native_handles * /*nptr*/,
      const char * name,
      const char * ext) {
    return std::make_unique<concrete_simple_asset>(name, ext);
  }
}
