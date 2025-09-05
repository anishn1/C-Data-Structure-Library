
#ifndef SET_H
#define SET_H
#include <stdbool.h>

typedef struct HashNode {
  void *key;
  struct HashNode *next;
} HashNode;

typedef struct HashSet {
  int size;
  HashNode **buckets;
  int capacity;
  unsigned int (*hash)(void *);
  int (*compare)(void *, void *);
} HashSet;

HashSet *createHashSet(int capacity, unsigned int (*hash)(void *), int (*compare)(void *, void *));
void destroyHashSet(HashSet *hs);
void addHashSet(HashSet *hs, void *key);
int sizeHashSet(HashSet *hs);
bool containsHashSet(HashSet *hs, void *key);
void forEachHashSet(HashSet *hs, void (*func)(void *key));
HashSet *unionHashSet(HashSet *hs1, HashSet *hs2);
void removeHashSet(HashSet *hs, void *key);
HashSet *intersectHashSet(HashSet *hs1, HashSet *hs2);
HashSet *differenceHashSet(HashSet *hs1, HashSet *hs2);
void addAllHashSet(HashSet *hs1, HashSet *hs2);
HashSet *symmetricDifferenceHashSet(HashSet *hs1, HashSet *hs2);

#endif //SET_H
