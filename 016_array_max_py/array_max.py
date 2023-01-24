def array_max(array):
    """
    Finds the largest number in the list.
    Ignores elements that are not an int or a float

    Args:
        array (list): list of numbers (either float or int)

    Returns:
    Largest number in the list.  None if array is empty
    or if array is not a list.
    """


    if type(array) == list:
        length = len(array)
        if length != 0: 
            if type(array[0]) != int and type(array[0]) != float and length == 1:
                return None         
            else:
                i = 0
                
                for i in range((len(array))):
                    if type(array[i]) == int or type(array[i]) == float:
                        maximum=array[i]
                        break
                    else:
                        continue 
                
                while i < len(array):
                    if type(array[i]) == int or type(array[i]) == float:
                        if maximum < array[i]:
                            maximum = array[i]
                            i += 1
                        else:
                            i += 1
                    else:
                        i += 1
                return(maximum)
        else:
            return None        
    else:
        return None

    
def do_test(array):
    print("{}: {}".format(array,array_max(array)))

array1 = [ 77, 33, 19, 99, 42, 6, 27, 4 ]
array2 = [ -3, -42, -99, -1000, -999, -88, -77 ]
array3 = [ 425, 59, -3, 77, 0, 36]
array4 = ["string"]
array5 = [45.2, "string", 3, 0, "test"]

do_test(array1)
do_test(array2)
do_test(array3)
do_test("string passed")
do_test([])
do_test(array4)
do_test(array5)
