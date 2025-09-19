
#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct {
  void **data;
  int size;
  int capacity;
} Array;

Array *createArray(int capacity);
void destroyArray(Array *arr, void (*freeFunc)(void *));
void addArray(Array *arr, void *element);
void *removeArray(Array *arr, int index);
void *getArray(Array *arr, int index);
void *setArray(Array *arr, void *element, int index);
bool isEmptyArray(Array *arr);
int sizeArray(Array *arr);
void *popArray(Array *arr);
void insertArray(Array *arr, void *element, int index);
void clearArray(Array *arr, void (*free)(void *element));
void resizeArray(Array *arr, int newCapacity);
bool containsArray(Array *arr, void *element, int (*compareFunc)(void *, void *));
int indexOfArray(Array *arr, void *element, int (*compareFunc)(void *, void*));
void forEachArray(Array *arr, void (*func)(void *));
void sortArray(Array *arr, int (*compareFunc)(void *, void *));
#endif //ARRAY_H
