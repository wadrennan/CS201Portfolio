#include <stdlib.h>
/* Some code may be similar to http://www.zentut.com/c-tutorial/c-queue/ but obviously with a stack implementation*/

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

void initializeStack(int* head, int* tail){

  *head = 0;
  *tail = 0;
  return;
}

void push(int* tail, int* arr, int val){
  arr[(*tail)] = val;
  (*tail)++;
  return;
}

int pop(int* arr, int* tail){

  (*tail)--;

  return arr[*tail];
}
