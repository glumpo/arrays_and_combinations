#include "letter_helpers.h"

bool letter_helpes::is_digit(std::string_view s) {
  return s.find_first_not_of("0123456789") == std::string_view::npos;
}
