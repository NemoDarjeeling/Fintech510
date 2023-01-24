def make_change(amount):
    '''
return the change with minimum number of bills
    '''
    amount_ic = int(amount * 100)
    a = amount_ic // 10000
    b = (amount_ic - 10000 * a) // 5000
    c = (amount_ic - 10000 * a - 5000 * b) // 2000
    d = (amount_ic - 10000 * a - 5000 * b - 2000 * c) // 1000
    e = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d) // 500
    f = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e) // 200
    g = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e - 200 * f) // 100
    h = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e - 200 * f - 100 * g) // 25
    i = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e - 200 * f - 100 * g - 25 * h) // 10
    j = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e - 200 * f - 100 * g - 25 * h - 10 * i) // 5
    k = (amount_ic - 10000 * a - 5000 * b - 2000 * c - 1000 * d - 500 * e - 200 * f - 100 * g - 25 * h - 10 * i - 5 * j) // 1

    money_change = {100.00 : a, 50.00 : b, 20.00 : c, 10.00 : d, 5.00 : e, 2.00 : f, 1.00 : g, 0.25 : h, 0.10 : i, 0.05 : j, 0.01 : k}
    change = {x:y for x,y in money_change.items() if y!=0}
    return change
  
    
def print_change(change):
    '''
use change from the previous function to print results in format
    '''
    list_key = list(change.keys())
    list_values = list(change.values())
    for i in range(len(list_key)):
        print("${:.2f}: {}".format(list_key[i],list_values[i]))
