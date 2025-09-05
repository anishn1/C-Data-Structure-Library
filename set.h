
#ifndef SET_H
#define SET_H

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

#endif //SET_H
