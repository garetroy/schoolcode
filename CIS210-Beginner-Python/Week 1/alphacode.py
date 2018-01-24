"""
alphacode.py:  CIS 210 assignment 1, Fall 2013
author: Garett Roberts

Convert 4-digit PIN to alphabetic code
"""

## Constants used by this program
CONSONANTS = "bcdfghjklmnpqrstvwyz" 
VOWELS = "aeiou"  

## Get pin code from command line
import sys
if (len(sys.argv) > 1) :
    pincode = int(sys.argv[1])
else :
    print("Usage: python3 alphacode 9999")
    exit(1)  ## Quit the program right here, indicating a problem


def start(origial_pincode):
	'''
	Splits the pincode, then gives it off to the encoding method to 
	obtain the first and the last half of the encoded string
	then prints off the string
	'''

	first_half = origial_pincode[0:2]
	second_half = origial_pincode[2:4]
	first_letters = encoding(int(first_half))
	second_letters = encoding(int(second_half))
	encoded = first_letters + second_letters
	print('Encoding of ' + origial_pincode + ' is ' + encoded)

def encoding(two_numbers):
	'''
	Encodes the string by the method described and pulling the
	letters it gets from the CONSONANTS and VOWELS lists
	'''
	return CONSONANTS[two_numbers // 5] + VOWELS[two_numbers % 5]

start(str(pincode))