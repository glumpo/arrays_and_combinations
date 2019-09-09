#ifndef COMBINATOR_H
#define COMBINATOR_H

#include <exception>
#include <string>
#include <vector>

#include "letter.h"

class CombinationsGenerato {
 private:
  LettersVector _res;

  std::vector<LettersVector::iterator> starts;
  std::vector<LettersVector::iterator> curs;
  std::vector<LettersVector::iterator> ends;

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
      _res.push_back(**cur);
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
  LettersVector combine(std::vector<LettersVector>& v) {
    for (auto& el : v) {
      starts.push_back(el.begin());
      curs.push_back(el.begin());
      ends.push_back(el.end());
    }

    size_t i = 0;
    while (i < (v[0].size() - 1)) {
      if (true == failed) {
        break;
      }
      if (combine_impl(starts.begin() + i, curs.begin() + i, ends.begin() + i,
                       starts.end())) {
        ++i;
      }
      if (starts.begin() + i == starts.end()) {
        break;
      }
    }
    return _res;
  }
};

#endif  // COMBINATOR_H
