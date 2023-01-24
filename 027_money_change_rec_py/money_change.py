def make_change(amount):
    '''
return the change with minimum number of bills, with mc_rec doing the recursion part                                                                           
    '''
    if amount < 0.01:
        return {} 
    else:
        a_ic = int(amount * 100)
        deno = [10000, 5000, 2000, 1000, 500, 200, 100, 25, 10, 5, 1]
        dict_mc_proto = {}    
        
        dict_mc_proto = mc_rec(a_ic, deno, dict_mc_proto)
        
        change = {x:y for x,y in dict_mc_proto.items() if y!=0}
        return change

def mc_rec(a_ic, deno, dict_mc_proto):
    '''
mc_rec doing the recursion
    '''    
    if a_ic == 0:
          return
    key = deno[0] / 100
    value = a_ic // deno[0]
    dict_mc_proto[key] = int(value)
    deno.pop(0)
    mc_rec(a_ic - key * 100 * value, deno,dict_mc_proto)
    return dict_mc_proto

def print_change(change):
    '''                                                                       
use change from the previous function to print results in format                   
    '''
    list_key = list(change.keys())
    list_values = list(change.values())
    for i in range(len(list_key)):
        print("${:.2f}: {}".format(list_key[i],list_values[i]))
