
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

void heapify_down(BinHeap* h, int index) {
  int smallest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  if (left < h->arr->size) {
    if (h->cmp(h->arr->data[left], h->arr->data[smallest]) < 0) {
      smallest = left;
    }
  }
  if (right < h->arr->size) {
    if (h->cmp(h->arr->data[right], h->arr->data[smallest]) < 0) {
      smallest = right;
    }
  }
  if (smallest != index) {
    void *temp = h->arr->data[index];
    h->arr->data[index] = h->arr->data[smallest];
    h->arr->data[smallest] = temp;

    heapify_down(h, smallest);
  }
}

void *extractHeap(BinHeap *h) {
  assert(h->arr->size > 0);
  void *data = getGeneralArray(h->arr, 0);
  h->arr->data[0] = h->arr->data[h->arr->size - 1];
  removeGeneralArray(h->arr, h->arr->size - 1);
  heapify_down(h, 0);
  return data;
}