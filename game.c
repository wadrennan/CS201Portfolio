#include <stdlib.h>
#include <curses.h>
#include "UI.h"
#include "stack.h"
//uses adjacency list because adjacency matrix would have much unneeded space, especially on a large graph
//a graph is an array of adjacency lists
typedef  struct node{
  int x; //x coord
  int y; //y coord
  int v; // vertex number
  int visited;
  int type; // 1 = vert 2 = horizontal
  struct node* next; //for adj lists
  struct node** adj; //pointer to p1 or p2 adj list
}node;

struct node* createNode(int x, int y, int v){

  node* newNode = malloc(sizeof(node));
  newNode->x = x;
  newNode->y = y;
  newNode->v = v;
  newNode->type = 0;

  newNode->next = NULL;
  return newNode;
} //creates a new node

node** adjResize(node** adj, int cap){
  struct node** resize = malloc(sizeof(node) * cap);
  for(int i = 0 ; i < cap/2; i++){
    resize[i] = adj[i];
    adj[i]->adj = resize;
  }
  for(int j = cap/2 ; j < cap; j++){
    resize[j] = NULL;
  }

  return resize;
} //resizes the adj list

void addToAdjacency(struct node** adj, struct node* newNode, int x, int y, int v){
  adj[v] = newNode;
  for(int i = 0; i < v; i++){
     // if x is is equal and y is 1 less or more, or if y is equal and x +-1
    if((adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1)) || (adj[i]->y == y && (adj[i]->x == x-1 || adj[i]->x == x+1))){
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
        temp2->type = 1; //type 1 = vertical adjacency
      }
      else if((adj[i]->x == x+1 || adj[i]->x == x-1) && adj[i]->y == y){
        temp2->type = 2; // type 2 = horizontal adjacency
      }
      temp2->next = NULL;
      temp2->adj = NULL;
      temp->next = temp2; // add the appropriate nodes to the new nodes adjacency list
      struct node* temp3 = malloc(sizeof(node));
      struct node* temp4 = malloc(sizeof(node));
      temp3 = adj[i];
      while(temp3->next){
        temp3 = temp3->next;

      }
      temp4->x = newNode->x;
      temp4->y = newNode->y;
      temp4->v = newNode->v;
      if(adj[i]->x == x && (adj[i]->y == y-1 || adj[i]->y == y+1)){
        temp4->type = 1;
     }
     else if(adj[i]->y == y && (adj[i]->x == x-1 || adj[i]->x == x+1)){

       temp4->type = 2;
     }
      temp4->next = NULL;
      temp3->next = temp4; // add the new node to its adjacent vertices' adjacency lists
    }
}
  return;
}

int checkForWinner(int p, int count, int** marked, int x, int y, int width, int height ){
  /*iterate through every node in adj list (number of vertices) and get their xy coords, check all around for neighbors*/
  if(count < 4){
    return 0;
  }
  int counter = 0;

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

      return 2;
    }
  }


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

    return 2;
  }

  starty--;
  startx++;
}

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

      return 2;
    }
    startx--;
    starty--;
  }
}


  return 0;
}

int Check(int t[3], node** adj, int x, int y, int** marked, int count, int type){ //checks for winning moves
  int  min;
  int max;
  //find y val closest to top (top == 0, so the minimum value) and check above for a move
  if(type == 1){
    min = adj[t[0]]->y;
    for(int i = 0; i < 3; i++){
      if(adj[t[i]]->y < min){
        min = adj[t[i]]->y;
      }
    }
    if(min-1 != -1){
      if(marked[min-1][adj[t[0]]->x] == 0 ){
        return adj[t[0]]->x;
      }
    }

    return -1;
  }
  else{
    //find min and max x val
    // check the max+1 minx-1 x val for y that's in line
    min = adj[t[0]]->x;
    max = adj[t[0]]->x;

    for(int i = 0; i < 3; i++){
      if(adj[t[i]]->x < min){
        min = adj[t[i]]->x;
      }
      else if(adj[t[i]]->x > max){
        max = adj[t[i]]->x;
      }
    }
    if(max+1 != x){
      if(marked[adj[t[0]]->y][max+1] == 0){
        return max+1;
      }
    }
    if(min-1 != -1){
      if(marked[adj[t[0]]->y][min-1] == 0){
        return min-1;
      }
    }

    return -1;
  }

}

