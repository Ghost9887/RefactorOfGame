#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

  Queue createQueue();
  void enqueue(Queue *q, Tile *tile);
  Tile *dequeue(Queue *q);
  Tile *peek(Queue *q);

  
#endif
