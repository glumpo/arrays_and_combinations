#include "typeparser.h"

type_parser::variantAndType type_parser::parseLetter(const std::string &s) {
  variantAndType res;
  bool guesed = false;
  for (auto ch : s) {
    if (std::isdigit(ch)) {
      guesed = true;
    } else {
      guesed = false;
      break;
    }
  }

  if (true == guesed) {
    res.first = std::stoul(s);
    res.second = INT;
    return res;
  }

  res.first = 0ul;
  res.second = FAIL;
  return res;
}
