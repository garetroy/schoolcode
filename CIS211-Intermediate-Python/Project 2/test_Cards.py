# Unit tests for Card and Deck classes
#
# John Conery
# CIS 211
# Winter 2015
#

import unittest

from Card import *

class CardTest(unittest.TestCase):

	def test_01_cards(self):
		"make some cards, check values returned by accessor methods"
		two_of_clubs = Card(0)
		self.assertEqual(0, two_of_clubs.rank(), "expected rank to be 0")
		self.assertEqual(0, two_of_clubs.suit(), "expected suit to be 0")
		ace_of_spades = Card(51)
		self.assertEqual(12, ace_of_spades.rank(), "expected rank to be 12")
		self.assertEqual(3, ace_of_spades.suit(), "expected suit to be 3")
		
		"check representations"
		self.assertEqual('2\u2663', repr(two_of_clubs), "expected representation to be 2\u2663")
		self.assertEqual('A\u2660', repr(ace_of_spades), "expected representation to be A\u2660")
		
		"check comparisons"
		self.assertTrue(two_of_clubs < ace_of_spades, "ordering failed")
		self.assertFalse(two_of_clubs == ace_of_spades, "comparison failed")
		
	def test_02_points(self):
		cards = [Card(i) for i in range(13)]
		points = [0] * 9 + list(range(1,5))
		self.assertEqual(points, [x.points() for x in cards], "points incorrect")
	
	def test_03_blackjack_cards(self):
		cards = [BlackjackCard(i) for i in range(13)]
		self.assertEqual(0, cards[0].rank(), "expected blackjack rank to be 0")
		self.assertEqual(0, cards[0].suit(), "expected blackjack suit to be 0")
		points = [i+2 for i in range(9)] + [10,10,10,11]
		self.assertEqual(points, [x.points() for x in cards], "blackjack points incorrect")
		
	def test_04_deck(self):
		d = [ Card(i) for i in range(52) ]
		self.assertEqual(52, len(d), "deck doesn't have 52 cards")
		suits = dict.fromkeys(range(4),0)
		ranks = dict.fromkeys(range(13),0)
		for x in d:
			suits[x.suit()] += 1
			ranks[x.rank()] += 1
		self.assertEqual(list(suits.values()), [13]*4, "didn't find 13 cards in each suit")
		self.assertEqual(list(ranks.values()), [4]*13, "didn't find 4 of each kind of card")
				
	def test_05_points(self):
		h = [Card(i) for i in range(13)]
		self.assertEqual(10, total(h), "expected cards to have 10 points")
		bh = [BlackjackCard(i) for i in range(13)]
		self.assertEqual(95, total(bh), "expected blakcjack cards to have 95 points")
