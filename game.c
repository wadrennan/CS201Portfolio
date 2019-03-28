#include <stdlib.h>
#include <curses.h>
#include "UI.h"
#include "queue.h"
//uses adjacency list because adjacency matrix would have much unneeded space, especially on a large graph
//a graph is an array of adjacency lists
typedef  struct node{
  int x; //x coord
  int y; //y coord
  int v; // vertex number
  int visited;
  int type; // 1 = vert 2 = horizontal 3  = diag
  struct node* next; //for adj lists
  struct node** adj; //pointer to p1 or p2 adj list
}node;

struct node* createNode(int x, int y, int v){

  node* newNode = malloc(sizeof(node));
  newNode->x = x;
  newNode->y = y;
  newNode->v = v;
  newNode->type = 0;
//  newNode->visited = 0;
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
      if(adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1)){
        temp2->type = 1;
      }
      else{
        temp2->type = 2;
      }
    //  temp2->visited = 0;
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
      if(adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1)){
        temp4->type = 1;
     }
     else{
       temp4->type = 2;
     }
      //if(adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1){
        //temp->type = 1;
    //  }
      //temp4->visited = 0;
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
      temp2->type = 3;
    //  temp2->visited = 0;
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
      temp4->type = 3;
      //temp4->visited = 0;
      temp4->next = NULL;
      temp3->next = temp4;
      //printw(" %d added %d to list", newNode->v, temp2->v);
      //refresh();
    }
    //printw(" || ");
    //refresh();
  }
/*  for(int j = 0; j < v; j++){
    node* new = adj[j]->next;
    printw(" adj %d ", adj[j]->v);
    while(new){
      printw(" type = %d ", new->type);
      refresh();
      new = new->next;
    }
  }*/
  return;
}

int checkForWinner(int p, int count, int** marked, int x, int y, int width, int height ){
  /*iterate through every node in adj list (number of vertices) and get their xy coords, check all around for neighbors*/
  if(count < 4){
    return 0;
  }
  int counter = 0;
  int i = 0;
  int temp;
  //straight check
  if(p ==1){
    for(int i = 0 ; i < width; i++){

      if(marked[y][i] == 1){
        counter++;
      }
      else{
        counter = 0;
      }
      if(counter == 4){
        printw("WINNER");
        refresh();
        return 1;
      }
    }
    counter = 0;
    for(int i = 0 ; i < height; i++){
      if(marked[i][x] == 1){
        counter++;
      }
      else{
        counter = 0;
      }
      if(counter == 4){
        printw("WINNER");
        refresh();
        return 1;
      }
    }
    //diagonal

    int startx = x ;
    int starty = y;
    counter = 0;
    while(startx < 0){
      startx++;
    }
    while(starty < 0){
      starty++;
    }
  while(starty < height-1 && startx >0){
    starty++;
    startx--;
  }
  //left to right diagonal
  while(starty >0 && startx < width){
    if(marked[starty][startx] == 1){
      counter++;
    }
    else{
      counter = 0;
    }
    if(counter == 4){
      printw("winner");
      refresh();
      return 1;
    }

    starty--;
    startx++;
  }
  //right to left diagonal
   startx = x ;
   starty = y;
  counter = 0;
  while(starty < height-1 && startx < width){
  starty++;
  startx++;
  }
    while((startx >0) && (starty >0)){
      if (marked[starty][startx] == 1){
        counter++;
      }
      else{
        counter = 0;
      }
      if(counter == 4){
        printw("WINNER");
        refresh();
        return 1;
      }
      startx--;
      starty--;
    }

  }
  else{
    for(int i = 0 ; i < width; i++){
      if(marked[y][i] == 2){
        counter++;
      }
      else{
        counter = 0;
      }
      if(counter == 4){
        printw("WINNER");
        refresh();
        return 2;
      }
    }
    counter = 0;
  for(int i = 0 ; i <height; i++){
    if(marked[i][x] == 2){
      counter++;
    }
    else{
      counter = 0;
    }
    if(counter == 4){
      printw("WINNER");
      refresh();
      return 2;
    }
  }
  //diagonal

  int startx = x ;
  int starty = y;
  counter = 0;
  while(startx < 0){
    startx++;
  }
  while(starty < 0){
    starty++;
  }
while(starty < height-1 && startx >0){
  starty++;
  startx--;
}
//left to right diagonal
while(starty >0 && startx < width){
  if(marked[starty][startx] == 2){
    counter++;
  }
  else{
    counter = 0;
  }
  if(counter == 4){
    printw("WINNER");
    refresh();
    return 2;
  }

  starty--;
  startx++;
}
//right to left diagonal
 startx = x ;
 starty = y;
counter = 0;
while(starty < height-1 && startx < width){
starty++;
startx++;
}
  while((startx >0) && (starty >0)){
    if (marked[starty][startx] == 2){
      counter++;
    }
    else{
      counter = 0;
    }
    if(counter == 4){
      printw("WINNER");
      refresh();
      return 2;
    }
    startx--;
    starty--;
  }
}


  return 0;
}

