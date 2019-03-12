#ifndef _game_h
#define _game_h

typedef struct node{
  int x;
  int y;
  int v; // vertex number
  struct node* next;
  struct node** adj;
}node;

void runGame(WINDOW*** gb, int x, int y, int mode);
struct node* createNode(int x, int y, int v);

#endif
