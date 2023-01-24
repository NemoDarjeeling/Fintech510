from curses.ascii import isalpha
import sys
from sys import argv

def breaker(f):
    dict_letter = {}
    while True:
        letter = f.read(1)
        if not letter: break
    
        if letter.isalpha():
            dict_letter[letter] = dict_letter.get(letter, 0) + 1
            
    dict_letter_sorted = sorted(dict_letter.items(), key = lambda x:x[1], reverse = True)
    is_e = dict_letter_sorted[0][0]

    
    if dict_letter == {}:
        sys.exit(1)
    elif dict_letter_sorted[0][1] == dict_letter_sorted[1][1]:
        sys.exit(1)

    
    e = "E"
    e = e.lower()
    e = ord(e)
    e -= ord("a")
    
    is_e = ord(is_e)
    is_e -= ord("a")
    
    key1 = is_e - e
    key2 = 26 + is_e - e
    if key1 < 0 or key1 >= 26:
        return key2
    elif key2 < 0 or key2 >=26:
        return key1
    else:
        return 0
    
if __name__ == "__main__":
    if len(argv) != 2:
        print("Usage: python3 breaker.py input_file_name")
        sys.exit(1)
    
    with open(argv[1]) as f:
        key = breaker(f)
        print(key)    
