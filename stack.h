#ifndef _queue_h
#define _queue_h
void initializeQueue(int* head, int* tail);

int isEmpty(int* head, int* tail);

int isFull(int tail, int size);

int pop(int* arr, int* tail);

void push(int* tail, int* arr, int val);

void initializeStack(int* head, int* tail);


#endif
