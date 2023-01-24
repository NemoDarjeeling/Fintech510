/*#include<stdio.h>  
#include<stdlib.h>  
  
  
int main()  
{  
    int i,j;  
    //申请一个3行2列的整型数组  
    int (*a)[2]=(int(*)[2])malloc(sizeof(int)*3*2);  
    for(i=0;i<3;i++)  
    {
        for(j=0;j<2;j++)  
        {  
            printf("%p\n",&a[i][j]);  //输出数组每个元素地址，每个元素的地址是连续的
        }
    }
 
 
    free(a);
    return 0;  
}  


board_t * makeBoard(int w, int h, int numMines) {
  board_t * playBoard = malloc(sizeof(*playBoard));
  playBoard = NULL; //initialising playBoard, with 2D array, width, height, totalMines in it
  playBoard->board = malloc(sizeof(int) * w * h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      playBoard->board[i][j] == UNKNOWN;
    }
  }
  playBoard->height = h;
  playBoard->width = w;
  playBoard->totalMines = numMines;

  for (int m = 0; m < numMines; m++) {
    addRandomMine(playBoard);
  }
  return playBoard;
}
*/

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
  board_t* b=malloc(sizeof(*b)) ;
  b->width = w;
  b->height = h;
  b->totalMines= numMines;
  b->board=malloc(h*(sizeof(*(b->board))));
  int * curr = NULL;
  for(int y=0 ; y<h; y++){
    curr = malloc(w*sizeof(*curr));
    for(int x=0 ;x<h;x++){
      curr[x]=UNKNOWN;
    }   
    b->board[y]= curr;
    curr=NULL;  
  }
  for(int i=0 ;i<numMines;i++) addRandomMine(b);
  return b;
 
}

int main() {
    makeBoard(3, 3, 4);
    return 0;
}