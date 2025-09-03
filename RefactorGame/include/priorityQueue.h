#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "common.h"

  PriorityQueue createPriorityQueue();
  void enqueue(PriorityQueue *pq, Tile *tile);
  void dequeue(PriorityQueue *pq);
  void peek(PriorityQueue *pq);
  void printQueue(PriorityQueue *pq);
  int getSize(PriorityQueue *pq);

#endif
