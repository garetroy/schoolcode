"""
Garett Roberts
CIS 211
rescraper.py

"""
from urllib.request import urlopen
import re
from sys import argv

def rescraper(url):
	"""
	Opens a url(ncaa_url) which is a website which contains multiple basketball games as response, it decodes and returnes what the final score was
	for each team
	"""
	response = urlopen(url)
	played_games = response.read().decode()
	for line in played_games.split('\n'):
		if '<table class="linescore' in line:
			text = line
			scores = re.findall(r'<td class="final score">(\d+)</td>',text)
			teams = re.findall(r'<a.*?>(.*?)</a>', text)
			print('{} {}, {} {}'.format(teams[0],scores[0],teams[1],scores[1]))

if __name__ == '__main__':
	rescraper(argv[1])
