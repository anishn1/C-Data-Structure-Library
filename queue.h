
#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
  void **data;
  int size;
  int capacity;
  int head;
  int tail;
} Queue;

#endif //QUEUE_H
