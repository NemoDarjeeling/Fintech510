import unittest
from max_seq import *
class TestMaxSequence(unittest.TestCase):
    def test_legal_list(self):
        """
        test legal list's result
        """
        self.assertEqual(max_seq([1,2,1,3,5,8,2,4,6,9]), [1,3,5,8], "Incorrect result")  
        
    def test_illegal_list(self):
        """
        test illegal list with element(s) that not arithmetically compatible with ints and floats
        """
        with self.assertRaises(Exception) as context:
            max_seq([1,2,"a",3,5,8,2,4,6,9])
        self.assertTrue(type(context.exception) == TypeError,"the list contains an item that is not arithmetically compatible with ints and floats")
        
    def test_empty_list(self):
        """
        test empty list's result
        """
        self.assertEqual(max_seq([]), [])
