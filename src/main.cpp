#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <variant>

#include <assert.h>

#include "combinator.h"
#include "data_input_output.h"

// Using this function it`s possible to check, that nuber of Letters is lower
// that some limit
size_t lengthOfOutput(const std::vector<LettersVector> &v) {
  size_t res = v[0].size();
  for (size_t i = 1; i < v.size(); ++i) {
    res *= v[i].size();
  }
  return res * v.size();
}

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
    std::cout << "Or use withot args to work with standart io" << std::endl;
    return 0;
  }

  std::vector<LettersVector> parsed_input;
  try {
    parsed_input = get_validated_input(*inp);
  } catch (std::domain_error &e) {
    *out << e.what() << std::endl;
    exit(0);
  } catch (std::exception &e) {
    *out << "Unknown problem: " << e.what() << std::endl;
    exit(1);
  } catch (...) {
    *out << "Unknown problem" << std::endl;
    exit(1);
  }

  auto solver = CombinationsGenerato();
  auto combinations = solver.combine(parsed_input);

  for (const auto &el : combinations) {
    if (el.pimpl->ind == Letter_impl::LONG)
      *out << std::get<0>(el.pimpl->data);
    else if (el.pimpl->ind == Letter_impl::CHAR)
      *out << std::get<1>(el.pimpl->data);
    else if (el.pimpl->ind == Letter_impl::STRING)
      *out << std::get<2>(el.pimpl->data);
  }

  assert(combinations.size() == lengthOfOutput(parsed_input));

  *out << std::endl;
  return 0;
}
