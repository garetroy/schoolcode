import argparse

"""
    shoutLetters1 - prints all characters within a phrase separated by
    by a space

    e.g. "Go Ducks!" -> "G O  D U C K S !"
"""

def shoutLetters1(phrase):

    phrase = phrase.upper() # really shout out loud

    print(phrase)

"""
    shoutLetters2 - prints all characters within words of a phrase
    separated by a hypen. Whitespace and punctuation are not printed
    with a hypen separator.

    e.g. "Go Ducks!" -> "G-O D-U-C-K-S!"
"""

def shoutLetters2(phrase):

    phrase = phrase.upper() # really shout out loud

    for i in phrase:
        if phrase[(len(phrase)-1)] == i:
            print(i)
        else:
            print(i+'-', end='')

    

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Shout Letters")
    parser.add_argument("phrase", type=str, help="Enter a phrase to shout")
    args = parser.parse_args()

    shoutLetters1(args.phrase)
    shoutLetters2(args.phrase)
