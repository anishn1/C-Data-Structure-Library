
#ifndef BINHEAP_H
#define BINHEAP_H
#include "array.h"

typedef struct {
  GeneralArray *arr;
  int (*cmp)(void *, void *);
} BinHeap;

#endif //BINHEAP_H
