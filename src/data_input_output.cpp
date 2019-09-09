#include <cctype>
#include <exception>
#include <set>
#include <utility>
#include <variant>

#include <iostream>

#include "data_input_output.h"

/*
 * Splits string to Letter with givven delimmiter (defaults to " ")
 * return vector of Letters
 */
LettersVector string_to_vec(std::string_view s, std::string_view delim = " ") {
  LettersVector v;
  if (s.empty()) {
    return v;
  }
  size_t start = 0U;
  size_t end = s.find(delim);
  while (end != std::string::npos) {
    std::string sub(s.substr(start, end - start));
    v.push_back(createLetter(sub));
    start = end + delim.length();
    end = s.find(delim, start);
  }
  std::string sub(s.substr(start, end - start));
  v.push_back(createLetter(sub));

  return v;
}

/*
 * DOESNT SKIP \n!!!
 * Skip all spaces and \t
 * return first valid char
 */
int first_non_space(std::istream &inp) {
  int ch;
  do {
    ch = inp.get();
  } while (ch == ' ' || ch == '\t');
  return ch;
}

/*
 * Reads input from istream and cheks, if input valid.
 * Throws: std::domain_error, std::bad_aloc from vector
 */
std::vector<LettersVector> get_validated_input(std::istream &inp) {
  std::vector<LettersVector> res;
  while (!inp.eof()) {
    int ch = first_non_space(inp);
    if ('\n' == ch) {
      break;
    }
    if ('[' != ch) {
      throw std::domain_error("Incorect input");
    }
    ch = first_non_space(inp);
    inp.putback(char(ch));
    std::string alphabet;
    std::getline(inp, alphabet, ']');

    ch = first_non_space(inp);
    if ('{' != ch) {
      throw std::domain_error("Incorect input");
    }
    std::string letters;
    std::getline(inp, letters, '}');
    if (letters.empty()) {
      throw std::domain_error("Validation Error: [" + alphabet + "] {" +
                              letters + "}");
    }

    // transforms "a-b" to [a, b]
    auto alphabet_vec = string_to_vec(alphabet, "-");
    auto letters_vec = string_to_vec(letters);

    if (alphabet_vec.size() != 2) {
      // if alphabet not in form of "a-b:
      throw std::domain_error("Incorect input");
    }

    if (!is_valid(alphabet_vec[0], alphabet_vec[1], letters_vec)) {
      throw std::domain_error("Validation Error: [" + alphabet + "] {" +
                              letters + "}");
    }
    res.push_back(std::move(letters_vec));

    if (inp.get() != '\n') {
      throw std::domain_error("Incorect input");
    }
  }

  return res;
}

/*
 * Checks, if LettersVector are valid for given first and last letters of
 * alphabet. Generetes alphabet ti the set and checks, if every letter in
 * LetterVector is in alphabet set
 */
bool is_valid(Letter first, Letter last, const LettersVector &letters_vec) {
  std::set<Letter> alphabet;
  for (auto i = first; i <= last; i = nextLetter(i)) {
    alphabet.insert(i);
  }

  for (const auto &el : letters_vec) {
    if (alphabet.find(el) == alphabet.end()) {
      return false;
    }
  }

  return true;
}
