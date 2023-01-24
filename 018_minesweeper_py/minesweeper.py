# Implements the minesweeper game: https://en.wikipedia.org/wiki/Minesweeper_(video_game)
# 
# As this assignments comes very early in your journey to learning Python,
# we have made some implementation decisions that are suboptimal as
# compared to using the entire language.

import random
import sys
from sys import argv

SQUARE_UNKNOWN     = -1
SQUARE_HAS_MINE    = -2
SQUARE_KNOWN_MINE  = -3

CLICK_KNOWN_MINE = -2
CLICK_INVALID    = -1
CLICK_CONTINUE   = 0
CLICK_LOSE       = 1

def board_width(board):
    return len(board[0])

def board_height(board):
    return len(board)

def add_random_mine(board): 
    """ attempts to place a random mine onto the board """
    
    # maximum number of times to place a mine before given up
    max_tries = board_height(board) * board_width(board) * 10
    for i in range(max_tries):
        x = random.randint(0, board_width(board)-1)
        y = random.randint(0, board_height(board)-1)
        if board[y][x] == SQUARE_UNKNOWN:
            board[y][x] = SQUARE_HAS_MINE
            return


def make_board(width, height, num_mines):
    """
    Creates a minesweeper board using a list of lists.  
    All entries are first created, setting each item to "SQUARE_UNKNOWN"
    Once that is done, "num_mines" are randomly placed on the board
    by calling add_random_mine repeatedly.
    """
    board = []
    for h in range(height):
        h_list = []
        for w in range(width):
            h_list.append(SQUARE_UNKNOWN)
        board.append(h_list)
    
    for n in range(num_mines):
        add_random_mine(board)

    return board


def print_board(board):
    #print header
    print("   ",end="")
    for i in range(board_width(board)):
        print(i // 10,end="")
    print()
    print("   ",end="")
    for x in range(board_width(board)):
        print(x % 10,end="")
    print()
    print("-" * (board_width(board)+3) )   # use string duplication

    for y in range(board_height(board)):
        print("{:2d}|".format(y),end="")
        for x in range(board_width(board)):
            if board[y][x] == SQUARE_UNKNOWN:
                print("?",end="")
            elif board[y][x] == SQUARE_HAS_MINE:
                print("?",end="")
            elif board[y][x] == SQUARE_KNOWN_MINE:
                print("*",end="")
            elif board[y][x] == 0:
                print(" ",end="")
            else:
                print(board[y][x],end="")
        print()

def has_mine(square):
    """ Returns true if a square has mine"""
    return square == SQUARE_HAS_MINE or square == SQUARE_KNOWN_MINE

def count_mines(board, x, y):
    """
    Counts the number of mines in the 8 squares around the (x,y) coordinate
    A mine is indicated by either SQUARE_HAS_MINE or SQUARE_KNOWN_MINE.
    We have provided a function that returns a Boolean value if a square has a
    boolean.
    Make sure you do not go outside of the list bounds
    """
    num_cm = 0
    for b in range(y-1, y+2):
        for a in range(x-1, x+2):
            if 0 <= a < len(board[0]) and 0 <= b < len(board) and (a != x or b != y) and has_mine(board[b][a]):
                num_cm += 1
    return num_cm

def click(board, x, y):
    if x < 0 or x > board_width(board) or y < 0 or y > board_height(board):
       return CLICK_INVALID
    elif board[y][x] == SQUARE_KNOWN_MINE:
        return CLICK_KNOWN_MINE
    elif board[y][x] == SQUARE_HAS_MINE:
        return CLICK_LOSE
    elif board[y][x] != SQUARE_UNKNOWN:
        return CLICK_CONTINUE
    else:
        board[y][x] = count_mines(board,x,y)
        return CLICK_CONTINUE

def check_win(board):
    """
    Game is won when no squares have the value SQUARE_UNKNOWN
    """
    for y in range (len(board)):
        for x in range(len(board[y])):
            if board[y][x] == SQUARE_UNKNOWN:
                return False

    return True


def reveal_mines(board):
    """
    Change SQUARE_HAS_MINE to SQUARE_KNOWN_MINE for all places on the board
    """
    for row in range(board_height(board)):
        for col in range(board_width(board)):
            if board[row][col] == SQUARE_HAS_MINE:
                board[row][col] = SQUARE_KNOWN_MINE

def read_int(prompt):
    while True:
        result = input(prompt)
        try:
            result = int(result)
            return result
        except:
            print("Invalid entry")

def do_reveal(board, x, y):
    for nx in range(x-1,x+2):
        if nx < 0 or nx >= board_width(board):
            continue
        for ny in range(y-1,y+2):
            if ny < 0 or ny >= board_height(board):
                continue

            if board[ny][nx] == SQUARE_HAS_MINE:
                board[ny][nx] = SQUARE_KNOWN_MINE
            else:
                if (board[ny][nx] == SQUARE_UNKNOWN): 
                    board[ny][nx] = count_mines(board, nx, ny)

def maybe_reveal(board, x, y):
    unknown_squares = 0
    known_mines = 0

    for nx in range(x-1,x+2):
        if nx < 0 or nx >= board_width(board):
            continue
        for ny in range(y-1,y+2):
            if ny < 0 or ny >= board_height(board):
                continue
            if board[ny][nx] == SQUARE_UNKNOWN or board[ny][nx] == SQUARE_HAS_MINE:
                unknown_squares += 1
            elif board[ny][nx] == SQUARE_KNOWN_MINE:
                known_mines += 1
    
    if unknown_squares > 0 and board[y][x] >=0:
        reveal_mines = (known_mines + unknown_squares == board[y][x])
        all_known = known_mines == board[y][x];
        
        if reveal_mines or all_known:
            do_reveal(board,x,y)
            return True

    return False

def determine_known_mines(board):
    found_more = False
    for y in range(board_height(board)):
        for x in range(board_width(board)):
            if board[y][x] >= 0:
                found_more = maybe_reveal(board,x,y) or found_more
    if found_more:
        determine_known_mines(board)


def play_turn(board):
    """ plays a turn.  Returns True if the game is over, otherwise False"""
    print("Current Board:")
    print_board(board)

    x = read_int("x coordinate:")
    y = read_int("y coordinate:")

    result = click(board,x,y)
    determine_known_mines(board)

    if result == CLICK_LOSE:
        print("Oh no! That square had a mine. You lose!")
        reveal_mines(board)
        print_board(board)
        return True;
    elif result == CLICK_INVALID:
        print("That is not a valid square, please try again")
        return False;
    elif result == CLICK_KNOWN_MINE:
        print("You already know there is a mine there!\n");
        return False;
    elif check_win(board):
        print_board(board)
        print("You win!")
        return True
    else:
        return False
    


# __name__ == "__main__" and argv explained in the "modules" notebook
if __name__ == "__main__":
    random.seed(42)    # seed the rng (set the beginning point) for validation]
    if len(argv) != 4:
        print("Usage: python3 minesweeper.py width height num_mines")
        sys.exit(-1)

    width     = int(argv[1])
    height    = int(argv[2])
    num_mines = int(argv[3])

    if (width <= 0 or height <= 0 or num_mines <= 0):
        print("Width, height, and num_mines must all be positive ints")
        sys.exit(-1)

    board = make_board(width,height,num_mines)
    game_over = False
    while not game_over:
        game_over = play_turn(board)
