from sys import argv
import sys

def parse_state_information(filename): # 没有检查数据合法性
    """
    Opens the state information file named in filename, loads all of the 
    values, placing them in a single data structure. Returns that data 
    structure.  You may created nested data structures.
    """
    state_info = {}
    with open(filename, "r") as f:
        lines = f.readlines()
        for line in lines:
            key_values = line.strip("\n").split(":")
            state_info[key_values[0]] = [key_values[1], key_values[2]]
    return state_info

def print_state_information(state_info):
    """
    For the state_info data structure (produced as a result),  
    print all statues in alphabetical order using the string:
    "{}: Population - {:,d}, Electoral Votes: {:d}"
    """
    state_info_sort = sorted(state_info.items())
    for i in range(len(state_info_sort)):
        print("{}: Population - {:,d}, Electoral Votes: {:d}".format(state_info_sort[i][0], int(state_info_sort[i][1][0]), int(state_info_sort[i][1][1])))

def parse_vote_information(filename): # 没有检查数据合法性
    """
    Opens the vote information file and returns the information 
    in a data structure
    """
    vote_info = {}
    with open(filename, "r") as f:
        lines = f.readlines()
        for line in lines:
            key_values = line.strip("\n").split(":")
            vote_info[key_values[0]] = key_values[1]
    return vote_info

def count_electoral_votes(state_info,vote_info):
    """
    Counts and returns the number of electoral votes received by 
    Candidate A in the election.

    For our purposes, Candidate A receives ALL electoral votes for a
    state if Candidate A receives strictly more than 50% of the votes in
    that State.  [Yes, we know that in the US there are a few states
    with more complex rules, but we will ignore them.  We will also
    ignore the electoral complexities of what would happen if a
    candidate received exactly 50%, and in this case, just say that
    Candidate A does not receive those electoral votes.  We are also
    assuming everyone in every state votes--while this doesn't happen in
    a real election, it is what we are doing here].
    """
    a = sorted(state_info.items())
    b = sorted(vote_info.items())
#[('W', ['300', '3']), ('X', ['1000', '10']), ('Y', ['500', '5']), ('Z', ['400', '4'])]
#[('W', '152'), ('X', '600'), ('Y', '250'), ('Z', '210')]    
    number_of_votes = 0
    
    for n in range(len(a)):
        a1 = int(a[n][1][0])
        b1 = int(b[n][1])
        if b1 / a1 > 0.5:
            number_of_votes += int(a[n][1][1])
    return number_of_votes

def determine_winner(state_info, candidate_a_electoral_votes):
    """
    Determines whether Candidate A or Candidate B won based upon who
    won the majority of the electoral votes. If there is a tie, return None.
    Returns "A", "B", or None    the last one is the value None
    """
    a = sorted(state_info.items())
#[('W', ['300', '3']), ('X', ['1000', '10']), ('Y', ['500', '5']), ('Z', ['400', '4'])]
    all_electoral_votes = 0
    for n in range(len(a)):
        all_electoral_votes += int(a[n][1][1])
    result = candidate_a_electoral_votes / all_electoral_votes
    
    if result > 0.5:
        return "A"
    elif result < 0.5:
        return "B"
    else:
        return None

def print_winner(winner_name, number_of_votes):
    """
    Prints the winner.  If Candidate A or B wins, print
    "Candidate {} wins the election with {:d} votes" using the winner_name
    and number of Electoral Collage.

    If neither won the vote, print "It's a tie in the Electoral Collage."
    """
    if winner_name == "A":
        winner_votes = number_of_votes
        print("Candidate {} wins the election with {:d} votes".format(winner_name, winner_votes))
    elif winner_name == "B":
        winner_votes = 538 - number_of_votes
        print("Candidate {} wins the election with {:d} votes".format(winner_name, winner_votes))
    else:
        print("It's a tie in the Electoral College.")

def determine_recounts(state_info, vote_info):
    """
    Produces a list of strings, where each string represents information
    about a state the requires a recount. Recounts are required when a 
    Candidate A is within +/ 0.5% of 50% of the votes.  So 49.50% or 50.50%
    require a recount, while 49.49% and 50.51% do not require a recount.
    
    Only include states that require a recount in the result. For each state
    that requires a recount, include a line of the form:
    "{} requires a recount (Candidate A has {:.2f}% of the vote)".
    """
    a = sorted(state_info.items())
    b = sorted(vote_info.items())
#[('W', ['300', '3']), ('X', ['1000', '10']), ('Y', ['500', '5']), ('Z', ['400', '4'])]
#[('W', '152'), ('X', '600'), ('Y', '250'), ('Z', '210')]    
    recount_list = []
    for n in range(len(a)):
        a1 = int(a[n][1][0])
        b1 = int(b[n][1])
        if 0.495 <= b1 / a1 <= 0.505:
            re_state = a[n][0]
            re_perce = (b1 / a1) * 100
            recount_list.append("{} requires a recount (Candidate A has {:.2f}% of the vote)".format(re_state, re_perce))
    return recount_list

def save_recounts(recount_list):
    """
    saves each entry of the list to a file named "recounts.txt".  The
    entries must be printed in alphabetical order.
    """
    f = open('recounts.txt', "wt")
    for i in range(len(recount_list)):
        f.write('{}\n'.format(recount_list[i]))
    f.close()

def determine_largest_win(state_info, vote_info):
    """
    Determines in which state Candidate A won the largest percentage 
    of the vote.

    returns a string with the following format:
    "Candidate A won {} with {:.2f}% of the vote"

    where the first {} should be the name of the state, and the {.2f} 
    should be the percentage of the vote won.  For example, it might return
    "Candidate A won California with 73.24% of the vote"

    None is returned if candidate A did not win a state
    """
    a = sorted(state_info.items())
    b = sorted(vote_info.items())
    dict_large_win = {}
#[('W', ['300', '3']), ('X', ['1000', '10']), ('Y', ['500', '5']), ('Z', ['400', '4'])]
#[('W', '152'), ('X', '600'), ('Y', '250'), ('Z', '210')]    
    
    for n in range(len(a)):
        a1 = int(a[n][1][0])
        b1 = int(b[n][1])
        if b1 / a1 > 0.5:
            key = a[n][0]
            value = (b1 / a1) * 100
            dict_large_win[key] = value
    list_large_win = sorted(dict_large_win.items(), key = lambda x:x[1], reverse = True)
    
    if list_large_win != []:
        return ("Candidate A won {} with {:.2f}% of the vote".format(list_large_win[0][0], list_large_win[0][1]))
    else:
        return None


def process(state_info_filename, voter_info_filename):
    """
    Implements the "Several steps exist for this assignment" section
    """
    state_info = parse_state_information(state_info_filename)
    vote_info = parse_vote_information(voter_info_filename)
    
    print_state_information(state_info)
    
    number_of_votes = count_electoral_votes(state_info, vote_info)
    candidate_a_electoral_votes = number_of_votes #迷惑操作，没必要专门用一行重命名
    winner_name = determine_winner(state_info, number_of_votes)
    print_winner(winner_name, number_of_votes)
    
    recount_list = determine_recounts(state_info, vote_info)
    save_recounts(recount_list)
    
    print(determine_largest_win(state_info, vote_info))


if __name__ == "__main__":
    """implement checking command line arguments, call process()"""
    if len(argv) != 3:
       print("Error: Incorrect number of command-line")
       sys.exit(1)
    process(argv[1], argv[2])
