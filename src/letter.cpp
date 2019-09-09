#include "letter.h"

Letter createLetter(std::string_view s) {
  using namespace letter_helpes;
  auto p = std::make_shared<Letter_impl>();

  if (is_digit(s)) {
    long digit = std::atol(s.data());
    p->data = digit;
    p->ind = Letter_impl::LONG;
    return Letter(p);
  } else {
    // TODO: impliment other cases
    throw "TODO";
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
  auto res = std::make_shared<Letter_impl>();
  res->ind = p->ind;

  if (Letter_impl::LONG == p->ind) {
    res->data = std::get<Letter_impl::LONG>(p->data) + 1;
  } else {
    // TODO: impliment
    throw "IMPLIMENT";
  }

  return res;
}
