def print_receipt(subtotal, tax_rate, tip_rate):
    '''
used to calculate tax, tip, and total
    '''
    tax=tax_rate*subtotal
    tip=tip_rate*subtotal
    total=subtotal+tax+tip
    
    print("Subtotal: $""{:10.2f}".format(subtotal))
    print("     Tax: $""{:10.2f}".format(tax))
    print("     Tip: $""{:10.2f}".format(tip))
    print("{:>21s}".format("=========="))
    print("   Total: $""{:10.2f}".format(total))
          
    
