"""
Garett Roberts
CIS211 Winter Term
hello.py
"""

from tkinter import *

root = Tk()

language_dict = {0:"Hello World", 1:"Hola Mundo", 
2:"مرحبا بالعالم", 3:"你好世界", 4:"Hallo Welt", 5:"Ciao mondo" }
#Language Dictionary

k = 1
#The position of the language (Called when change_language is called)

def quit():
	"""
	Quits the program when called
	"""
	root.quit()

def change_language():
	"""
	This changes the text to a different language using language_dict
	and the counter k
	"""
	global language_dict,k
	hello.config(text=language_dict[k])
	k = (1 + k) % 6

hello = Label(root, text=language_dict[0]) #creates the first instance of the text
hello.pack() #packs hello



Button(root, text="Change Language", command=change_language).pack() #This button changes languages
Button(root, text="Quit", command=quit).pack() #This button quits the program
root.mainloop() #Calls mainloop