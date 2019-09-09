#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
import string
import sys

class Tests:
    def test_empty_file(self):
        return ""

    def answer_empty_file(self):
        return ""

    def test_empty_arrays(self):
        return "[0-0] {}" + '\n' + "[0-0] {}"

    def answer_empty_arrays(self):
        return ""

    def test_empty_alphabet(self):
        return "[1-1] {0 0}"

    def answer_empty_alphabet(self):
        return "Validation Error [1-1] {0 0}"

    def test_incorrect_input(self):
        return "lol, I am a test case"

    def answer_incorrect_input(self):
        return "Incorect input"

    def test_two_letters(self):
        return "[a-b] {a b}"

    def answer_two_letters(self):
        return "ab"

    def test_two_ints(self):
        return "[1-2] {1 2}"

    def answer_two_ints(self):
        return "12"

def test_to_answer(test):
    return "answer" + test[len("test"):]

if __name__ == "__main__":
    tests = Tests()
    method_list = [func for func in dir(tests) if callable(getattr(tests, func)) and func.startswith("test_")]
    
    for test_method_name in method_list:
        method_name_base = test_method_name[len("test_"):]

        gen_test = getattr(tests, test_method_name)
        gen_answer = getattr(tests, test_to_answer(test_method_name))

        test_output_filename = "tests/{}.t".format(method_name_base)
        with open(test_output_filename, "w") as output:
            output.write(gen_test() + "\n" + '\n')

        answer_output_filename = "tests/{}.a".format(method_name_base)
        with open(answer_output_filename, "w") as output:
            output.write(gen_answer() + "\n")



