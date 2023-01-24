def max_seq(l):
   """
   max_seq returns a the maximum increasing contiguous subsequence in the list.
   
   Args:
   l(list): list of numbers
   Returns:
   the maxiumum increasing contiguous subsequence as a list. If the l is empty,
   an empty list is returned
   Raises:
   TypeError is the function contains an item that is not arithmetically 
   compatible with ints and floats
   """
   for i in range(len(l)):
       if type(l[i]) != int and type(l[i]) != float:
           raise TypeError("the list contains an item that is not arithmetically compatible with ints and floats")
    
   if len(l) == 0:
       return []
   
   list_sub = []
   a = l[0]
   l_split = [l[0]]
   for i in range(len(l)-1):
       if l[i+1] > a:
           l_split.append(l[i+1])
           a = l[i+1]
       else:
           list_sub.append(l_split)
           l_split = []
           a = l[i+1]
           l_split.append(l[i+1])
   list_sub.append(l_split)
   
   len_sub = 0
   for i in range(len(list_sub)):
       if len(list_sub[i]) > len_sub:
           max_seq = list_sub[i]
           len_sub = len(list_sub[i])
   return max_seq          
