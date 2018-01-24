"""
Garett Roberts
CIS211 Winter
payment.py
"""

from tkinter import *

root = Tk()

Label(root, text="Loan Amount($)").grid(row=0) #Creates amount label
Label(root, text="Rate(%)").grid(row=1) #Creates rate label
Label(root, text="Durration of Loan(years)").grid(row=2) #Creates year label

amount = Entry(root) #Creates entry box assigned to amount
rate = Entry(root) #Creates entry box assigned to rate
length = Entry(root) #Creates entry box assigned to length

#These jsut position the buttons
amount.grid(row=0,column=1)
rate.grid(row=1,column=1)
length.grid(row=2,column=1)

def monthly_payment():
	"""
	This takes the amount put in the entry boxes and finds the monthly_payment
	using the formula given
	"""
	Rate = float(rate.get())
	Amount = float(amount.get())
	Length = float(length.get())
	r = Rate/100/12
	p = 12 * Length
	Payment = ((r * Amount) / (1 - (1 + r)**(-p)))
	Payment = round(Payment,2)
	Label(root, text="Payment per month: " + str(Payment)).grid(row=4, column=1)

Button(root, text="Calculate Monthly Payment", command=monthly_payment).grid(row=1,column=2)

root.mainloop()