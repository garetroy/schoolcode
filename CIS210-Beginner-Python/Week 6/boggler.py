"""
Boggle solver finds words on a boggle board. 
Authors:  Garett Roberts
Credits: N/A

Usage:  python3 boggler.py  "board" dict.txt
    where "board" is 16 characters of board, in left-to-right reading order
    and dict.txt can be any file containing a list of words in alphabetical order
    
"""

from boggle_board import BoggleBoard   
import argparse   # Command line processing
import game_dict  # Dictionary of legal game words

def main():
    """
    Main program: 
    Find all words of length 3 or greater on a boggle 
    board. 
    Args:
        none (but expect two arguments on command line)
    Returns: 
        Nothing (but prints found words in alphabetical
        order, without duplicates, one word per line)
    """
    dict_file, board_text = getargs()
    game_dict.read( dict_file )
    board = BoggleBoard(board_text)
    results = [ ] 
    total_score = 0
    for i in range(0,4):
        for j in range(0,4):
            find_words(board,i,j,'',results)
    results = deadu(results)
    for word in results:
        print(word + ' ' + str(score(word)))
        total_score += score(word)
    print("Total Score " + str(total_score))

def deadu(results):
    """
    Removes duplicates and sorts a list
    Args:
        reults: the list we are going to change
    Returns:
        none (but expect two arguments on command line)
    Effects:
        No duplicates and alphabetically arranged list
    """
    results = list(set(results))
    return sorted(results)

def getargs():
    """
    Get command line arguments.
    Args:
       none (but expects two arguments on program command line)
    Returns:
       pair (dictfile, text)
         where dictfile is a file containing dictionary words (the words boggler will look for)
         and   text is 16 characters of text that form a board
    Effects:
       also prints meaningful error messages when the command line does not have the right arguments
   """
    parser = argparse.ArgumentParser(description="Find boggle words")
    parser.add_argument('board', type=str, help="A 16 character string to represent 4 rows of 4 letters. Q represents QU.")
    parser.add_argument('dict', type=argparse.FileType('r'),
                        help="A text file containing dictionary words, one word per line.")
    args = parser.parse_args()  # will get arguments from command line and validate them
    text = args.board
    dictfile = args.dict
    if len(text) != 16 :
        print("Board text must be exactly 16 alphabetic characters")
        exit(1)
    return dictfile, text

def find_words(board, row, col, prefix, results):
    """Find all words starting with prefix that
    can be completed from row,col of board.
    Args:
        row:  row of position to continue from (need not be on board)
        col:  col of position to continue from (need not be on board)
        prefix: looking for words that start with this prefix
        results: list of words found so far
    Returns: nothing
        (side effect is filling results list)
    Effects:
        inserts found words (not necessarily unique) into results
    """
    if not board.available(row,col):
        return
    char = board.get_char(row,col)
    prefix += char
    if game_dict.search(prefix) == 1:
        board.mark_taken(row,col)
        results.append(prefix)
    elif game_dict.search(prefix) == 2:
        board.mark_taken(row,col)
    else:
        prefix = prefix[:len(prefix)-1]
        return
    find_words(board,row+1,col,prefix,results) #Down
    find_words(board,row-1,col,prefix,results) #Up
    find_words(board,row,col+1,prefix,results) #Right
    find_words(board,row,col-1,prefix,results) #Left
    find_words(board,row-1,col-1,prefix,results) #Up and Right
    find_words(board,row-1,col+1,prefix,results) #Up and Left
    find_words(board,row+1,col-1,prefix,results) #Down and Right
    find_words(board,row+1,col+1,prefix,results) #Down and Left
    board.unmark_taken(row,col)
    return
    
    
def score(word):
    """
    Compute the Boggle score for a word, based on the scoring table
    at http://en.wikipedia.org/wiki/Boggle. 
    Args:
        word: word is the word we are scoring
    Returns: the score of the word
     """
    if len(word) == 3 or len(word) == 4:
        return 1
    if len(word) == 5:
        return 2
    if len(word) == 6:
        return 3
    if len(word) == 7:
        return 5
    if len(word) >= 8:
        return 11
    return 0



####
# Run if invoked from command line
####

if __name__ == "__main__":
    main()
    input("Press enter to end")

