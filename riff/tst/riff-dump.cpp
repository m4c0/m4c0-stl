#include "m4c0/log.hpp"
#include "m4c0/riff/fs_reader.hpp"
#include "m4c0/riff/reader.hpp"
#include "m4c0/riff/subreader.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <type_traits>

using namespace m4c0::riff;

struct header {
  std::uint32_t fourcc;
  std::uint32_t length;
};
static std::string fourcc_str(std::uint32_t fourcc) {
  return std::string(static_cast<char *>(static_cast<void *>(&fourcc)), 4);
}
static bool warn(const char * msg) {
  m4c0::log::warning(msg);
  return false;
}
static bool read_chunk(reader * r, bool (*callback)(header h, reader * r)) {
  auto h = r->read<header>();
  if (!h) return warn("Failed to read chunk header");

  auto start = r->tellg();
  auto end = start + (h->length + 1U & ~1U);
  if (!r->seekg(end)) return warn("Found truncated or misaligned chunk");
  if (!r->seekg(start)) return warn("Failure rewinding stream");

  subreader sr { r, start, h->length };
  return callback(*h, &sr) && r->seekg(end);
}
static bool read_list(header h, reader * r, bool (*chunk_callback)(header h, reader * r)) {
  auto type = r->read<std::uint32_t>();
  if (!type) return warn("Failed to read file type in chunk list");

  std::cerr << fourcc_str(h.fourcc) << " - type=[" << fourcc_str(*type) << "] - len=" << h.length << "\n";
  while (r->tellg() < h.length) {
    if (!read_chunk(r, chunk_callback)) {
      return false;
    }
  }
  std::cerr << "end list\n";
  return true;
}
static bool read_list_chunks(auto h, auto * /*r*/) {
  std::cerr << "  " << fourcc_str(h.fourcc) << " - len=" << h.length << "\n";
  return true;
}
static bool read_riff_chunks(auto h, auto * r) {
  if (h.fourcc == 'TSIL') return read_list(h, r, read_list_chunks);
  std::cerr << "  " << fourcc_str(h.fourcc) << " - len=" << h.length << "\n";
  return true;
}
static bool read_riff(reader * r) {
  return read_chunk(r, [](header h, reader * r) {
    return (h.fourcc == 'FFIR') ? read_list(h, r, read_riff_chunks) : warn("File may not be RIFF\n");
  });
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
