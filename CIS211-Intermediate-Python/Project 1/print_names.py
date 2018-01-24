from sys import argv

class Name:

	def __init__(self,first,last):
		self.first = first
		self.last = last


def name_list(x, sort_order='', inits=''):
	"""
	This function takes file x and makes opens it into variable people.
	Then it interates through the list checking the sort order, and if initials
	are wanted, it makes the initals.
	"""
	people = open(x)
	sort_list = []
	for i in people:
		name_person = i.split() #gets rid of the /n
		person = Name(name_person[0],name_person[1]) #defines person
		if inits == 'inits' and sort_order.lower() == 'last': #checks to see if it is sorted by last name and wants inits
			sort_list.append(person.last + ", " + person.first[0] + ".")
		elif sort_order.lower() == 'last': #checks to see if wanted to sort by last name
			sort_list.append(person.last + ", " + person.first)
		if inits == 'inits' and sort_order.lower() == 'first':
			sort_list.append(person.first[0] + "." + " " + person.last)
		elif sort_order.lower() == 'first':  #checks to see if wanted to sort by first name
			sort_list.append(person.first + " " + person.last)
		if sort_order == '': #if there are no sort order listed, defaults to fist and last
			sort_list.append(person.first + " " + person.last)
	sort_list.sort()
	return('\n'.join(sort_list))

		
if __name__ == '__main__':
	if len(argv) == 4:
		print(name_list(argv[1],argv[2],argv[3]))
	elif len(argv) == 3:
		print(name_list(argv[1],argv[2]))
	elif len(argv) == 2:
		print(name_list(argv[1]))
	else:
		print("Not enough info, don't forget txt file, sort order, and if you want initals")
