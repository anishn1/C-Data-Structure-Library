
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "array.h"

Array *createArray(int capacity) {
	Array *arr = malloc(sizeof(Array));
	assert(arr != NULL);
    if (capacity <= 0) {
      arr->capacity = 16;
    } else {
	  arr->capacity = capacity;
    }
	arr->size = 0;
	arr->data = malloc(sizeof(void *) * arr->capacity);
	assert(arr->data != NULL);
	return arr;
}

void destroyArray(Array *arr, void (*freeFunc)(void *)) {
	forEachArray(arr, freeFunc);
	free(arr->data);
	free(arr);
}

void addArray(Array *arr, void *element) {
	if (arr->size == arr->capacity) {
		arr->capacity *= 2;
		arr->data = realloc(arr->data, sizeof(void *) * arr->capacity);
		assert(arr->data != NULL);
	}
	arr->data[arr->size] = element;
	arr->size++;
}

void *getArray(Array *arr, int index) {
	assert(index >= 0 && index < arr->size);
	return arr->data[index];
}

bool isEmptyArray(Array *arr) {
	return arr->size == 0;
}

int sizeArray(Array *arr) {
	return arr->size;
}

void *removeArray(Array *arr, int index) {
	assert(index >= 0 && index < arr->size);
	void *element = arr->data[index];
	for (int i = index; i < arr->size - 1; i++) {
		arr->data[i] = arr->data[i + 1];
	}
	arr->size--;
	return element;
}

void *popArray(Array *arr) {
	void *element = getArray(arr, arr->size - 1);
	removeArray(arr, arr->size - 1);
	return element;
}

void setArray(Array *arr, void *element, int index) {
	assert(index >= 0 && index < arr->size);
	arr->data[index] = element;
}

void insertArray(Array *arr, void *element, int index) {
	if (arr->size == arr->capacity) {
		arr->capacity *= 2;
		arr->data = realloc(arr->data, sizeof(void *) * arr->capacity);
		assert(arr->data != NULL);
	}
	for (int i = arr->size - 1; i >= index; i--) {
		arr->data[i+1] = arr->data[i];
	}
	arr->data[index] = element;
	arr->size++;
}

void clearArray(Array *arr, void (*freeFunc)(void *)) {
	forEachArray(arr, freeFunc);
	arr->size = 0;
}

void resizeArray(Array *arr, int newCapacity) {
	assert(newCapacity >= arr->size);
	arr->capacity = newCapacity;
	arr->data = realloc(arr->data, sizeof(void *) * newCapacity);
	assert(arr->data != NULL);
}

bool containsArray(Array *arr, void *element, int (*compareFunc)(void *, void *)) {
	for (int i = 0; i < arr->size; i++) {
		if (compareFunc(arr->data[i], element) == 0) {
			return true;
		}
	}
	return false;
}

int indexOfArray(Array *arr, void *element, int (*compareFunc)(void *, void*)) {
	for (int i = 0; i < arr->size; i++) {
		if (compareFunc(arr->data[i], element) == 0) {
			return i;
		}
	}
  return -1;
}

void forEachArray(Array *arr, void (*func)(void *)) {
	for (int i = 0; i < arr->size; i++) {
		func(arr->data[i]);
	}
}

static int (*userCmp)(void *elem1, void *elem2);

static int qsortWrapper(const void *a, const void *b) {
	void *pa = *(void **)a;
	void *pb = *(void **)b;
	return userCmp(pa, pb);
}

void sortArray(Array *arr, int (*compareFunc)(void *, void *)) {
  userCmp = compareFunc;
	qsort(arr->data, arr->size, sizeof(void *), qsortWrapper);
}
