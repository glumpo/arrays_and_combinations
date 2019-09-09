#include <iostream>
#include <variant>

#include "combinator.h"
#include "data_input_output.h"

int main() {
  auto parsed_input = get_validated_input(std::cin);
  auto combinations = combine(parsed_input);
  for (auto el : combinations) {
    std::cout << std::get<0>(el.pimpl->data) << " ";
  }
  std::cout << std::endl;

  return 0;
}
