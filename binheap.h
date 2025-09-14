
#ifndef BINHEAP_H
#define BINHEAP_H
#include "array.h"

typedef struct {
  GeneralArray *arr;
  int (*cmp)(void *, void *);
} BinHeap;

BinHeap* createHeap(int capacity, int (*cmp)(void*, void*));
void destroyHeap(BinHeap* heap);
void insertHeap(BinHeap* h, void *data);
void *extractHeap(BinHeap *h);

#endif //BINHEAP_H
