#include "m4c0/log.hpp"
#include "m4c0/riff/fs_reader.hpp"
#include "m4c0/riff/reader.hpp"
#include "m4c0/riff/subreader.hpp"

#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <type_traits>

using namespace m4c0::riff;

using fourcc_t = std::uint32_t;
struct header {
  fourcc_t fourcc;
  std::uint32_t length;
};
using chunk_callback_t = std::function<bool(header, reader *)>;

static std::string fourcc_str(fourcc_t fourcc) {
  return std::string(static_cast<char *>(static_cast<void *>(&fourcc)), 4);
}
static bool warn(const char * msg) {
  m4c0::log::warning(msg);
  return false;
}
static bool read_chunk(reader * r, const chunk_callback_t & callback) {
  auto h = r->read<header>();
  if (!h) return warn("Failed to read chunk header");

  auto start = r->tellg();
  auto end = start + (h->length + 1U & ~1U);
  if (!r->seekg(end)) return warn("Found truncated or misaligned chunk");
  if (!r->seekg(start)) return warn("Failure rewinding stream");

  subreader sr { r, start, h->length };
  return callback(*h, &sr) && r->seekg(end);
}

template<fourcc_t Expected>
static bool read_riff(reader * r, const chunk_callback_t & callback) {
  return read_chunk(r, [&](header h, reader * r) {
    if (h.fourcc != 'FFIR') return warn("File may not be a RIFF");

    auto type = r->read<fourcc_t>();
    if (!type) return warn("Failed to read file type in chunk list");
    if (*type != Expected) return warn("File is not an appropriate RIFF");

    while (r->tellg() < h.length) {
      if (!read_chunk(r, callback)) {
        return false;
      }
    }

    return true;
  });
}

class wav_dumper {
public:
  bool dump_fmt(reader * r) { // NOLINT
    m4c0::log::info("Found format");
    return true;
  }
  bool dump_data(reader * r) { // NOLINT
    m4c0::log::info("Found data");
    return true;
  }
};
static bool read_wav_chunks(header h, reader * r) {
  wav_dumper wd;
  if (h.fourcc == 'tmf ') return wd.dump_fmt(r);
  if (h.fourcc == 'atad') return wd.dump_data(r);
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
  if (!read_riff<'EVAW'>(&reader, &read_wav_chunks)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
