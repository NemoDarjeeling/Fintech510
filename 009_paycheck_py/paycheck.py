# sample code only to demonstrate how to print
# Copy this line and modify the label and variable
# to display results

def input_work_hours():
    return float(input("How many hours did the employee work?"))

def input_pay_rate():
    return float(input("What is the employee's pay rate?"))

def main():
    work_hours=input_work_hours()
    pay_rate=input_pay_rate()
    if work_hours<=40:
        total_pay=work_hours*pay_rate
    else:
        total_pay=40*100+(work_hours-40)*pay_rate*1.5
    tax=total_pay*0.2
    net_pay=total_pay-tax
    print("Total pay:",total_pay)
    print("Taxes:",tax)
    print("Net pay:",net_pay)
    
main()
