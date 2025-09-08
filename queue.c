
#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

Queue *createQueue(int capacity) {
  Queue *queue = malloc(sizeof(Queue));
  assert(queue != NULL);
  queue->capacity = capacity;
  if (queue->capacity <= 0) {
    queue->capacity = 16;
  }
  queue->data = malloc(queue->capacity * sizeof(void *));
  assert(queue->data != NULL);
  queue->size = 0;
  queue->head = 0;
  queue->tail = 0;
  return queue;
}

void destroyQueue(Queue *queue) {
  free(queue->data);
  free(queue);
}

void *dequeue(Queue *queue) {
  assert(queue != NULL);
  assert(queue->size > 0);
  void *data = queue->data[queue->head];
  queue->head = (queue->head + 1) % queue->capacity;
  queue->size--;
  return data;
}

bool isEmptyQueue(Queue *queue) {
  return (queue->size == 0);
}

bool isFullQueue(Queue *queue) {
  return (queue->size == queue->capacity);
}

void resizeQueue(Queue *queue) {
  int newCapacity = queue->capacity * 2;
  void **newData = malloc(newCapacity * sizeof(void *));
  for (int i=0; i < queue->size; i++) {
    newData[i] = queue->data[(queue->head + i) % queue->capacity];
  }
  free(queue->data);
  queue->data = newData;
  queue->capacity = newCapacity;
  queue->head = 0;
  queue->tail = queue->size;
}

bool enqueue(Queue *queue, void *data) {
  assert(queue != NULL);
  if (isFullQueue(queue)) {
    resizeQueue(queue);
  }
  queue->data[queue->tail] = data;
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->size++;
  return true;
}

void forEachQueue(Queue *queue, void (*func)(void *elem)) {
  for (int i = queue->head; i != queue->tail; i = (i + 1) % queue->capacity) {
    func(queue->data[i]);
  }
}

void *peek(Queue *queue) {
  assert(queue != NULL);
  assert(queue->size > 0);
  return queue->data[queue->head];
}

void *peekBack(Queue *queue) {
  assert(queue != NULL);
  assert(queue->size > 0);
  int last = (queue->tail + queue->capacity - 1) % queue->capacity;
  return queue->data[last];
}