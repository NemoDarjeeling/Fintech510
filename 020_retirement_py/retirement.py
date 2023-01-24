working_info = dict(months = int(489), contribution = float(1000), rate_of_return = float(0.045/12))
retired_info = dict(months = int(384), contribution = float(-4000), rate_of_return = float(0.01/12))
start_age = 327 // 12
initial_savings = 21345

def retirement(start_age, initial_savings, working_info, retired_info):
    """
    Prints the current status of an individual's retirement account.
    The dictionaries both have these fields:
        "months","contribution","rate_of_return"
    Args:
       start_age (int): At what age (in months) does the individual start
       initial_savings (float): initial savings in dollars
       working_info (dict): information about working
       retired_into (dict): information about retirement
    Returns:
    None
    """
    m1 = 0
    for m1 in range(working_info['months'] + 1):
        age = (327 + m1) // 12
        m3 = (m1+3) % 12
        print("Age {:3d} month {:2d} you have ${:,.2f}".format(age, m3, initial_savings))
        if m1 == 489:
            break
        a = initial_savings * (working_info['rate_of_return'] + 1) + working_info['contribution']
        initial_savings = a
        m1 += 1
        
        
    m2 = 0
    for m2 in range(retired_info['months'] - 1):
        age = (817 + m2) // 12
        m4 = (m2+817) % 12
        b = initial_savings * (retired_info['rate_of_return'] + 1) + retired_info['contribution'] 
        initial_savings = b
        print("Age {:3d} month {:2d} you have ${:,.2f}".format(age, m4, initial_savings))
        m2 += 1    
        
retirement(start_age, initial_savings, working_info, retired_info)
