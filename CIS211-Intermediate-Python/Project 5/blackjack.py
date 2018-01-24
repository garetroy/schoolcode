"""
Garett Roberts
CIS211 Winter
blackjack.py
"""


from tkinter import *
from random import randint,shuffle
from CardLabel import *
from Deck import BlackjackDeck
from Card import BlackjackCard, total
from tkinter.messagebox import showinfo

root = Tk()

computer_hand = [] #The hand the computer will be playing with
person_hand = [] #The hand that the player will be playing with
deck = BlackjackDeck()
deck.shuffle()
deck_counter = 0 #So we know where we are in the deck

def deal():
	'''
	This function deletes the hands of both players, shuffles the deck, and
	restarts any of the other settings used then deals out two cards to each
	player using the hit function and enables the button hit and pass then
	disables the deal button
	'''
	global deck_counter
	del person_hand[:]
	del computer_hand[:]
	deck.shuffle()
	deck_counter = 0
	hit()
	hit()
	hit(computer_hand)
	hit(computer_hand)
	hit_btn['state'] = 'normal'
	pass_btn['state'] = 'normal'
	display_cards(computer_hand, True)
	display_cards(person_hand, True)
	deal_btn['state'] = 'disabled'

def hit(hand=person_hand):
	'''
	This function appends a card to the hand list (by default person hand)
	then increases the deck_counter to keep track of where we are in the deck
	then checks to see if the player is over 21, if so it calls the function
	lost
	'''
	global deck_counter
	hand.append(deck[deck_counter])
	deck_counter +=1
	display_cards(hand)
	if total(person_hand,True) > 21:
		lost(person_hand)


def end_turn():
	'''
	This invokes the dealers(computers) turn then compares then checks to see
	who the winner is then reports to the lost function
	'''
	while total(computer_hand) < 18 or total(computer_hand,True) < 18:
		hit(computer_hand)
	if ((total(computer_hand,True) > total(person_hand,True) or total(computer_hand) > total(person_hand)) and total(computer_hand,True) < 21) or total(computer_hand) == 21:
		lost(person_hand)
	elif total(computer_hand) == total(person_hand):
		lost('tie')
	else:
		lost(computer_hand)

def lost(hand):
	'''
	Displays which hand won and then disables the hit btn and the pass btn
	then enables the deal button and reveals the computers hand.
	'''
	if hand == computer_hand:
		showinfo("Game Over","You won!")
	elif hand == person_hand:
		showinfo("Game Over","You lost!")
	else:
		showinfo("Game Over","It was a tie!")
	hit_btn['state'] = 'disabled'
	pass_btn['state'] = 'disabled'
	deal_btn['state'] = 'active'
	display_cards(computer_hand,False,True)

def key(event):
	'''
	These are for keystroak commands
	'''
	if event.char == 'd':
		deal()
	if event.char == 'h':
		hit()
	if event.char == 'p':
		end_turn()
	if event.char == '\x11':
		root.quit()

def display_cards(hand,restart=False,show_hand=False):
	'''
	This creates the labels for each user and makes the first card of the comp
	uters  hand visible if show hand is true. If restart is true then all
	lables are reset.
	'''
	for i in range(len(hand)):
		a = CardLabel(root)
		if i == 0 and hand == computer_hand and not show_hand:
			a.display('back',hand[i].n)
		else:
			a.display('front',hand[i].n)
		if hand == computer_hand:
			a.grid(row=0,column=i+1)
		else:
			a.grid(row=1,column=i+1)
	if restart == True:
		for i in range(len(hand),6):
			a = CardLabel(root)
			a.display(1)
			if hand == computer_hand:
				a.grid(row=0,column=i+1)
			else:
				a.grid(row=1,column=i+1)




CardLabel.load_images()
root.bind("<Key>", key) #Key events
deck_lbl = CardLabel(root)
deck_lbl.grid(row=0,column=0)
deck_lbl.display('back',0)
deal_btn = Button(root,text="Deal",command=deal)
hit_btn = Button(root,text="Hit",command=hit)
hit_btn['state'] = 'disabled'
pass_btn = Button(root,text="Pass",command=end_turn)
pass_btn['state'] = 'disabled'
deal_btn.grid(row=3,column=1)
hit_btn.grid(row=3, column=2)
pass_btn.grid(row=3,column=3)

if __name__ == '__main__':
	root.mainloop()
