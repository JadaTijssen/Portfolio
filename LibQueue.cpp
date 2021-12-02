#include <iostream>
#include <float.h>
#include <assert.h>
#include "LibQueue.hpp"

Queue newQueue (int s) {
  Queue q;
  q.array = new int[s];
  assert(q.array != NULL);
  q.back = 0;
  q.front = 0;
  q.size = s;
  return q;
}

int isEmptyQueue (Queue q) {
  return (q.back == q.front);
}

void queueEmptyError() {
  std::cout << "queue empty" << endl;
  abort();
}

void enqueue (int item, Queue *qp) {
  qp->array[qp->back] = item;
  qp->back = (qp->back + 1) % qp->size;
}

int dequeue (Queue *qp) {
  int item;
  if (isEmptyQueue(*qp)) {
    queueEmptyError();
  }
  item = qp->array[qp->front];
  qp->front = (qp->front + 1) % qp->size;
  return item;
}

void freeQueue (Queue q) {
  free(q.array);
}
