"""
Print the calendar for a month
(without using the Python 'calendar' module).

Limitations: Treats February as always having 28 days. 

Author: Garett Roberts
"""

import sys      # For command-line arguments 
import datetime # To determine what day of week a month
				# begins on.  
# Note: For this project, module calendar
# is not permitted.  It basically has a function
# to do the whole assignment in one line. 

USAGE = """
Usage:  python3 calpr.py 12 2013
  where 12 can be replaced by any month 1..12
  and 2013 can be replaced by any year 1..2100
"""

if len(sys.argv) != 3:
	print(USAGE)
	exit(1)
	       
month = int(sys.argv[1])
year = int(sys.argv[2])

MONTHLEN = [ 0, # No month zero
	31, # 1. January
	28, # 2. February (ignoring leap years)
	31, # 3. March
	30, # 4. April
	31, # 5. May
	30,	# 6. June
	31, # 7. July
	31, # 8. August
	30, # 9. September
	31, #10. October
	30, #11. November
	31, #12. December
	]


# What day of the week does year,month begin on? 
a_date = datetime.date(year, month, 1)
starts_weekday = a_date.weekday()
## a_date.weekday() gives 0=Monday, 1=Tuesday, etc.
## Roll to start week on Sunday
starts_weekday = (1 + starts_weekday) % 7  
print(starts_weekday)


month_day = 1   			## Next day to print
last_day = MONTHLEN[month]  ## Last day to print

print(" Su Mo Tu We Th Fr Sa")
###
###  The first (perhaps partial) week
###
for i in range(7):
	if i < starts_weekday :
		print("   ", end="")
	else:
		# Logic for printing one day, moving to next
		print(format(month_day, "3d"), end="")
		month_day += 1
print() # Newline


days_left = (last_day - month_day + 1)
while (days_left - 6) > 0:
	for i in range(7):
		print(format(month_day, '3d'), end="")
		month_day += 1
	print(format(''))
	days_left -= 7

	
if month_day <= last_day:
	while month_day <= last_day:
		print(format(month_day, '3d'), end="")
		month_day += 1
print(format(''))