int checkPath(int* t, node** adj, int** marked, int x, int y, int size){
  int* xvals=malloc(sizeof(int)*size);
  int* yvals = malloc(sizeof(int)*size);
  for(int j =0; j < size;j++){
    xvals[j] = 0;
    yvals[j] = 0;
  }
  for(int i = 0 ; i < size; i++){
    xvals[i] = adj[t[i]]->x;
    yvals[i] = adj[t[i]]->y;
  }
  printw(" size = %d ",size);
  refresh();
  //works

  if(size ==3){
    if((xvals[0] == xvals[1] && xvals[1] == xvals[2]) || yvals[0] == yvals[1] && yvals[1] == yvals[2]){
        printw(" straight ");
        refresh();
        if(xvals[0] == xvals[1]){
          printw(" vertical ");
          refresh();
          //check for winning move
          if(yvals[2]-1 != -1){
            if(marked[yvals[2]-1][xvals[0]] == 0){
              return xvals[0];
            }
            for(int i = 0; i < 3; i++){
              printw(" looping ");
              refresh();
              if(marked[yvals[i]][xvals[i]] == 0){
                return xvals[i];
              }
            } //give back next column
          }
        }
        if(yvals[0] == yvals[1]){
          printw(" horizontal ");
          refresh();
          //check for winning move
          if(xvals[2]+1 != x){
            if(marked[yvals[0]][xvals[2]+1] == 0){
              return xvals[2]+1;
            }
          }
          if(xvals[0]-1 != -1){
            if(marked[yvals[0]][xvals[0]-1] == 0){
              return xvals[0]-1;
            }
          }
          if(marked[yvals[2]-1][xvals[2]] ==0){
            return xvals[2];
          }
          //return -1;
        }
        //return -1;
      }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Diagonals

    if((xvals[1]-1 != -1)&& (xvals[1]+1 != x) && (yvals[1]-1 != -1 && yvals[1]+1 != y)){
      if(xvals[0] == xvals[1]-1 && yvals[0] == yvals[1] - 1){
        /* x
              x
                  x*/
        // 0  to left of 1
        if(xvals[2]-1 != -1 && yvals[2]-1 != -1){
          if(xvals[1]==xvals[2]-1 && yvals[1] == yvals[2]-1){
            //officially left to right up

          }
        }
      }
      else if(xvals[0] == xvals[1]-1 && yvals[0] == yvals[1] + 1){
        if(xvals[2]-1 != -1 && yvals[2]+1 != y){
          if(xvals[1]==xvals[2]-1 && yvals[1] == yvals[2]+1){
            //officially left to right down
            if(yvals[0]+1 != y && xvals[2]+1 != x){
              if(marked[yvals[0]+1][xvals[2]+1] == 0){
                return xvals[2]+1;
              }
            }
          }
        }
      }
      //////////////////////////////////////////////
      if(xvals[0] == xvals[1]+1 && yvals[0] == yvals[1] - 1){

        if(xvals[2]-1 != -1 && yvals[2]-1 != -1){
          if(xvals[1]==xvals[2]+1 && yvals[1] == yvals[2]-1){
            //officially right to left  down
          }
        }
      }
      else if(xvals[0] == xvals[1]+1 && yvals[0] == yvals[1] + 1){
        if(xvals[2]+1 != -1 && yvals[2]+1 != y){
          if(xvals[1]==xvals[2]+1 && yvals[1] == yvals[2]-1){
            //officially right to left up
          }
        }
      }
    }
    /*else{
      printw(" not valid diagonal ");
      refresh();
      return -1;
    }*/
    size--;
  }

  if(size == 2){
  /*  printw(" path of size 2: %d, %d ",xvals[1], yvals[1]);
    refresh();
    printw("  y=%d ",yvals[1]);*/
    if(xvals[0] == xvals[1]){ // x vals stay same
      if(yvals[1]-1!= -1){ // make sure you're not reaching out of bounds
      printw(" same col ");
      refresh();
        if(marked[yvals[1]-1][xvals[0]] == 0){

        return xvals[1];
        }
      }
    }
   if(yvals[0] == yvals[1]){ // y vals stay the same
      if(xvals[0] == xvals[1]-1){ // x[0] to the left of x[1]
        printw(" x right ");
        refresh();
        if(xvals[1]+1 != x){ // make sure we aren't overreaching
          if(marked[yvals[0]][xvals[1]+1] ==0){
            return xvals[1]+1;
          }
        }
      }
       if(xvals[0] == xvals[1]+1){ // x[0] to right of x[1]
        if(xvals[1]-1 != -1){
          printw(" x left ");
          refresh();
          if(marked[yvals[0]][xvals[1]-1] ==0){
            return xvals[1]-1;
          }
        }
      }
    }
    //diagonals
   if(xvals[0] == xvals[1]+1){//right
     printw("R");
     refresh();
      if(yvals[0] == yvals[1]+1){//up
        printw(" right up ");
        refresh();
        if(yvals[1]-1 != -1 && xvals[1]+1 !=x){
          if(marked[yvals[1]-1][xvals[1]+1] == 0){
            return xvals[1]+1;
          }
        }
      }
    }
 if(xvals[0] == xvals[1]-1){//left
      if(yvals[0] == yvals[1]-1){//up
        printf(" left up ");
        refresh();
        if(yvals[1]-1 != -1 && xvals[1]-1 !=0){
          if(marked[yvals[1]-1][xvals[1]-1] == 0){
            return xvals[1]-1;
          }
        }
      }
    }
    if(yvals[1]-1 != -1){
    if(marked[yvals[1]-1][xvals[0]]==0){
      printw("hi");
      refresh();
      return xvals[0];
    }
    else if(marked[yvals[1]-1][xvals[1]]==0){
      printw("hi2");
      refresh();
      return xvals[1];
    }


    // maybe take end of 3 conntected to another block and reset the visited? FIXME
  /*  else if(xvals[1]+1 != x && yvals[1]-1 != -1){
      if(marked[yvals[1]][xvals[1]+1] == 0 || marked[yvals[1]-1][xvals[1]+1] ){
      printw("hi3 %d",xvals[1]+1);
      refresh();
      return xvals[1]+1;
      }
    }*/
    /*else{
      return 0;
    }*/
  }
  size--;
}


if(size == 1){

  if(yvals[0]-1 != -1){
    if(marked[yvals[0]-1][xvals[0]] == 0){
    return xvals[0];
    }
  }
  if(xvals[0] +1 != x ){
    if(marked[yvals[0]][xvals[0]+1] == 0){
    return xvals[0]+1;
    }
  }
   if(xvals[0]-1 != -1){

    if(marked[yvals[0]][xvals[0]-1] == 0 ){
    return xvals[0]-1;
    }
  }
  //diagonals
 if(xvals[0]-1 != -1 && yvals[0]-1 != -1 ){

    if(marked[yvals[0]-1][xvals[0]-1] == 0){
    return xvals[0]-1;
    }
  }
  if(xvals[0]+1 != x && yvals[0]-1 != -1){
    if(marked[yvals[0]-1][xvals[0]+1] == 0){
   printw(" 5TH if ");
    refresh();
    return xvals[0]+1;
    }
  }
}
printw("checkpath failed");
refresh();
  //use same logic as in selectCol to determine if path is straght or diagonal

return -1;
}

