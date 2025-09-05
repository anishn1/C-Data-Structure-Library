
#include "set.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#define LOAD 0.75

HashSet *createHashSet(int capacity, unsigned int (*hash)(void *), int (*compare)(void *, void *)) {
  HashSet *hs = malloc(sizeof(HashSet));
  assert(hs != NULL);
  if (capacity <= 0) {
    hs->capacity = 16;
  } else {
    hs->capacity = capacity;
  }
  hs->size = 0;
  hs->hash = hash;
  hs->compare = compare;
  hs->buckets = calloc(hs->capacity, sizeof(HashNode *));
  assert(hs->buckets != NULL);
  return hs;
}

void destroyHashSet(HashSet *hs) {
  for (int i = 0; i < hs->capacity; i++) {
    HashNode *curr = hs->buckets[i];
    while (curr != NULL) {
      HashNode *next = curr->next;
      free(curr);
      curr = next;
    }
  }
  free(hs->buckets);
  free(hs);
}

static int getBucketIndex(HashSet *hs, void *key) {
  return (int)hs->hash(key) % hs->capacity;
}

static void resizeHashSet(HashSet *hs) {
  int newCap = hs->capacity * 2;
  HashNode **newBuckets = calloc(newCap, sizeof(HashNode *));
  assert(newBuckets != NULL);
  for (int i = 0; i < hs->capacity; i++) {
    HashNode *curr = hs->buckets[i];
    while (curr != NULL) {
      int newIndex = (int)hs->hash(curr->key) % newCap;
      HashNode *nextNode = curr->next;
      curr->next = newBuckets[newIndex];
      newBuckets[newIndex] = curr;
      curr = nextNode;
    }
  }
  free(hs->buckets);
  hs->buckets = newBuckets;
  hs->capacity = newCap;
}

void addHashSet(HashSet *hs, void *key) {
  assert(hs != NULL);
  int index = getBucketIndex(hs, key);
  HashNode *curr = hs->buckets[index];
  while (curr != NULL) {
    if (hs->compare(curr->key, key) == 0) {
      return;
    }
    curr = curr->next;
  }
  HashNode *newNode = malloc(sizeof(HashNode));
  assert(newNode != NULL);
  newNode->key = key;
  newNode->next = hs->buckets[index];
  hs->buckets[index] = newNode;
  hs->size++;
  if ((double)hs->size > LOAD * hs->capacity) {
    resizeHashSet(hs);
  }
}

int sizeHashSet(HashSet *hs) {
  return hs->size;
}

bool containsHashSet(HashSet *hs, void *key) {
  assert(hs != NULL);
  int index = getBucketIndex(hs, key);
  HashNode *curr = hs->buckets[index];
  while (curr != NULL) {
    if (hs->compare(curr->key, key) == 0) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

void forEachHashSet(HashSet *hs, void (*func)(void *key)) {
  for (int i = 0; i < hs->capacity; i++) {
    HashNode *curr = hs->buckets[i];
    while (curr != NULL) {
      func(curr->key);
      curr = curr->next;
    }
  }
}

HashSet *unionHashSet(HashSet *hs1, HashSet *hs2) {
  assert(hs1 != NULL && hs2 != NULL);
  assert(hs1->hash == hs2->hash && hs1->compare == hs2->compare);
  HashSet *hs = createHashSet(hs1->capacity, hs1->hash, hs1->compare);
  for (int i = 0; i < hs1->capacity; i++) {
    HashNode *curr = hs1->buckets[i];
    while (curr != NULL) {
      addHashSet(hs, curr->key);
    }
  }
  for (int i = 0; i < hs2->capacity; i++) {
    HashNode *curr = hs2->buckets[i];
    while (curr != NULL) {
      addHashSet(hs, curr->key);
    }
  }
  return hs;
}

void removeHashSet(HashSet *hs, void *key) {
  assert(hs != NULL);
  assert(hs->size > 0);
  int index = getBucketIndex(hs, key);
  HashNode *curr = hs->buckets[index];
  HashNode *next = curr->next;
  if (hs->compare(curr->key, key) == 0) {
    hs->buckets[index] = curr->next;
    free(curr);
    hs->size--;
    return;
  }
  while (next != NULL) {
    if (hs->compare(next->key,key) == 0) {
      curr->next = next->next;
      free(next);
      hs->size--;
      return;
    }
    curr = next;
    next = curr->next;
  }
}

HashSet *intersectHashSet(HashSet *hs1, HashSet *hs2) {
  assert(hs1 != NULL && hs2 != NULL);
  assert(hs1->hash == hs2->hash && hs1->compare == hs2->compare);
  HashSet *hs = createHashSet(hs1->capacity, hs1->hash, hs1->compare);
  for (int i = 0; i < hs1->capacity; i++) {
    HashNode *curr = hs1->buckets[i];
    while (curr != NULL) {
      if (containsHashSet(hs2, curr->key)) {
        addHashSet(hs, curr->key);
      }
      curr = curr->next;
    }
  }
  return hs;
}

HashSet *differenceHashSet(HashSet *hs1, HashSet *hs2) {
  assert(hs1 != NULL && hs2 != NULL);
  assert(hs1->hash == hs2->hash && hs1->compare == hs2->compare);
  HashSet *hs = createHashSet(hs1->capacity, hs1->hash, hs1->compare);
  for (int i = 0; i < hs1->capacity; i++) {
    HashNode *curr = hs1->buckets[i];
    while (curr != NULL) {
      if (!containsHashSet(hs2, curr->key)) {
        addHashSet(hs, curr->key);
      }
      curr = curr->next;
    }
  }
  return hs;
}

void addAllHashSet(HashSet *hs1, HashSet *hs2) {
  for (int i = 0; i < hs2->capacity; i++) {
    HashNode *curr = hs2->buckets[i];
    while (curr != NULL) {
      addHashSet(hs1, curr->key);
    }
  }
}

HashSet *symmetricDifferenceHashSet(HashSet *hs1, HashSet *hs2) {
  HashSet *unionHS = unionHashSet(hs1, hs2);
  HashSet *interHS = intersectHashSet(hs1, hs2);
  HashSet *diffHS = differenceHashSet(unionHS, interHS);
  destroyHashSet(unionHS);
  destroyHashSet(interHS);
  return diffHS;
}