import sys
from sys import argv

def read_key_values(filename):
    """
    Reads a key-value delimited file (separated by first =) into a dictionary

    Args:
    filename(str): name of the file to read
    
    Returns:
    dictionary of the read items
    """
    dictionary = {}
    
    with open(filename, "rt") as f:
        lines = f.readlines()
        for line in lines:
            key_values = line.strip("\n").split("=")
            dictionary[key_values[0]] = key_values[1]
    
    return dictionary

def create_output_filename(name):
    """
    create the output file name.  Given an input filename such as "input.txt",
    return "input.txt.counts"
    """
    output_name = name + ".counts"
    
    return output_name

def process_key_file(filename,key_values):
    """
    Loads in a key file and produces a dictionary of the count of the values 
    If a key is not found in key_values use "<unknown>"

    Args:
    filename(str): file containing keys to process
    key_values(dict): existing keys to load
    """
    with open(filename, "rt") as f:
        
        keys = f.readlines()
        value_count = {}
        
        for key in keys:
            key = key.strip("\n")
            value = key_values.get(key, '<unknown>') #按照key去key_value里面get对应key的value，而不是key本身，如果key_value里面没有这个key，就返回unknown作为value
            value_count[value] = value_count.get(value,0) + 1 
    
    return value_count

def write_output(filename,counts):
    """
    Sort the output value the highest count descending. If two values are
    equal, arbitrarily choose 1
    """
    f = open(filename, "wt")
    
    counts_sorted = sorted(counts.items(), key = lambda x : x[1], reverse = True)
    
    for count in counts_sorted:
        f.write('{}: {}\n'.format(count[0],count[1]))
        
    f.close()

def process(args):
    """
    Implement your algorithm in this function
    """
    # print(args)   #Uncomment if you want to validate/see the command-line arguments
    key_value = read_key_values(args[1])
    
    for file in args[2:]:
        counts = process_key_file(file, key_value)
        output_name = create_output_filename(file)
        write_output(output_name, counts) 

# __name__ == "__main__" and argv explained in the "modules" notebook
if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: python3 key_value.py file1_name file2_name ...")
        sys.exit(-1)
    process(argv)
