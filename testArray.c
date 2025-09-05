
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
    printf("PASSED: testAddGet\n");
  } else {
    numFailed++;
    printf("FAILED: testAddGet\n");
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
    printf("PASSED: testAddSize\n");
  } else {
    numFailed++;
    printf("FAILED: testAddSize\n");
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

  int *element = removeGeneralArray(arr, 5);
  int checkVal = *element;
  if (!containsGeneralArray(arr, &checkVal, intCmp)) {
    numPassed++;
    printf("PASSED: testRemoveContains\n");
  } else {
    printf("FAILED: testRemoveContains\n");
    numFailed++;
  }
  free(element);
  forEachGeneralArray(arr, free);
  destroyGeneralArray(arr);
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
  testSummary();
}