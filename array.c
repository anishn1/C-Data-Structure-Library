
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "array.h"

GeneralArray *createGeneralArray(int capacity) {
	GeneralArray *arr = malloc(sizeof(GeneralArray));
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

void destroyGeneralArray(GeneralArray *arr) {
	free(arr->data);
	free(arr);
}

void addGeneralArray(GeneralArray *arr, void *element) {
	if (arr->size == arr->capacity) {
		arr->capacity *= 2;
		arr->data = realloc(arr->data, sizeof(void *) * arr->capacity);
		assert(arr->data != NULL);
	}
	arr->data[arr->size] = element;
	arr->size++;
}

void *getGeneralArray(GeneralArray *arr, int index) {
	assert(index >= 0 && index < arr->size);
	return arr->data[index];
}

bool isEmptyGeneralArray(GeneralArray *arr) {
	return arr->size == 0;
}

int sizeGeneralArray(GeneralArray *arr) {
	return arr->size;
}

void *removeGeneralArray(GeneralArray *arr, int index) {
	assert(index >= 0 && index < arr->size);
	void *element = arr->data[index];
	for (int i = index; i < arr->size - 1; i++) {
		arr->data[i] = arr->data[i + 1];
	}
	arr->size--;
	return element;
}

void *popGeneralArray(GeneralArray *arr) {
	void *element = getGeneralArray(arr, arr->size - 1);
	removeGeneralArray(arr, arr->size - 1);
	return element;
}

void setGeneralArray(GeneralArray *arr, void *element, int index) {
	assert(index >= 0 && index < arr->size);
	arr->data[index] = element;
}

void insertGeneralArray(GeneralArray *arr, void *element, int index) {
	for (int i = arr->size - 1; i >= index; i--) {
		arr->data[i+1] = arr->data[i];
	}
	arr->data[index] = element;
	arr->size++;
}

void clearGeneralArray(GeneralArray *arr) {
	arr->size = 0;
}

void resizeGeneralArray(GeneralArray *arr, int newCapacity) {
	assert(newCapacity >= arr->size);
	arr->capacity = newCapacity;
	arr->data = realloc(arr->data, sizeof(void *) * newCapacity);
	assert(arr->data != NULL);
}

bool containsGeneralArray(GeneralArray *arr, void *element, int (*compareFunc)(void *, void *)) {
	for (int i = 0; i < arr->size; i++) {
		if (compareFunc(arr->data[i], element) == 0) {
			return true;
		}
	}
	return false;
}

int indexOfGeneralArray(GeneralArray *arr, void *element, int (*compareFunc)(void *, void*)) {
	for (int i = 0; i < arr->size; i++) {
		if (compareFunc(arr->data[i], element) == 0) {
			return i;
		}
	}
  return -1;
}

void forEachGeneralArray(GeneralArray *arr, void (*func)(void *)) {
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

void sortGeneralArray(GeneralArray *arr, int (*compareFunc)(void *, void *)) {
  userCmp = compareFunc;
	qsort(arr->data, arr->size, sizeof(void *), qsortWrapper);
}
