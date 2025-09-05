
#include "testArray.h"

#include <stdlib.h>

#include "array.h"

int numTests = 0;
int numPassed = 0;
int numFailed = 0;

void testAddGet(int a, int b, int c, int d) {
  numTests++;
  GeneralArray *arr = createGeneralArray(5);
  addGeneralArray(arr, &a);
  addGeneralArray(arr, &b);
  addGeneralArray(arr, &c);
  addGeneralArray(arr, &d); // [5,1,2,9]
  int v1 = *(int *)getGeneralArray(arr, 0);
  int v2 = *(int *)getGeneralArray(arr, 1);
  int v3 = *(int *)getGeneralArray(arr, 2);
  int v4 = *(int *)getGeneralArray(arr, 3);
  if (v1 == a && v2 == b && v3 == c && v4 == d) {
    numPassed++;
  } else {
    numFailed++;
  }
  destroyGeneralArray(arr);
}

void testAddSize(int num) {
  numTests++;
  GeneralArray *arr = createGeneralArray(16);
  for (int i = 0; i < num; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addGeneralArray(arr, val);
  }
  if (arr->size == num) {
    numPassed++;
  } else {
    numFailed++;
  }
  forEachGeneralArray(arr, free);
  destroyGeneralArray(arr);
}

void testRemoveContains() {
  numTests++;
  GeneralArray *arr = createGeneralArray(16);
  for (int i = 0; i < 32; i++) {
    int *val = malloc(sizeof(int));
    *val = i;
    addGeneralArray(arr, val);
  }

  removeGeneralArray(arr, 5);
  if (!containsGeneralArray(arr, 5)) {
    numPassed++;
  } else {
    numFailed++;
  }
  forEachGeneralArray(arr, free);
  destroyGeneralArray(arr);
}

void main() {
  testAddGet(1, 2, 3, 4);
  testAddGet(300, 400, 500, 600);
  testAddSize(3);
  testAddSize(30);
}