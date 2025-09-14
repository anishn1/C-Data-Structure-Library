
#include "binheap.h"
#include "array.h"
#include <assert.h>
#include <stdlib.h>

BinHeap* createHeap(int capacity, int (*cmp)(void*, void*)) {
  BinHeap* heap = malloc(sizeof(BinHeap));
  assert(heap != NULL);
  heap->arr = createGeneralArray(capacity);
  assert(heap->arr != NULL);
  heap->cmp = cmp;
  return heap;
}

void destroyHeap(BinHeap* heap) {
  destroyGeneralArray(heap->arr);
  free(heap);
}

void heapify_up(BinHeap* h, int index) {
  int i = index;
  while (i > 0) {
    int parent = (i-1)/2;
    if (h->cmp(h->arr->data[i], h->arr->data[parent]) < 0) {
      void *temp = h->arr->data[i];
      h->arr->data[i] = h->arr->data[parent];
      h->arr->data[parent] = temp;
      i = parent;
    } else {
      return;
    }
  }
}

void insertHeap(BinHeap* h, void *data) {
  addGeneralArray(h->arr, data);
  heapify_up(h, h->arr->size - 1);
}