#ifndef LETTER_H
#define LETTER_H

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "letter_helpers.h"

struct Letter_impl {
  enum { LONG, CHAR, STRING };
  std::variant<long, char, std::string> data;
  int ind;
};

class Letter {
  // DEGUB
  // private:
 public:
  using implPointer_t = std::shared_ptr<Letter_impl>;
  implPointer_t pimpl;

 public:
  Letter(Letter_impl *p) { pimpl.reset(p); }
  Letter(implPointer_t p) { pimpl = p; }

  Letter &operator=(const Letter &other) {
    this->pimpl = other.pimpl;
    return *this;
  }

  Letter &operator=(Letter &&other) {
    this->pimpl = std::move(other.pimpl);
    return *this;
  }

  Letter(const Letter &other) { this->pimpl = other.pimpl; }

  Letter(Letter &&other) { this->pimpl = std::move(other.pimpl); }

  ~Letter() = default;

 public:
  bool operator<(const Letter &other) const {
    return this->pimpl->data < other.pimpl->data;
  }

  bool operator<=(const Letter &other) const {
    return this->pimpl->data <= other.pimpl->data;
  }
};

using LettersVector = std::vector<Letter>;

Letter createLetter(std::string_view);
Letter::implPointer_t nextLetter_impl(const Letter::implPointer_t p);
Letter nextLetter(const Letter &letter);

#endif  // LETTER_H
