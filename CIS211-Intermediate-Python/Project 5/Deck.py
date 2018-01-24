from random import shuffle
from Card import *
	


class Deck(list):
	"""
	Creates a new deck and assigns functions to the deck
	"""


	def __init__(self):
		"""
		Initializes the class and creates a deck, Returns nothing
		"""
		for i in range(52):
			self.append(Card(i)) #places the cards in self
		return

	def shuffle(self):
		"""
		Shuffles the cards in the cards list
		"""
		return shuffle(self)

	def deal(self, x):
		"""
		Returns the dealed hands and removes of the cards delt in the deck
		"""
		return [self.pop(0) for i in range(x)]
		
	def restore(self, l):
		"""
		It appends the cards to the deck that are in l
		"""
		for i in l:
			self.append(i)

class PinochleDeck(Deck):
	"""
	Creates a PinochleDeck and inherits the Deck class to utilize its functions
	"""

	def __init__(self):
		"""
		Initializes this class and creates a PinochleDeck
		"""
		for i in range(52): #goes through all cards
			if Card(i).rank() < 7: #if the rank is not 9 it passes
				pass
			else:
				self.extend((Card(i),Card(i))) # addeds the 9 or greater card twice to deck
		self.sort() #sorts the deck
		return

class BlackjackDeck(Deck):
	def __init__(self):
		"""
		Initializes the class and creates a deck, Returns nothing
		"""
		for i in range(52):
			self.append(BlackjackCard(i)) #places the cards in self
		return


if __name__ == '__main__':
	k = Deck()
	print(k)
	print(str(len(k)) + " This is the length of the deck")
	k.shuffle()
	print('\n')
	print(str(k) + " Shuffled")
	print('\n')
	w = k.deal(5)
	print(str(w) + " This is the delt cards")
	print('\n')
	k.restore(w)
	print(str(k) + " This is the restored cards that were delt")
	k = PinochleDeck()
	print('\n')
	print(str(k) + " This is a PinochleDeck")
	print(str(len(k)) + " This is the length of PinochleDeck")
	k.shuffle()
	print('\n')
	print(str(k) + " Shuffled PinochleDeck")
	print('\n')
	w = k.deal(5)
	print(str(w) + " This is the delt cards for PinochleDeck")
	print('\n')
	k.restore(w)
	print(str(k) + " This is the restored cards that were delt for PinochleDeck")