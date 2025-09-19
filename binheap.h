
#ifndef BINHEAP_H
#define BINHEAP_H
#include "array.h"
#include <stdbool.h>

typedef struct {
  Array *arr;
  int (*cmp)(void *, void *);
} BinHeap;

BinHeap* createHeap(int capacity, int (*cmp)(void*, void*));
void destroyHeap(BinHeap* heap, void (*freeFunc)(void *));
void insertHeap(BinHeap* h, void *data);
void *extractHeap(BinHeap *h);
int sizeHeap(BinHeap* h);
bool isEmptyHeap(BinHeap* h);
Array *heapSort(BinHeap *h);

#endif //BINHEAP_H