int finalCheck(int t[3], node** adj, int x, int y, int** marked, int count, int type){ //checks for 2 or 1 spot moves
  int min, max;

//check for vertical 2 spot moves then vertical 1 spot moves
  if(type == 1){
    if(count > 1){
      min = adj[t[0]]->y;
      for(int i = 0; i < count; i++){
        if(adj[t[i]]->y < min){
          min = adj[t[i]]->y;
        }
      }
      if(min-1 != -1){

        if(marked[min-1][adj[t[0]]->x] == 0 ){
          return adj[t[0]]->x;
        }
      }
      return -1;
    }
    else{
      int  xval = adj[t[0]]->x;
      int yval = adj[t[0]]->y;
      if(yval-1 != -1){
        if(marked[yval-1][xval] == 0){
          return xval;
        }
      }
      return -1;
    }
  }
  //check for horizontal 2 spot moves and 1 spot moves
  else{
    if(count > 1){
      min = adj[t[0]]->x;
      max = adj[t[0]]->x;

      for(int i = 0; i < count; i++){
        if(adj[t[i]]->x < min){
          min = adj[t[i]]->x;
        }
        else if(adj[t[i]]->x > max){
          max = adj[t[i]]->x;
        }
      }

      if(max+1 != x){
        if(marked[adj[t[0]]->y][max+1] == 0){
          return max+1;
        }
      }
      if(min-1 != -1){
        if(marked[adj[t[0]]->y][min-1] == 0){
          return min-1;
        }
      }
      return -1;
    }
    else{
      int  xval = adj[t[0]]->x;
      int yval = adj[t[0]]->y;
      if(xval+1 != x){
        if(marked[yval][xval+1] == 0){
          return xval+1;
        }
      }
      if(xval-1 != -1){
        if(marked[yval][xval-1] == 0){
          return xval-1;
        }
      }
      return -1;
    }
  }
}
int pickOne(int** marked, int x, int y, int count, node** adj){ //if all else fails pick a random one
  int r;
  if(x > 31){
    x = 30;
  }
 while(1){
    r = rand() % x;
    if(marked[y-2][r] == 0){
      return r;
    }
  }
}

int denfenseDFS(node** adj, int** marked, int x, int y, int count){ //defense first AI, blocks horizontal and vertical groups of 3 from opponent
    int select;
    int type1 = 0;
    int type2 = 0;
    int type1arr[3];
    int type2arr[3];
    //int type3 = 0;
      struct node* temp;
      if(marked[y-1][0] ==1 && count == 0){
        select = 1;
        return select;
      }
      else if(count == 0 && marked[y-1][0] !=1){
        select = 0;
        return select;
      }

      int head,tail, m;
      int empty = 0;
      int check;
      int flag;
      initializeStack(&head,&tail);
      int* arr = malloc(sizeof(int)*count); //stack array
      int* visited = malloc(sizeof(int)*count);
      for(int i = 0 ; i < count; i++){ //assure you visit every node
        empty = 0;
         type1 = 1;
         type2 = 1;
         for(int j = 0 ; j < 3; j++){
           type1arr[j] = -1;
           type2arr[j] = -1;
         }
        for(int j = 0; j < count; j++){
          visited[j] = 0;
        }
        type1arr[0] = adj[i]->v;
        type2arr[0] = adj[i]->v;
        type1++;
        type2++;
        push(&tail, arr, adj[i]->v);
        while(empty == 0){
          m = pop(arr, &tail);
          if(visited[m] == 0){
            visited[m] = 1;
            temp= adj[i]->next;
            while(temp){
              //check for types and increment accordingly add to arrays
              //if type1 == 3 or type2 ==3
              if(visited[temp->v] == 0){
              if(temp->type ==1){
               flag = 0;
                for(int k = 0; k < type1; k++){
                  if(type1arr[k] == temp->v){
                    flag = 1;
                  }
                }
                if(flag == 0){
                type1arr[type1-1] = temp->v;
                type1++;

                }
              }
                if(type1 == 4){
                  check = Check(type1arr, adj, x,y,marked, type1-1, 1);
                  if(check!= -1){
                    return check;
                  }
                  type1 = 1;
                  type1arr[0]= adj[i]->v;
                  for(int j = 1; j < 3; j++){
                    type1arr[j] = -1;
                  }
                }

              if(temp->type == 2){
                flag = 0;
                for(int k = 0; k < type2; k++){
                  if(type2arr[k] == temp->v){
                    flag = 1;
                  }
                }
                if(flag == 0){
                type2arr[type2-1] = temp->v;
                type2++;
              }
                if(type2 == 4){
                check = Check(type2arr, adj, x,y,marked, type2-1, 2);
                if(check!= -1){
                  return check;
                }
                type2 = 1;
                type2arr[0] = adj[i]->v;
                for(int j = 1; j < 3; j++){
                  type2arr[j] = -1;
                }
                }
              }
              push(&tail,arr,temp->v);
            }
            temp = temp->next;
            }
          }
          empty = isEmpty(&head, &tail);
        }
      }
      return -1;
}

