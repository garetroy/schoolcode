"""
Garett Roberts
CIS211
Project 7
"""
from string import punctuation

def codes(string):
	"""
	This function returns the ordered number for each character in a string
	"""
	return [ord(i) for i in string]

def vowels(string):
	"""
	This function takes a string and returns the characters that are vowles
	"""
	return ''.join([i for i in string if i.lower() in 'aeiou'])

def tokens(string):
	"""
	Removes punctuation from the string using strip_punctuation function
	"""
	return map(strip_punctuation, string.split())

def strip_punctuation(s):
	"""
	removes punctuation
	"""
	return s.strip(punctuation)

def numbers(string):
	"""
	This function returns the integers in string
	"""
	return [i for i in tokens(string) if i.isdigit()]

def sq_ft(txt_file):
	"""
	This takes a file with mesurments, runs the mesurments through numbers function to get the numbers
	then multiplies them together, then adds all of the areas in the list and returns the total
	sq ft
	"""
	return sum([int(numbers(line)[0])*int(numbers(line)[1]) for line in open(txt_file)])