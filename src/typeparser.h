#ifndef TYPEPARSER_H
#define TYPEPARSER_H

#include <string>
#include <variant>

namespace type_parser {
// TODO: tryParse functions and parsing with giving type

enum {
  FAIL,
  INT,
  CHAR,
  STRING,
};

using parsedVariant = std::variant<unsigned long, char, std::string>;
using typeIndex = int;
using variantAndType = std::pair<parsedVariant, typeIndex>;

variantAndType parseLetter(const std::string &s);

}  // namespace type_parser

#endif  // TYPEPARSER_H
