from sys import argv
import datetime
from sqlite3 import *


def start_string():
	"""
	This will print out the first set of strings that are needed then calls creating to start creating the other
	parts of the strings
	"""
	print("""
		--- Sakila DVD Rentals ---

		Monthly report for Leo Ebert
		""")
	creating()
def creating():
	"""
	This takes each tuple that is presented in res and creates rented and returned as 
	a date time. Then checks to see if the arguments and the rented and returned are in the same months and year
	using month_year_check then prints out the strings needed using the tuple and late() function.
	"""
	for i in range(len(res)):
		rented = datetime.datetime.strptime(res[i][4], date_format)
		returned = datetime.datetime.strptime(res[i][5], date_format)
		if month_year_check(month, year, rented):
			k = late(rented, returned, res[i][3])
			print(res[i][2] + "            " + rented.strftime("%m/%d/%Y") +"   " + str(res[i][3]))
			print("            " + k)
	print("\n" + "Monthly total: " + str(round(total,2)))

def late(rented,returned,price):
	"""
	The late function first adds the price of rental to the total, then compares
	the rented date to the returned date and sees if the difference in days are
	greater than 3, if so then it adds the price of rental again to the total
	and prints out the late fee warning and the price
	"""
	global total
	total += price
	diff = returned - rented
	if diff.days > 3:
		total += price
		return("**late fee   " + returned.strftime("%m/%d/%Y") + "  " + str(price))
	else:
		return(returned.strftime("%m/%d/%Y"))

def month_year_check(month, year, rented):
	"""
	This just checks to see if the month and the year are the same as the one that is 
	presented in the arguments
	"""
	time_frame = datetime.datetime.strptime(str(month) + "/" + str(year), "%m/%Y")
	if time_frame.month == rented.month and time_frame.year == rented.year:
		return True
	return False

if __name__ == '__main__':
	sakila = connect("sakila211.db")
	name = argv[1].capitalize()
	year = int(argv[2])
	month = int(argv[3])
	cur = sakila.cursor()
	date_format = "%Y-%m-%d %H:%M:%S.%f"
	cur.execute('SELECT first_name, last_name, title, rental_rate, rental_date, return_date  FROM customer JOIN rental USING (customer_id) JOIN inventory USING (inventory_id) JOIN film USING (film_id) WHERE (last_name = "%s" OR first_name = "s")' % name)
	res = cur.fetchall() #Fetches all the arguments from the cur.execute command
	total = 0 #price that the person ows
	start_string()