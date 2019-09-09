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
        return "[] {}" + '\n' + "[] {}"

    def answer_empty_arrays(self):
        return ""

    def test_empty_alphabet(self):
        return "[] {0 0}"

    def answer_empty_alphabet(self):
        return "Validation Error [] {0 0}"

    def test_incorrect_input(self):
        return "lol, I am a test case"

    def answer_incorrect_input(self):
        return "Parsing Error"

    def test_two_letters(self):
        return "[a-b] {a b}"

    def test_one_correct(self):
        return "abba"

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
            output.write(gen_test() + "\n")

        answer_output_filename = "tests/{}.a".format(method_name_base)
        with open(answer_output_filename, "w") as output:
            output.write(gen_answer() + "\n")



