#ifndef _queue_h
#define _queue_h
void initializeQueue(int* head, int* tail);

int isEmpty(int* head, int* tail);

int isFull(int tail, int size);

void enqueue(int* tail, int* arr, int val);

int dequeue(int* arr, int* head);

void queueResize(int* arr, int size, int** marked);

int peek(int* tail, int* arr);

int pop(int* arr, int* tail);

void push(int* tail, int* arr, int val);

void stackResize(int* arr, int size);

void initializeStack(int* head, int* tail);


#endif
