#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H
#include <fstream>
#include <utility>

#include "letter.h"

std::vector<LettersVector> get_validated_input(std::istream &);
bool is_valid(Letter first, Letter last, const LettersVector &letters_vec);
#endif  // PARSE_INPUT_H
