def compute_average(l):
    """
    Computes the average of list, ignoring any entries that 
    are not numbers (floats or ints)

    Args:
    l(list): list of items to compute the average
 
    returns:
    average of the numbers in the list
    
    raises:
    ValueError if the argument is not a list or if the list does not contain any numbers
    """
    # TODO: Implement function
    sum_l = 0
    num_num = 0
    
    if isinstance(l, list):
        if len(l) == 0:
            raise ValueError("the list does not contain any numbers")
        for i in range(len(l)): 
            if type(l[i]) != int and type(l[i]) != float:
                continue
            else:
                sum_l += l[i]
                num_num += 1
        if num_num == 0:
            raise ValueError("the list does not contain any numbers")
        else:
            avg_l = sum_l / num_num
            return avg_l
    else:
        raise ValueError("the argument is not a list")
