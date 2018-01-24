"""
Check that password is 8-32 contains required elements:
  Upper case letters
  Lower case letters
  Digits

 CIS 210 assignment 1, Fall 2013

authors: Garett Roberts

"""

## Get password from command line
import sys
if (len(sys.argv) > 1) :
    passwd = sys.argv[1]
else:
    print("Usage: python3 passwdcheck.py 9999")
    exit(1)  ## Quit the program right here, indicating a problem

def check(password):
  '''
  Checks the password for inefficiencies by first checking length,
  then checking if there is any digits present in the string,
  then checking for uppercase letters presence in the string,
  then checking for lowercase letters presence in the string,
  if there are any inefficiencies the counter 'problem' is added
  this way at the end the program can tell if it is a good program.
  '''
  password = str(password)
  problem = 0
  if len(password) < 6:
    print ('Password must be at least 6 characters long')
    problem += 1
  if not (any(digit.isdigit() for digit in password)):
    print('Password must include digits')
    problem += 1
  if not (any(upper.isupper() for upper in password)):
    print ('Passowrd must include upper case letters')
    problem += 1
  if not (any(lower.islower() for lower in password)):
    print ('Password must include lower case letters')
    problem +=1
  if problem == 0:
    print('Good passowrd')

check(passwd)