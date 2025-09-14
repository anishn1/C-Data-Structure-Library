
#ifndef BINHEAP_H
#define BINHEAP_H
#include "array.h"
#include <stdbool.h>

typedef struct {
  GeneralArray *arr;
  int (*cmp)(void *, void *);
} BinHeap;

BinHeap* createHeap(int capacity, int (*cmp)(void*, void*));
void destroyHeap(BinHeap* heap);
void insertHeap(BinHeap* h, void *data);
void *extractHeap(BinHeap *h);
int sizeHeap(BinHeap* h);
bool isEmptyHeap(BinHeap* h);
GeneralArray *heapSort(BinHeap *h);

#endif //BINHEAP_H
