"""
Garett Roberts
CIS211
Winter 2015

This project is utilizing classes by creating a Card class and defininig and representing a Card along
with assigining a point system to the cards
"""

class Card:
	"""
	Creates a card's rank, suit, and point value and represents the card with the suit and rank
	"""


	sym = {0: '\u2663', 1: '\u2666', 2:'\u2665', 3:'\u2660'} 
	point_sysm = {12:4, 11:3, 10:2, 9:1}
	rank_sym = [2,3,4,5,6,7,8,9,10,'J', 'Q', 'K', 'A']


	def __init__(self, n):
		"""
		Initializes the class with n and raises error if id is too big
		"""
		if n >= 52:
			raise Exception("This card does not exist")
		self.n = n

	def __repr__(self):
		"""
		Returns a card according to it's rank and symbol by comparing the suit
		to sym and rank to rank_sym
		"""
		return (str(self.rank_sym[self.rank()]) + self.sym[self.suit()])

	def __lt__(self,other):
		"""
		Returns the comparison of which is greater based on id unless switched to sort
		by rank
		"""
		return self.n < other.n

	
	def rank(self):
		"""
		Finds the rank of the card and returns rank
		"""
		rank = self.n % 13
		return rank
	
	def suit(self):
		"""
		Finds the suit of the card and returns suit
		"""
		suit = self.n // 13
		return suit

	def points(self):
		"""
		Returns the point value of the card based on the point_sysm
		"""
		if self.rank() >= 9:
			return self.point_sysm[self.rank()]
		else:
			return 0
	

	
class BlackjackCard(Card):
	"""
	Defines a new __lt__ for the ranks to be compared and creates a new point
	system for blackjack cards
	"""


	point_sysm = {12:11, 11:10, 10:10, 9:10}

	def __lt__(self,other):
		"""
		Returns True if the self rank is higher than the other rank
		"""
		return self.rank() < other.rank()

	def points(self):
		"""
		Returns the point value for the card based on Blackjack scoring rules
		"""
		if self.rank() in self.point_sysm:
			return self.point_sysm[self.rank()]
		else:
			return (self.rank() + 2)
	
	
def total(h):
	"""
	Finds the total points that the hand h has and returns that value
	"""
	return sum(i.points() for i in h)

def new_deck(cla):
	"""
	Returns a deck full of a cards that are defined by the cla class
	"""
	return [cla(i) for i in range(52)]