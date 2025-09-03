#include "queue.h"

Queue createQueue(){
  Queue q;
  q.front = NULL;
  q.rear = NULL;
  q.size = 0;
  return q;
}

void enqueue(Queue *q, Tile *tile){
  if(q->front == NULL){
    q->front = q->rear = tile;
    q->size++;
    return;
  }
  q->rear->next = tile;
  q->rear = tile;
  q->size++;
}

Tile *dequeue(Queue *q){
  if(q->front == NULL) return NULL;
  Tile *temp = q->front;
  q->front = q->front->next;
  q->size--;
  return temp;
}

Tile *peek(Queue *q){
  return q->front;
}

int getSize(Queue *q){
  return q->size;
}
