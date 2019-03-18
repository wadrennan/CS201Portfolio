#include <stdlib.h>
#include <curses.h>
#include "UI.h"
//uses adjacency list because adjacency matrix would have much unneeded space, especially on a large graph
//a graph is an array of adjacency lists
typedef  struct node{
  int x; //x coord
  int y; //y coord
  int v; // vertex number
  struct node* next; //for adj lists
  struct node** adj; //pointer to p1 or p2 adj list
}node;

struct node* createNode(int x, int y, int v){

  node* newNode = malloc(sizeof(node));
  newNode->x = x;
  newNode->y = y;
  newNode->v = v;
  newNode->next = NULL;
  return newNode;
}
node** adjResize(node** adj, int cap){
  struct node** resize = malloc(sizeof(node) * cap);
  for(int i = 0 ; i < cap/2; i++){
    resize[i] = adj[i];
    adj[i]->adj = resize;
  }
  for(int j = cap/2 ; j < cap; j++){
    resize[j] = NULL;
  }
  printw("array resized ");
  refresh();
  return resize;
}
void addToAdjacency(struct node** adj, struct node* newNode, int x, int y, int v){
  //printw("%d added to adj ",v);
  adj[v] = newNode;
  for(int i = 0; i < v; i++){
     // if x is is equal and y is 1 less or more, or if y is equal and x +-1
    if((adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1)) || (adj[i]->y == y && (adj[i]->x == x-1 || adj[i]->x == x+1))){
      //printw("straight ");
      //refresh();
      struct node* temp = malloc(sizeof(node));
      struct node* temp2 = malloc(sizeof(node));
      temp = newNode;
      while(temp->next){
        temp = temp->next;
      }
      temp2->x = adj[i]->x;
      temp2->y = adj[i]->y;
      temp2->v = adj[i]->v;
      temp2->next = NULL;
      temp2->adj = NULL;
      temp->next = temp2;
      //printw(" %d added %d to list", newNode->v, temp2->v);
      //refresh();
      /////////////////////////////////////////////////////////////////////
      struct node* temp3 = malloc(sizeof(node));
      struct node* temp4 = malloc(sizeof(node));
      temp3 = adj[i];
      while(temp3->next){
        temp3 = temp3->next;
        //printw("adj[%d]->next = node %d ", i, temp3->v);
        //refresh();
      }
      temp4->x = newNode->x;
      temp4->y = newNode->y;
      temp4->v = newNode->v;
      temp4->next = NULL;
      temp3->next = temp4;
      //printw("adj[%d]->next = node %d ", i, newNode->v);
      //refresh();
    }
    if((adj[i]->x == x+1 || adj[i]->x == x-1) && (adj[i]->y == y-1 || adj[i]->y == y+1)){
      //printw("diagonal ");
      //refresh();
      struct node* temp = malloc(sizeof(node));
      struct node* temp2 = malloc(sizeof(node));
      temp = newNode;
      while(temp->next){
        temp = temp->next;
      }
      temp2->x = adj[i]->x;
      temp2->y = adj[i]->y;
      temp2->v = adj[i]->v;
      temp2->next = NULL;
      temp2->adj = NULL;
      temp->next = temp2;
      struct node* temp3 = malloc(sizeof(node));
      struct node* temp4 = malloc(sizeof(node));
      temp3 = adj[i];
      while(temp3->next){
        temp3 = temp3->next;
        //printw("adj[%d]->next = node %d ", i, temp3->v);
      //  refresh();
      }
      temp4->x = newNode->x;
      temp4->y = newNode->y;
      temp4->v = newNode->v;
      temp4->next = NULL;
      temp3->next = temp4;
      //printw(" %d added %d to list", newNode->v, temp2->v);
      //refresh();
    }
    //printw(" || ");
    //refresh();
  }
  return;
}

void runGame(WINDOW*** gb, int x, int y, int mode){
int colorcheck = 1; // alternates players
int** marked = malloc(sizeof(int*)*y);   //array to tell whether a certain window is marked by coordinates
for(int i = 0; i < y; i++){
  marked[i] = malloc(sizeof(int)*x);
}
for(int i = 0; i < y; i++){
  for(int j = 0; j < x; j++){
    marked[i][j] = 0;                   // all marked array == 0
  }
}
int* colarr = (int*)calloc(x, sizeof(int)); // values of each entry in colarr will represent how many windows are colored in the column
int col, p1count, p2count, totalcount, p1cap, p2cap;
p1count = 0; // represents v dynamically added to graph for p1
p2count = 0; // represents v dynamically added to graph of p2;
p1cap = 10;
p2cap = 10;
struct node** p1adj = malloc(sizeof(struct node*) * p1cap);
struct node** p2adj = malloc(sizeof(struct node*) * p2cap);
for(int i  = 0; i < p1cap; i++){
  p1adj[i] = NULL;
  p2adj[i] = NULL;
}
char ch = 'f';//placeholder
while(ch != 'q'){
  col = selectCol(gb,x,y,colorcheck % 2, marked);
  moveSpot(gb, col, colarr[col],y, colorcheck % 2);
  marked[y-1-colarr[col]][col] = 1;
  colarr[col]++;
  if(colorcheck %2 == 1){
      if(p1count > p1cap-1){
        p1cap = p1cap * 2;
      p1adj =  adjResize(p1adj, p1cap);
      }
      struct node* newNode = createNode(col, y-colarr[col], p1count);
      addToAdjacency(p1adj, newNode, col, y-colarr[col], p1count);
      p1count++;
  }
  else{
    if(p2count > p2cap-1){
      p2cap = p2cap * 2;
    p2adj =  adjResize(p1adj, p1cap);
    }
    struct node* newNode = createNode(col, y-colarr[col], p2count);
    addToAdjacency(p2adj, newNode, col, y-colarr[col], p2count);
    p2count++;
  }
  colorcheck++;
  ch = getch();
}
return;
}
