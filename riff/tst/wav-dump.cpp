#include "m4c0/riff/fs_reader.hpp"
#include "m4c0/riff/parser.hpp"

#include <iostream>

using namespace m4c0::riff;

class wav_dumper {
public:
  bool dump_fmt(reader * r) { // NOLINT
    std::cout << "Found format\n";
    return true;
  }
  bool dump_data(reader * r) { // NOLINT
    std::cout << "Found data\n";
    return true;
  }
  bool extra(reader * r) { // NOLINT
    std::cout << "Ignoring extra chunk\n";
    return true;
  }
};

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

  riff_parser<wav_dumper> rp('EVAW');
  rp.emplace(' tmf', &wav_dumper::dump_fmt);
  rp.emplace('atad', &wav_dumper::dump_data);

  wav_dumper w;

  if (!rp.parse(&reader, &w)) {
    return EXIT_FAILURE;
  }

  std::cerr << "Parse succeeded\n";
  return EXIT_SUCCESS;
}
