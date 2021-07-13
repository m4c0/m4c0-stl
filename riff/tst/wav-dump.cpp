#include "m4c0/io/istr_reader.hpp"
#include "m4c0/riff/parser.hpp"

#include <fstream>
#include <iostream>

using namespace m4c0::riff;

class wav_dumper {
public:
  bool dump_fmt(m4c0::io::reader * r) { // NOLINT
    std::cout << "Found format\n";
    return true;
  }
  bool dump_data(m4c0::io::reader * r) { // NOLINT
    std::cout << "Found data\n";
    return true;
  }
  bool extra(m4c0::io::reader * r) { // NOLINT
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

  m4c0::io::istr_reader reader { in };

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
