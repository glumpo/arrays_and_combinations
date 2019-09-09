#ifndef COMBINATOR_H
#define COMBINATOR_H

#include <exception>
#include <string>
#include <vector>

#include "letter.h"

class CombinationsGenerato {
 private:
  LettersVector res_;

  std::vector<LettersVector::iterator> starts_;
  std::vector<LettersVector::iterator> curs_;
  std::vector<LettersVector::iterator> ends_;

  bool failed = false;

 private:
  bool combine_impl(std::vector<LettersVector::iterator>::iterator st,
                    std::vector<LettersVector::iterator>::iterator cur,
                    std::vector<LettersVector::iterator>::iterator ed,
                    std::vector<LettersVector::iterator>::iterator stop) {
    if (st == stop) {
      return true;
    }

    try {
      res_.push_back(**cur);
    } catch (std::bad_alloc&) {
      st = cur = ed = stop;
      failed = true;
      return false;
    }

    if (combine_impl(st + 1, cur + 1, ed + 1, stop)) {
      if (true == failed) {
        return false;
      }

      ++(*cur);
      if (*cur == *ed) {
        *cur = *st;
        return true;
      }
    }

    return false;
  }

 public:
  /*
   * Function combine preperases internal class state and calls combine_impl
   * for every element of the top multitude. combine_impl goes through all
   * multitudes, pushing curent letters to the _res. To determine current letter
   * in every multitude, combine_impl keeps iterator cur. The auxiliary
   * iterators st, ed and stop are needed to reset cur, check if cur == end,
   * check, if bottom multitude was reached. Curent letter changes on next (or
   * on first) if combine_impl returned true.
   *
   * If genereted sequence too big and push_back thows bad_aloc, failed flag
   * sets to true and function returns alredy genereted part of sequence.
   *
   */
  LettersVector combine(std::vector<LettersVector>& v) {
    for (auto& el : v) {
      if (el.size() == 0) {
        continue;
      }
      starts_.push_back(el.begin());
      curs_.push_back(el.begin());
      ends_.push_back(el.end());
    }

    long i = 0;
    while (size_t(i) < (v[0].size() - 1)) {
      if (true == failed) {
        break;
      }
      if (starts_.begin() + i == starts_.end()) {
        break;
      }
      if (combine_impl(starts_.begin() + i, curs_.begin() + i,
                       ends_.begin() + i, starts_.end())) {
        ++i;
      }
    }
    return res_;
  }

  bool is_failed() { return failed; }
};

#endif  // COMBINATOR_H
