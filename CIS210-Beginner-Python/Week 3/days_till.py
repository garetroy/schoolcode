"""
How many days from yyyy mm dd until the next mm dd
CIS 210 assignment 3, Fall 2014
Usage example: python days_till.py  2012 09 24 06 14
	(first day of fall classes until end of spring finals)

Authors: Garett Roberts
"""

import sys  # For exit with a message
import argparse # Fancier command line parsing
MONTHLEN = [ 0, # No month zero
	31, # 1. January
	28, # 2. February (ignoring leap years)
	31, # 3. March
	30, # 4. April
	31, # 5. May
	30, # 6. June
	31, # 7. July
	31, # 8. August
	30, # 9. September
	31, #10. October
	30, #11. November
	31, #12. December
	]


def leapyear(year):
	"""
	Find if the year that it is paassed is a leap year or not then returns true or false
	"""
	if year % 400 == 0:
		return True
	if year % 100 == 0:
		return False
	if year % 4 == 0:
		return True
	else:
		return False

def count_days(year, first_month, first_day, end_month, end_day):
	"""
	Has counter days and adds days to the counter. It starts with the amount of days in a full month inbetween the first_month and 
	the end_month taking into count if it is a leap year or not. It finally ends with assesing how many days are left that aren't whole
	months and adds thoes days together.
	"""
	days = 0
	if is_same_month(year, first_month, first_day, end_month, end_day):
		print(str(0))
		return
	if is_in_leapyear(year, first_month, first_day, end_month, end_day):
		days += 1
	#if the end_month is greater than the first_month the counter counts backwards
	if first_month < end_month:
		days += ((end_day) + (MONTHLEN[first_month] - first_day))
		for x in range(first_month + 1, end_month):
			if x == 2 and leapyear(year):
				days += 1
				days += MONTHLEN[x]
			else:
				days += MONTHLEN[x]
		print(days)
	#if the end_month is less than the first_month the counter counts forward
	elif end_month < first_month:
		days += (MONTHLEN[first_month] - first_day)
		for x in range(first_month + 1, 13):
			if x == 2 and leapyear(year):
				days += 1
				days += MONTHLEN[x]
			else:
				days += MONTHLEN[x]
		for x in range(1, end_month):
			if x == 2 and leapyear(year + 1):
				days += 1
				days += MONTHLEN[x]
			else:
				days += MONTHLEN[x]
		days += end_day
		print(days)

	else:
		days += end_day - first_day
		print(days)

def is_same_month(year, first_month, first_day, end_month, end_day):
	'''
	Checks to see if they are the same month and day
	'''
	if first_month == end_month and end_day == first_day:
		return True
	return False

def is_in_leapyear(year, first_month, first_day, end_month, end_day):
	#If it is a leap year and both months are in that leap year adds one
	if first_month == 2 and end_month == 2 and leapyear(year):
		return True
	#Adds one if the first month is within the leap year
	if first_month == 2 and leapyear(year):
		return True
	#Adds one if the end month is within the leap year
	if end_month == 2 and leapyear(year):
		return True
	return False

def main():
	"""
	Main program gets year number from command line, 
	invokes computation, reports result on output. 
	args: none (reads from command line)
	returns: none (write to standard output)
	effects: message or result printed on standard output
	"""
	## The standard way to get arguments from the command line, 
	##    make sure they are the right type, and print help messages
	parser = argparse.ArgumentParser(description="Compute days from yyyy-mm-dd to next mm-dd.")
	parser.add_argument('year', type=int, help="Start year, between 1800 and 2500")
	parser.add_argument('start_month', type=int, help="Starting month, integer 1..12")
	parser.add_argument('start_day', type=int, help="Starting day, integer 1..31")
	parser.add_argument('end_month', type=int, help="Ending month, integer 1..12")
	parser.add_argument('end_day', type=int, help="Ending day, integer 1..12")
	args = parser.parse_args()  # will get arguments from command line and validate them
	year = args.year
	start_month = args.start_month
	start_day = args.start_day
	end_month = args.end_month
	end_day = args.end_day
	
   #print("Checking date ", str(year) + "/" + str(start_month) + "/" + str(start_day))
	
	#Checks to see if invalid input date of leapyear day while not a leapyear
	if end_month == 2 and end_day == 29 and not leapyear(year):
		end_month = 3
		end_day = 1

	if year >= 2500 or year <= 1800:
		print('Must  start on a valid date between 1800 and 2500')
	elif start_day > MONTHLEN[start_month] or end_day > MONTHLEN[end_month] and not leapyear(year):
		print('Must  start on a valid date between 1800 and 2500')
	elif start_day > (MONTHLEN[start_month] + 1) or end_day > (MONTHLEN[end_month] + 1) and leapyear(year):
		print('Must  start on a valid date between 1800 and 2500')
	elif (start_month == 2 and not leapyear(year) and start_day == 29):
		print('Must  start on a valid date between 1800 and 2500')
	elif start_month > 12 or end_month > 12 or start_month < 0 or end_month < 0:
		print('Must  start on a valid date between 1800 and 2500')
	else:
		count_days(year,start_month,start_day,end_month,end_day)


if __name__ == "__main__":
	main()
		