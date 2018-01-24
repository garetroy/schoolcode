import argparse

"""

Pig Latin is a language game, where you move the first letter of the word to 
the end and add "ay." So "Python" becomes "ythonpay." To write a Pig Latin translator in Python, 
here are the steps we'll need to take:

	Ask the user to input a phrase in English.
	Make sure the user entered a valid phrase.
	Separate the phrase to a list of words and then convert each word from English to Pig Latin. 
	This results in a new list of Pig Lating words. 
	Finally, join all the words in the Pig Latin list to make a new Pig Latin Phrase.
	Display the translation result.

	e.g. python -> ythonpay

"""

"""
1.Let's create a variable to hold our translation suffix.

2.ensure that the user actually typed something
   if len(empty_string) > 0:
	   Run this block.
	   Maybe print something?
   else:
		That string must have been empty.

3.We can check that the user's string actually has characters!
   Let's make sure the word the user enters contains only alphabetical 
   characters. You can use isalpha() to check this!

   e.g.   x = "J123"
		  x.isalpha()  # False

	If the word does contain non-alpha characters, then don't translate the word.

4.You move the first letter of the word to the end and then append the suffix 'ay'.

	Example: python -> ythonpay

5. Make sure to use two different functions:

	* pigLatinWord() - returns a word in its Pig Latin format.
	* pigLatinPhrase() - replaces words in a word list with the Pig Latin format
	  "python is good" -> ythonpay siay oodgay

6. Need more ...

	write a reverse translator called igLatinWordpay.py which takes a pig latin phrase and
	translates it back into english.
"""

"""
	Translates a word into pig latin
"""
def pigLatinWord(word):
	if word.isalpha():
		word = word[1:] + word[0] + 'ay'
		return word
	else:
		return word

"""
	Replaces each word in wordList translated into pig latin
"""
def pigLatinPhrase(wordList):
	for i in range(len(wordList)):
		wordList[i] = pigLatinWord(wordList[i])
	return wordList

if __name__ == "__main__":

	parser = argparse.ArgumentParser(description="pigLatin")
	parser.add_argument("phrase", type=str, help="Enter a word: python")
	args = parser.parse_args()
	
	wordList = args.phrase.split()
	if len(wordList) > 0:
		pigLatinPhrase(wordList)
	else:
		print("Try a list of words")
	print(" ".join(wordList))

   
