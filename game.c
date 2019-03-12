#include <stdlib.h>
#include <curses.h>
#include "UI.h"
//uses adjacency list because adjacency matrix would have much unneeded space, especially on a large graph
//a graph is an array of adjacency lists
typedef  struct node{
  int x;
  int y;
  int v; // vertex number
  struct node* next;
  struct node** adj;
}node;
struct node* createNode(int x, int y, int v){
  node* newNode = malloc(sizeof(node));
  newNode->x = x;
  newNode->y = y;
  newNode->v = v;
  newNode->next = NULL;
  newNode->adj = NULL;
  return newNode;
}
void runGame(WINDOW*** gb, int x, int y, int mode){
int colorcheck = 1;
int** marked = malloc(sizeof(int*)*y);
for(int i = 0; i < y; i++){
  marked[i] = malloc(sizeof(int)*x);
}
for(int i = 0; i < y; i++){
  for(int j = 0; j < x; j++){
    marked[i][j] = 0;
  }
}

int* colarr = (int*)calloc(x, sizeof(int)); // values of each entry in colarr will represent how many windows are colored in the column
int col, p1count, p2count, totalcount;
p1count = 0;
p2count = 0;
node** p1adj = malloc(sizeof(node*)*10);
node** p2adj = malloc(sizeof(node*)*10);
char ch = 'f';
while(ch != 'q'){
  col = selectCol(gb,x,y,colorcheck % 2, marked);
  moveSpot(gb, col, colarr[col],y, colorcheck % 2);
  marked[y-1-colarr[col]][col] = 1;
  colarr[col]++;
  colorcheck++;
  ch = getchar();
}

return;
}
