"""
Garett Roberts
CIS211 Winter
flipper.py
"""


from tkinter import *
from random import randint
from CardLabel import *

root = Tk()

flipping_status = ['back', 'front', 'blank']
counter1 = 0 # Counter for the first card
counter2 = 0 # Counter for the second card
counter3 = 0 # Counter for the third card
#Sets the first cards that are called id
rand_num1, rand_num2, rand_num3 = randint(0,51),randint(0,51),randint(0,51) 

def flipping_cards():
	"""
	This function increases the counters based on the value of the other
	counters, so that they flip one after another in the same order together
	then displayes the cards. When the cards are set back to 0('back') they will
	be reassigned a new id value
	"""
	global counter1, counter2, counter3, label, rand_num1, rand_num2, rand_num3
	if counter1 == counter2 and counter1 == counter3: #If they are all the same, card1 flips
		counter1 = (counter1 + 1) % 3
	elif counter1 != counter2 and counter2 == counter3: #If first card flipped, then second card flips
		counter2 = (counter2 + 1) % 3
	elif counter2 != counter3: #If the first and second card is flipped, the third card is
		counter3 = (counter3 + 1) % 3

	if counter1 == 0 and counter2 == 0 and counter3 == 0: #Assigns new cards when cards flipped to back again
		rand_num1 = randint(0,51)
		rand_num2 = randint(0,51)
		rand_num3 = randint(0,51)

	a.display(flipping_status[counter1], rand_num1)#Displays first card
	b.display(flipping_status[counter2], rand_num2)#Displays second card
	c.display(flipping_status[counter3], rand_num3)#Displays third card

CardLabel.load_images() #Loads the images of the cards

a = CardLabel(root) #Makes 'a' a label of class CardLabel
a.grid(row=0, column=0)

b = CardLabel(root) #Makes 'b' a label of class CardLabel
b.grid(row=0,column=1)

c = CardLabel(root) #Makes 'c' a label of class CardLabel
c.grid(row=0,column=2)

button = Button(root,text='Flip', command=flipping_cards) #Flips the cards
button.grid(row=1,column=1)

if __name__ == '__main__':
	root.mainloop() #Calls mainloop