int computerSelect(WINDOW*** gb, int x, int y, int colorpair, int** marked, node** adj, int count){

 /*int select = 0;

    if(marked[y-1][0] ==1 && count == 0){
      select = 1;
      return select;
    }
    else if(count == 0 && marked[y-1][0] !=1){
      select = 0;
      return select;
    }

  int head, tail, w,type,greatestpath;
  node* temp;
  int type1 =0;
  int type2 = 0;
  int type3 = 0;

  initializeQueue(&head, &tail);
/*  initStack(&head, &tail);
  printw("hello");
  refresh();*/
  /*int* arr = malloc(sizeof(int)*count);
  int* visited= malloc(sizeof(int)*count);
  int empty = 0; //flag to check if queue is empty
  int path = 0; // shows length of path
    path = 0;
   int* t2;
    greatestpath=0;
    int f = 0;
    int t[3];
    int p[3];

  for(int i = 0; i < count; i++){
    //initializing arrays
    arr[i] = 0;
    visited[i] = 0;
  }

/*for(int i = 0; i < count; i++){
  printw(" || ");
  refresh();
for(int k = 0; k < count; k++){
  arr[k] = 0;
}
  for (int j = 1; j < 4; j++ ){
    type = j;
    path =0;
  push(i, &tail, arr);
  while(empty == 0){
    w = pop(&tail, arr);
    path++;
    if(type == 1){
      type1++;
    }
    if(type ==2){
      type2++;
    }
    if(type==3){
      type3++;
    }
    if(visited[w] ==0){
      visited[w] = 1;
      temp = adj[w]->next;
      while(temp){
        //if(type == temp->type){

        push(temp->v,&tail,arr);
        printw(" %d is %d to %d ",temp->v,type,w);
        refresh();
      //}
        temp = temp->next;
      }
    }
  empty = isEmpty(&head, &tail);
  }
  if(path > 3){
    printw(" 3 iterations ");
    refresh();
  }
}
}
for(int i = 0; i < count; i++){
  arr[i] = 0;
  visited[i] = 0;
}
free(arr);
//free(head);
//free(tail);
//free(t);
//free(p);
free(visited);
*/
/*  for(int i = 0; i < count; i++){
  /*  type1 = 0;
    type2 = 0;
    type3= 0;*/

  /*  printw(" || ");
    refresh();// makes sure all vertices are visited
    for(int j = 1; j < 4; j++){// iterates through all types
      type = j;
      path = 0;
       empty = 0;
       for(int k=0;  k <  count; k++){
         arr[k] =0;
          visited[k] = 0;
       }
       if(visited[i] == 0){

         for(int l = 0; l < 3; l++){
           t[l] = 0;
         }
         int whilecount =0;
         enqueue(&tail, arr, adj[i]->v);
         //path = 0;
         while(empty ==0){
           w = dequeue(arr,&head);
          // printw("visiting %d ",w);
           //refresh();
           if(whilecount != 0){
           if(type ==1){
             t[type1] = w;
             printw(" %d ", type1);
            f++;

             type1++;
             if(type1 ==3){
              t2 = t;
          //   select = checkPath(t2,adj,marked,x,y,3);
              if(select != -1){
                return select;
              }
            }

             printw(" type1 == %d ", type1);
             refresh();
           }
           if(type==2){
             type2++;
             t[f] = w;
             printw(" type2 == %d ", type2);
            f++;
            if(type2 ==3){
              t2 = t;
             select = checkPath(t2,adj,marked,x,y,3);
             if(select != -1){
               return select;
             }
            }
            // refresh();
           }
           if(type ==3){
             type3++;
             t[f] = w;
            f++;
             if(type1 ==3){
                t2 = t;
              select = checkPath(t2,adj,marked,x,y,3);
              if(select != -1){
                return select;
              }
             }
             //printw(" type3 == %d ", type3);
             //refresh();
           }
         }

          path++;
             if(visited[w]==0){



               visited[w] = 1;
              //printw("check");
               //refresh();


            temp = adj[i]->next;
            while(temp){
              if(temp->type == type && visited[temp->v] == 0){
               //printw(" %d %d ", type, temp->v);
              //refresh();

                enqueue(&tail, arr, temp->v);

              }
              temp = temp->next;
            }
            }
            whilecount++;
              empty = isEmpty(&head,&tail);
     }

      if(path > greatestpath){
        greatestpath = path;
        for(int a = 0 ; a < 3; a++){
          p[a] = t[a];
        }
        printw(" new greatest path = %d ",path);
        refresh();
      }

    }
  }
}
*/

  ////////////////////////////////////////////////////////////////////////

//base cases
int select = 0;
  if(marked[y-1][0] ==1 && count == 0){
    select = 1;
    return select;
  }
  else if(count == 0 && marked[y-1][0] !=1){
    select = 0;
    return select;
  }

int head, tail, w;
node* temp;
initializeQueue(&head, &tail);
int* arr = malloc(sizeof(int)*count);
int* visited= malloc(sizeof(int)*count);
for(int i = 0; i < count; i++){ //initializing arrays
  visited[i] = 0;
  arr[i] = 0;
}
int empty = 0; //flag to check if queue is empty
int path = 0; // shows length of path
  path = 0;
  int f = 0;
  int t[3];
  for(int i = 0; i < count; i++){
    for(int j = 0; j < count; j++){
      visited[j] = 0;
    }// makes sure all nodes can be visited even if not connected
    if(visited[i] == 0){
      for(int j = 0 ; j < 3; j++){
        t[j] = 0;
      }
      enqueue(&tail, arr, adj[i]->v);
      i=0;
      path = 0;
  while(i == 0){

    w = dequeue(arr,&head);
      if(visited[w]==0){
        path++;
        visited[w] = 1;
        printw("check");
        refresh();
        t[f] = w;
        f++;
        temp = adj[w]->next;
        while(temp){
          enqueue(&tail, arr, temp->v);
          temp = temp->next;
        }

      }

      if(path ==3){
        int* t2 = t;
        select = checkPath(t2,adj,marked,x,y,3);
        if(select != -1){

          return select;
        }
        //select = checkPath(t2,adj,marked,x,y,2);
        //if(select != -1){
        //  return select;
        //}
        printw("heyo");
        refresh();
        path = 0;
        f = 0;
        for(int i = 0; i < 3; i++){
          t[i] = 0;
        }
      }
      printw(" path = %d ",path);
      refresh();
    i = isEmpty(&head,&tail);
  }
    if(path == 1){
      int* t2 = t;
      select = checkPath(t2,adj,marked,x,y,1);
      return select;
    }
    if(path == 2){
      int* t2 = t;
      select = checkPath(t2,adj,marked,x,y,2);
      if(select != -1){
      return select;
    }
  }
  }
}

//breadth first search
getch();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
return 0;
}


