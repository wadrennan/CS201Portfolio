#include <stdlib.h>
/* Some code may be similar to http://www.zentut.com/c-tutorial/c-queue/*/
void initializeQueue(int* head, int* tail){
  *head = 0;
  *tail = 0;
  return;
}
int isEmpty(int* head, int* tail){
  if((*head) == (*tail)){
    return 1;
  }
  return 0;
}

int isFull(int tail, int size){
  if(tail == size){
    return 1;
  }
  return 0;
}
//hie
void enqueue(int* tail, int* arr, int val){
  arr[(*tail)] = val;
  (*tail)++;
  return;
}

int dequeue(int* arr, int* head){
  (*head)++;
  return arr[(*head)-1];
}

void queueResize(int* arr, int size){
  int* temp = malloc(sizeof(int)*(size*2));
  for(int i = 0 ; i < size; i++){
    temp[i] = arr[i];
  }
  for(int j = size; j < size*2; j++){
    temp[j] = 0;
  }
  arr = temp;
  return;
}

void initializeStack(int* head, int* tail){

  *head = 0;
  *tail = 0;
  return;
}

void push(int* tail, int* arr, int val){
  arr[(*tail)] = val;
/*  printw("pushed");
  refresh();*/
  (*tail)++;
  //printf("tail now %d with val %d\n", *tail, val);
  return;
}

int pop(int* arr, int* tail){

  (*tail)--;
//  printw("popping %d ",arr[*tail]);
//  refresh();
  return arr[*tail];
}
