def printDigits(x):
  if x == 0:
    print("0",end="")
  elif (x < 0):
    print("-",end="")
    printDigits(-x)
  else:
    a = x // 10
    b = x % 10
    print("a={:d}, b={:d}".format(a,b))
    if a != 0:
      printDigits(a)

    print(b,end="")

printDigits(297)
print()
