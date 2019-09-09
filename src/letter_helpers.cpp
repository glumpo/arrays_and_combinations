#include "letter_helpers.h"

bool letter_helpes::is_digit(std::string_view s) {
  return s.find_first_not_of("0123456789") == std::string_view::npos;
}

bool letter_helpes::is_char(std::string_view s) { return s.size() == 1; }

std::string letter_helpes::incr_string(std::string s) {
  for (auto it = s.rbegin(); it != s.rend(); ++it) {
    if (*it == 'z') {
      *it = 'a';
    } else {
      *it += 1;
      break;
    }
  }
  return s;
}

char letter_helpes::incr_char(char ch) {
  if ('z' == ch) {
    return 'a';
  } else {
    return ch + 1;
  }
}
