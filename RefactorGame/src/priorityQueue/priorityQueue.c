#include "priorityQueue.h"


PriorityQueue createPriorityQueue(){
  PriorityQueue pQueue;
  pQueue.front = NULL;
  pQueue.rear = NULL;
  return pQueue;
}

void enqueue(PriorityQueue *pq, Tile *tile){
  if(pq->front == NULL){
    pq->front = pq->rear = tile;
    return;
  }
  if(tile->fCost > pq->front->fCost){
    tile->next = pq->front;
    return;
  }
  Tile *current = pq->front;
  while(current->next != NULL && current->next->fCost >= tile->fCost){
    current = current->next;
  }
  tile->next = current->next;
  pq->size++;
  if(tile->next == NULL){
    pq->rear = tile;
  }
}

void dequeue(PriorityQueue *pq){
  if(pq->front == NULL){
    return;
  }
  Tile *temp = pq->front;
  int data = temp->fCost;
  pq->front = pq->front->next;
  if(pq->front == NULL){
    pq->rear = NULL;
  }
  pq->size--;
}

void peek(PriorityQueue *pq){
  printf("peek: %d", pq->front->fCost);
}

void printQueue(PriorityQueue *pq){
  if (pq->front == NULL) {
    printf("Queue is empty!\n");
    return;
  }
  Tile *current = pq->front;
  printf("Queue: ");
  while (current != NULL) {
    printf("%d -> ", current->fCost);
    current = current->next;
  }
  printf("NULL\n");
}

int getSize(PriorityQueue *pq){
  return pq->size;
}
