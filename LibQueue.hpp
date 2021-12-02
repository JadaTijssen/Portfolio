#ifndef LIBQUEUE_HPP
#define LIBQUEUE_HPP

using namespace std;

#include <iostream>
#include <float.h>
#include <assert.h>

typedef struct Queue {
  int *array;
  int back;
  int front;
  int size;
} Queue;

Queue newQueue (int s);
int isEmptyQueue(Queue q);
void queueEmptyError();
void enqueue(int item, Queue *qp);
int dequeue(Queue *qp);
void freeQueue(Queue q);

#endif
