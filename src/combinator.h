#ifndef COMBINATOR_H
#define COMBINATOR_H

#include <string>
#include <vector>

#include "letter.h"

static LettersVector _res;

std::vector<LettersVector::iterator> starts;
std::vector<LettersVector::iterator> curs;
std::vector<LettersVector::iterator> ends;

bool combine_impl(std::vector<LettersVector::iterator>::iterator st,
                  std::vector<LettersVector::iterator>::iterator cur,
                  std::vector<LettersVector::iterator>::iterator ed,
                  std::vector<LettersVector::iterator>::iterator stop) {
  if (st == stop) {
    return true;
  }

  _res.push_back(**cur);
  if (combine_impl(st + 1, cur + 1, ed + 1, stop)) {
    ++(*cur);
    if (*cur == *ed) {
      *cur = *st;
      return true;
    }
  }

  return false;
}

LettersVector combine(std::vector<LettersVector>& v) {
  for (auto& el : v) {
    starts.push_back(el.begin());
    curs.push_back(el.begin());
    ends.push_back(el.end());
  }

  size_t i = 0;
  while (i < (v[0].size() - 1)) {
    if (combine_impl(starts.begin() + i, curs.begin() + i, ends.begin() + i,
                     starts.end())) {
      ++i;
    }
  }
  return _res;
}

#endif  // COMBINATOR_H