//function for actual game process
int runGame(WINDOW*** gb, int x, int y, int mode){
int colorcheck = 1; // alternates players
int winner =0; //marker int to check if game should terminate
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
  if(colorcheck%2 == 1 &&(mode ==1 || mode==2)){
  col = selectCol(gb,x,y,colorcheck % 2, marked); //select the column player wishes to move to
  moveSpot(gb, col, colarr[col],y, colorcheck % 2); // move game piece down to lowest unoccupied spot in the column
}
if(colorcheck %2== 0 && mode ==1){
//int* selected; //pointer to store return value of what the AI determines is the best x just like select col

  col = computerSelect(gb,x,y,colorcheck % 2, marked, p2adj, p2count);

  moveSpot(gb,col, colarr[col], y, colorcheck % 2);
}
else if(colorcheck%2 == 0 && mode ==2){
  col = selectCol(gb,x,y,colorcheck % 2, marked);
  moveSpot(gb, col, colarr[col],y, colorcheck % 2);
}
//adding to adjacency list and cheking for a winner
  if(colorcheck %2 == 1){
    marked[y-1-colarr[col]][col] = 1;
    colarr[col]++;
      if(p1count > p1cap-1){
        p1cap = p1cap * 2;
      p1adj =  adjResize(p1adj, p1cap);
      }
      struct node* newNode = createNode(col, y-colarr[col], p1count);
      addToAdjacency(p1adj, newNode, col, y-colarr[col], p1count);
      p1count++;
      winner = checkForWinner(1,p1count,marked, col,y-colarr[col],x,y);
  }
  else{

    marked[y-1-colarr[col]][col] = 2;
    colarr[col]++;
    if(p2count > p2cap-1){
      p2cap = p2cap * 2;
    p2adj =  adjResize(p1adj, p1cap);
    }
    struct node* newNode = createNode(col, y-colarr[col], p2count);
    addToAdjacency(p2adj, newNode, col, y-colarr[col], p2count);
    p2count++;
  winner =  checkForWinner(2,p2count, marked, col, y-colarr[col], x, y);
  }
  //checking to see if winner has been determined and freeing allocated memory if so
  if(winner ==1 || winner == 2){
    for(int i = 0; i < y; i++){
        free(marked[i]);
    }
    free(marked);
    free(p1adj);
    free(p2adj);
  if(winner == 1){
    return 1;
  }
if(winner == 2){
  return 2;
}

  }
  colorcheck++;
  ch = getch();
}

}
