#ifndef _game_h
#define _game_h

typedef struct node{
  int x;
  int y;
  int v; // vertex number
  struct node* next;
  struct node** adj;
}node;

int runGame(WINDOW*** gb, int x, int y, int mode);

struct node* createNode(int x, int y, int v);

void addToAdjacency(struct node** adj, struct node* node, int x, int y, int v);

void adjResize(node** adj, int cap);

int checkForWinner(int p, int count, int** marked, int x, int y, int width, int height );

int computerSelect(WINDOW*** gb, int x, int y, int colorpair, int** marked);

int checkPath(int* t, int** marked, int x, int y); // checks path to see if it's cut off
#endif
