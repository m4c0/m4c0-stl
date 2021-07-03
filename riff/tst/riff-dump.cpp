#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <type_traits>

class reader {
protected:
  [[nodiscard]] virtual bool read(void * buffer, unsigned len) = 0;

public:
  [[nodiscard]] virtual bool seekg(unsigned pos) = 0;
  [[nodiscard]] virtual unsigned tellg() = 0;

  template<class Tp>
  [[nodiscard]] std::optional<Tp> read() {
    static_assert(std::is_trivial_v<Tp>);
    Tp res {};
    if (read(&res, sizeof(res))) {
      return { res };
    }
    return {};
  }
};

class fs_reader : public reader {
  std::ifstream & m_ifs;

public:
  explicit constexpr fs_reader(std::ifstream & ifs) : m_ifs(ifs) {
  }

  [[nodiscard]] bool read(void * buffer, unsigned len) override {
    return static_cast<bool>(m_ifs.read(static_cast<char *>(buffer), len));
  }
  [[nodiscard]] bool seekg(unsigned pos) override {
    return static_cast<bool>(m_ifs.seekg(pos));
  }
  [[nodiscard]] unsigned tellg() override {
    return m_ifs.tellg();
  }
};

struct header {
  std::uint32_t fourcc;
  std::uint32_t length;
};
static bool read_riff(reader * r) {
  auto h = r->read<header>();
  if (!h) {
    std::cerr << "Failed to read RIFF header\n";
    return false;
  }
  if (h->fourcc != 'FFIR') {
    std::cerr << "File may not be RIFF\n";
    return false;
  }
  auto start = r->tellg();
  if (!r->seekg(start + h->length)) {
    std::cerr << "Truncated chunk at " << start << "\n";
    return false;
  }
  std::cerr << "RIFF - len=" << h->length << "\n";
  return true;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    std::cerr << "Missing file name\n";
    return EXIT_FAILURE;
  }

  const char * filename = argv[1]; // NOLINT
  std::ifstream in { filename, std::ios::binary };
  if (!in) {
    std::cerr << "File not found: " << filename << "\n";
    return EXIT_FAILURE;
  }

  fs_reader reader { in };
  if (!read_riff(&reader)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
