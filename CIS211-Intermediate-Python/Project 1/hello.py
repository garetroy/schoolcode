from sys import argv


language_dict = {"english":"Hello World", "spanish":"Hola Mundo", 
"arabic":"مرحبا بالعالم", "chinese":"你好世界", "german":"Hallo Welt", "italian":"Ciao mondo" }

def translate(x):
	"""
	Takes x as an argument, x is a language that the user put into the terminal which is the language they want translated to
	Hello World
	It checks to see if the language is in the dictionary
	If not blank it does not know the language and tells the user

	"""
	if x in language_dict:
		return(language_dict[x])
	else:
		return("Sorry I do not speak" + ' ' + x.capitalize())


if __name__ == "__main__":
	try:
		print(translate(argv[1].lower()))
	except:
		print(translate("english"))
