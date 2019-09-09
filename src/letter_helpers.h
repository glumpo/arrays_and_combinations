#ifndef LETTER_HELPERS_H
#define LETTER_HELPERS_H

#include <string>

namespace letter_helpes {

bool is_digit(std::string_view s);
bool is_char(std::string_view s);

std::string incr_string(std::string s);
char incr_char(char ch);

}  // namespace letter_helpes

#endif  // LETTER_HELPERS_H
