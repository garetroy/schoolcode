"""
jumbler.py:  CIS 210 assignment 2, Fall 2013
author: Garett Roberts

Unscrable words
"""

import sys

dictionary = open(sys.argv[2])
jumbled_word = sorted(sys.argv[1])

def main(dictionary, jumbled_word):
    '''
    This function takes the dictionary and the jumbled word.
    For every word that it takes from the dictionary it sorts
    the word alphabetically and records the amount of words that
    it has gone through in the dictionary. Then it compares the
    sorted words from the dictionary and compares them to the sorted
    jumbled word. If it is correct it adds one to the matches counter
    then it prints the unsorted match from the dictionary. The '\n's
    appear in the dictionary words when you sort them in dict.txt so
    I added code in there to delete that indentation so I could compare
    the dictionary words and the jumbled word. Also it is removed so
    that the output matches the desired output stated for the assignment.
    '''

    matches = 0
    words_gone_through = 0
    for dic_word in dictionary:
        words_gone_through += 1
        dic_word_sorted = sorted(dic_word)
        if dic_word_sorted[0] == '\n':
            dic_word_sorted.remove('\n')
            if dic_word_sorted == jumbled_word:
                if list(dic_word)[-1] == '\n':
                    dic_word = list(dic_word)
                    dic_word.remove('\n')
                    dic_word = ''.join(dic_word)
                    print(dic_word)
                    matches += 1
    words_gone_through += 1
    if matches == 0:
        print('No matches')
    else:
        print(str(matches) + ' matches from ' + str(words_gone_through) + ' lines.')

main(dictionary, jumbled_word)
dictionary.close()			