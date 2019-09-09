#include "letter.h"

Letter createLetter(std::string_view s) {
  using namespace letter_helpes;
  auto p = std::make_shared<Letter_impl>();

  if (is_digit(s)) {
    long digit = std::atol(s.data());
    p->data = digit;
    p->ind = Letter_impl::LONG;
    return Letter(p);
  } else if (is_char(s)) {
    char ch = s[0];
    p->data = ch;
    p->ind = Letter_impl::CHAR;
    return Letter(p);
  }

  p->data = s.data();
  p->ind = Letter_impl::STRING;
  return Letter(p);
}

Letter nextLetter(const Letter &letter) {
  auto next_letter_impl = nextLetter_impl(letter.pimpl);
  Letter res(next_letter_impl);
  return res;
}

Letter::implPointer_t nextLetter_impl(const Letter::implPointer_t p) {
  using namespace letter_helpes;
  auto res = std::make_shared<Letter_impl>();
  res->ind = p->ind;

  if (Letter_impl::LONG == p->ind) {
    res->data = std::get<Letter_impl::LONG>(p->data) + 1;
  } else if (Letter_impl::CHAR == p->ind) {
    res->data = incr_char(std::get<Letter_impl::CHAR>(p->data));
  } else {
    res->data = incr_string(std::get<Letter_impl::STRING>(p->data));
  }

  return res;
}
