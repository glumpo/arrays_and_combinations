#include <fstream>
#include <iostream>
#include <istream>
#include <variant>

#include "combinator.h"
#include "data_input_output.h"

int main(int argc, char *argv[]) {
  std::istream *inp;
  std::ostream *out;
  std::ifstream ifs;
  std::ofstream ofs;

  if (1 == argc) {
    inp = &std::cin;
    out = &std::cout;
  } else if (3 == argc) {
    try {
      ifs.open(argv[1]);
      ofs.open(argv[2]);
    } catch (const std::ifstream::failure &e) {
      std::cout << "Error opening file " << argv[1] << std::endl;
      std::cout << e.what() << std::endl;
    } catch (const std::ofstream::failure &e) {
      std::cout << "Error opening file " << argv[2] << std::endl;
      std::cout << e.what() << std::endl;
    }
    inp = &ifs;
    out = &ofs;
  } else {
    std::cout << "Usage:" << std::endl << argv[0] << " input_file output_file";
    std::cout << std::endl;
    std::cout << "Or use withou args to work with standart io" << std::endl;
    return 0;
  }

  auto parsed_input = get_validated_input(*inp);
  auto combinations = combine(parsed_input);
  for (auto el : combinations) {
    *out << std::get<0>(el.pimpl->data);
  }
  *out << std::endl;

  return 0;
}
