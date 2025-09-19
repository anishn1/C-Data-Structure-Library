
#include "testArray.h"

#include <stdio.h>
#include <stdlib.h>

#include "array.h"

int numTests = 0;
int numPassed = 0;
int numFailed = 0;

static int intCmp(void *elem1, void *elem2) {
  int e1 = *(int *)elem1;
  int e2 = *(int *)elem2;
  return e1 - e2;
}

void testAddGet(int a, int b, int c, int d) {
  numTests++;
  Array *arr = createArray(5);
  addArray(arr, &a);
  addArray(arr, &b);
  addArray(arr, &c);
  addArray(arr, &d); // [5,1,2,9]
  int v1 = *(int *)getArray(arr, 0);
  int v2 = *(int *)getArray(arr, 1);
  int v3 = *(int *)getArray(arr, 2);
  int v4 = *(int *)getArray(arr, 3);
  if (v1 == a && v2 == b && v3 == c && v4 == d) {
    numPassed++;
    printf("PASSED: testAddGet\n");
  } else {
    numFailed++;
    printf("FAILED: testAddGet\n");
  }
  destroyArray(arr, free);
}

void testAddSize(int num) {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < num; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  if (sizeArray(arr) == num) {
    numPassed++;
    printf("PASSED: testAddSize\n");
  } else {
    numFailed++;
    printf("FAILED: testAddSize\n");
  }
  destroyArray(arr, free);
}

void testRemoveContains() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }

  int *element = removeArray(arr, 5);
  int checkVal = *element;
  if (!containsArray(arr, &checkVal, intCmp)) {
    numPassed++;
    printf("PASSED: testRemoveContains\n");
  } else {
    printf("FAILED: testRemoveContains\n");
    numFailed++;
  }
  free(element);
  destroyArray(arr, free);
}

void testRemoveEmpty() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  bool check = true;
  for (int i = 32; i > 0; i++) {
    int *element = removeArray(arr, i-1);
    if (*element != (i-1)) {
      check = false;
    }
    free(element);
  }
  if (isEmptyArray(arr) && check) {
    numPassed++;
    printf("PASSED: testRemoveEmpty\n");
  } else {
    numFailed++;
    printf("FAILED: testRemoveEmpty\n");
  }
  destroyArray(arr, free);
}

void testClearEmpty() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  clearArray(arr, free);
  if (arr->size == 0 && isEmptyArray(arr)) {
    numPassed++;
    printf("PASSED: testClearEmpty\n");
  } else {
    numFailed++;
    printf("FAILED: testClearEmpty\n");
  }
  destroyArray(arr, free);
}

void testPopSize() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  int size = 32;
  bool check = true;
  for (int i = 0; i < 32; i++) {
    int *element = popArray(arr);
    if (*element != i || size != 31 - i) {
      check = false;
    }
  }
  if (check) {
    numPassed++;
    printf("PASSED: testPopSize\n");
  } else {
    numFailed++;
    printf("FAILED: testPopSize\n");
  }
}

void testIndexGet() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  int *search = malloc(sizeof(int));
  *search = 8;
  int index = indexOfArray(arr, search, intCmp);
  free(search);
  if (*(int *)getArray(arr, index) == 8) {
    numPassed++;
    printf("PASSED: testIndexGet\n");
  } else {
    numFailed++;
    printf("FAILED: testIndexGet\n");
  }
  destroyArray(arr, free);
}

void testSetGet() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  int *new  = malloc(sizeof(int));
  *new = 121;
  void *old = setArray(arr, new, 4);
  free(old);
  if (*(int *)getArray(arr, 4) == 121) {
    numPassed++;
    printf("PASSED: testSetGet\n");
  } else {
    numFailed++;
    printf("FAILED: testSetGet\n");
  }
  destroyArray(arr, free);
}

static int sum = 0;

void sumFunc(void *elem) {
  sum += *(int *)elem;
}

void testForEach() {
  numTests++;
  Array *arr = createArray(16);
  int check = 0;
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    check += i;
    addArray(arr, val);
  }
  forEachArray(arr, sumFunc);
  if (sum == check) {
    numPassed++;
    printf("PASSED: testForEach\n");
  } else {
    numFailed++;
    printf("FAILED: testForEach\n");
  }
  destroyArray(arr, free);
}

void doubleFunc(void *elem) {
  *(int *)elem *= 2;
}

void testForEachModify() {
  numTests++;
  Array *arr = createArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addArray(arr, val);
  }
  forEachArray(arr, doubleFunc);
  bool check = true;
  for (int i = 0; i < 32; i++) {
    if (*(int *)getArray(arr, i) != 2*i) {
      check = false;
    }
  }
  if (check) {
    numPassed++;
    printf("PASSED: testForEachModify\n");
  } else {
    numFailed++;
    printf("FAILED: testForEachModify\n");
  }
  destroyArray(arr, free);
}

void testSummary() {
  printf("\n--------------------------------\n");
  printf("Number of tests: %d\n", numTests);
  printf("Passed: %d\n", numPassed);
  printf("Failed: %d\n", numFailed);
}

int main() {
  testAddGet(1, 2, 3, 4);
  testAddGet(300, 400, 500, 600);
  testAddSize(3);
  testAddSize(30);
  testRemoveContains();
  testRemoveEmpty();
  testClearEmpty();
  testPopSize();
  testIndexGet();
  testSetGet();
  testForEach();
  testForEachModify();
  testSummary();
}