# Unit tests for functions in Project 7
#
# CIS 211
# Winter 2015
#

import unittest

from fp import *

class FPTest(unittest.TestCase):
    
    def test_01_codes(self):
        c = codes('Hello')
        self.assertEqual(c, [72, 101, 108, 108, 111], "expected codes('Hello') to be [72, 101, 108, 108, 111]")

    def test_02_vowels(self):
        s = vowels('Hello, world')
        self.assertEqual(s, 'eoo', "expected vowels('Hello, world') to be 'eoo'")

    def test_03_tokens(self):
        m = tokens('Veni, vidi, vici')
        self.assertEqual(list(m), ['Veni', 'vidi', 'vici'], "expected list(tokens('Veni, vidi, vici')) to be ['Veni', 'vidi', 'vici']")

    def test_04_numbers(self):
        self.assertEqual(numbers("1, 2, 3 o'clock rock"), ['1','2','3'], "expected numbers(\"1, 2, 3 o'clock rock\") to be ['1','2','3']")
