p = input("What is the amount borrowed?")
r = input("What is the annual interest rate - express this as a decimal such as 0.07 for 7%?")

p1=float(p)
r1=float(r)/12

n=12*30
m=(1+r1)**n
A=p1*r1*m/(m-1)

payment_amount = int(A*100)/100
print(payment_amount)