int DFS(node** adj, int** marked, int x, int y, int count){
  int select;
  int type1 = 0;
  int type2 = 0;
  int type1arr[3];
  int type2arr[3];
  //int type3 = 0;
    struct node* temp;
    if(marked[y-1][0] ==1 && count == 0){
      select = 1;
      return select;
    }
    else if(count == 0 && marked[y-1][0] !=1){
      select = 0;
      return select;
    }

    int head,tail, m;
    int empty = 0;
    int check;
    int flag;
    initializeStack(&head,&tail);
    int* arr = malloc(sizeof(int)*count); //stack array
    int* visited = malloc(sizeof(int)*count);
    for(int i = 0 ; i < count; i++){ //assure you visit every node
      empty = 0;
       type1 = 1;
       type2 = 1;
       for(int j = 0 ; j < 3; j++){
         type1arr[j] = -1;
         type2arr[j] = -1;
       }
      for(int j = 0; j < count; j++){
        visited[j] = 0;
      }
      type1arr[0] = adj[i]->v;
      type2arr[0] = adj[i]->v;
      type1++;
      type2++;
      push(&tail, arr, adj[i]->v);
      while(empty == 0){
        m = pop(arr, &tail);
        if(visited[m] == 0){
          visited[m] = 1;
          temp= adj[i]->next;
          while(temp){
            //check for types and increment accordingly add to arrays
            //if type1 == 3 or type2 ==3
            if(visited[temp->v] == 0){
            if(temp->type ==1){
             flag = 0;
              for(int k = 0; k < type1; k++){
                if(type1arr[k] == temp->v){
                  flag = 1;
                }
              }
              if(flag == 0){

              type1arr[type1-1] = temp->v;
              type1++;

              }
            }
              if(type1 == 4){

                check = Check(type1arr, adj, x,y,marked, type1-1, 1);
                if(check!= -1){
                  return check;
                }
                type1 = 1;
                type1arr[0]= adj[i]->v;
                for(int j = 1; j < 3; j++){
                  type1arr[j] = -1;
                }
              }

            if(temp->type == 2){
              flag = 0;
              for(int k = 0; k < type2; k++){
                if(type2arr[k] == temp->v){
                  flag = 1;
                }
              }
              if(flag == 0){
              type2arr[type2-1] = temp->v;
              type2++;
            }
              if(type2 == 4){

              check = Check(type2arr, adj, x,y,marked, type2-1, 2);
              if(check!= -1){
                return check;
              }

              type2 = 1;
              type2arr[0] = adj[i]->v;
              for(int j = 1; j < 3; j++){
                type2arr[j] = -1;
              }
              }
            }
            push(&tail,arr,temp->v);
          }
          temp = temp->next;
          }
        }
        empty = isEmpty(&head, &tail);
      }
    }
      // check paths of left over arrays
      if(type1 == type2){

        check = finalCheck(type1arr, adj, x,y,marked, type1-1, 1);
        if(check != -1){
          return check;
        }
        check = finalCheck(type2arr, adj, x,y,marked, type2-1, 2);
      }
      if(type1 > type2){

        check = finalCheck(type1arr, adj, x,y,marked, type1-1, 1);
        if(check != -1){
          return check;
        }
      }
      if(type1<type2){

        check = finalCheck(type2arr, adj, x,y,marked, type2-1, 2);
        if(check != -1){
          return check;
        }
      }
  return pickOne(marked, x, y, count, adj);
}

//function for actual game process
int runGame(WINDOW*** gb, int x, int y, int mode, int mainx, int mainy){
WINDOW* coords = newwin(10,35,mainy-4,mainx-35);
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
int col, p1count, p2count, p1cap, p2cap;
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
  col = selectCol(gb,x,y,colorcheck % 2, marked, coords); //select the column player wishes to move to

  if(col < 31){

      moveSpot(gb, col, colarr[col],y, colorcheck % 2); // move game piece down to lowest unoccupied spot in the column
  }
}
if(colorcheck %2== 0 && mode ==1){
  col = denfenseDFS(p1adj,marked,x,y,p1count);
  if(col != -1 && col < 30){
    moveSpot(gb,col, colarr[col], y, colorcheck % 2);
  }
  else{
    col = DFS(p2adj, marked, x, y, p2count);

    if(col < 30){
    moveSpot(gb,col, colarr[col], y, colorcheck % 2);
    }
  }
}
else if(colorcheck%2 == 0 && mode ==2){
  col = selectCol(gb,x,y,colorcheck % 2, marked, coords);
  if(col < 30){
  moveSpot(gb, col, colarr[col],y, colorcheck % 2);
  }
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
    p2adj =  adjResize(p2adj, p2cap);
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
return 0;
}
