"""
Garett Roberts
CIS 211
scrapper.py
"""

from urllib.request import urlopen
from sys import argv
from html.parser import HTMLParser


class Printer(HTMLParser):
    """
    Object that is looking for two different teams and returns the final score, a subclass of HTMLParser
 
    """
    def __init__(self):
        HTMLParser.__init__(self)
        self._wanted = False
        self._current_game = None
        self._games=[]

    def handle_starttag(self, tag, attrs):
        """
        sets wanted to true if it is a finished game
        """

        if tag == 'table' and attrs == [('class', 'linescore')]:
            self._current_game = []

        if tag == 'td' and attrs == [('class','final score')] and self._current_game != None:
            self._current_game= True 

        elif tag == 'a' and '/schools/' in attrs[0][1] and self._current_game != None:
            self._wanted = True
        
    def handle_data(self, text):
        """
        if he wanted is true, then this will handle the data within the tag
        """

        if self._current_game != None and self._grab_this:
            self._current_game.append(text.strip())
            self._wanted = False

    def handle_endtag(self, tag):
        """
        This shows how to handle the tag
        """

        if tag == 'table' and self._current_game != None:
            self._games.append(self._current_game)
            self._current_game=None


def scraper(url):
    """
    This is where it will print the teams and final score
    """
    
    games = Printer()
    games.feed(urlopen(ncaa_url).read().decode())
    for game in games._games:
        print('{} {}, {} {}'.format(game[0],game[1],game[2],game[3]))
        

if __name__ == '__main__':
	scraper(argv[1])