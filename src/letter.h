#ifndef LETTER_H
#define LETTER_H

#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "letter_helpers.h"

struct Letter_impl {
  enum { LONG, CHAR, STRING };
  using data_t = std::variant<long, char, std::string>;
  data_t data;
  int ind;
};

/*
 * Class Letter implemments pimpl idiom, so when storring a number of same
 * letters you will store only pointers on them. May be it has  sence to go
 * deeper and create complet Flyweight pattern with permanent centralized store
 *
 * It is better to pass Letter by value than by reference
 * becouz of size (long * 2) and other things
 */
class Letter {
 public:
  // May be its better to make pointer private
  using implPointer_t = std::shared_ptr<Letter_impl>;
  implPointer_t pimpl;

 public:
  Letter(Letter_impl *p) noexcept { pimpl.reset(p); }
  Letter(implPointer_t p) noexcept { pimpl = std::move(p); }

  Letter &operator=(const Letter &other) noexcept = default;
  Letter &operator=(Letter &&other) noexcept = default;

  Letter(const Letter &other) noexcept = default;
  Letter(Letter &&other) noexcept = default;

  ~Letter() = default;

 public:
  bool operator<(const Letter &other) const noexcept {
    return this->pimpl->data < other.pimpl->data;
  }

  bool operator<=(const Letter &other) const noexcept {
    return this->pimpl->data <= other.pimpl->data;
  }
};

using LettersVector = std::vector<Letter>;

Letter createLetter(std::string_view);
Letter::implPointer_t nextLetter_impl(const Letter::implPointer_t p);
Letter nextLetter(const Letter &letter);

#endif  // LETTER_H
