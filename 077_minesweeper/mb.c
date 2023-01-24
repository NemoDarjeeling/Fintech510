#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)


struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};

typedef struct _board_t board_t;

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines taht we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while(b->board[y][x] == HAS_MINE);
  b->board[y][x] = HAS_MINE;
}

board_t * makeBoard(int w, int h, int numMines) {
  board_t * playBoard = NULL;
  playBoard = malloc(sizeof(*playBoard));//initialising playBoard, with 2D array, width, height, totalMines in it
  //malloc之后再NULL分配的记忆本身不会消失，但是把记忆地址擦除了，之后再想给地址里赋值就出问题了
  playBoard->height = h;
  playBoard->width = w;
  playBoard->totalMines = numMines;

  playBoard->board = malloc(h * (sizeof(*(playBoard->board))));
  for (int i = 0; i < h; i++) {
    playBoard->board[i] = malloc(sizeof(*(playBoard->board[i])) * w);
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      playBoard->board[i][j] = UNKNOWN;//不是==哦，捏妈妈的
    }
  }

  for (int m = 0; m < numMines; m++) {
    addRandomMine(playBoard);
  }
  return playBoard;
}

/*void printBoard(board_t * b) {    
  int found = 0;
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x/10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x%10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y %100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == KNOWN_MINE) {
	printf("*");
	found++;
      }
      else if (b->board[y][x] < 0) {
	printf("?");
      }
      else if (b->board[y][x] == 0) {
	printf(" ");
      }
      else {
	printf("%d", b->board[y][x]);
      }
    }
    printf("\n");
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");

  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x/10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x%10);
  }
  printf("\nFound %d of %d mines\n", found, b->totalMines);
}*/

int countMines(board_t * b, int x, int y) {
  int mineCount = 0;
  for (int j = -1; j < 2; j++) {
    for (int i = -1; i < 2; i++){
        if ((x + i) < 0 || (x + i) >= b->width) {
            continue;
        }
        else if ((y + j) < 0 || (y + j) >= b->height) {
            continue;
        }
        else if ((i == 0) && (j == 0)) {
            continue;
        }
        else {
            int nx = x + i;
            int ny = y + j;
            if (IS_MINE(b->board[ny][nx])) {
                mineCount++;
            }
        }
    }
  }
  return mineCount;
}

int checkWin(board_t * b) {//checkWin(b) is true, print win, so if win, checkWin(b) return 1
  for (int j = 0; j < b->height; j++) {
    for (int i = 0; i < b->width; i++) {
        if (b->board[j][i] == UNKNOWN) {
            return 0
        }
    }
  }
  return 1;
}

int main() {
    board_t * test = makeBoard(3, 3, 4);
    
    
    
    return 0;
}