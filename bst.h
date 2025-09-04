
#ifndef BST_H
#define BST_H

typedef struct BSTNode {
  void *data;
  struct BSTNode *left;
  struct BSTNode *right;
} BSTNode;

typedef struct BST {
  BSTNode *root;
  int size;
  int (*compare)(void *, void *);
} BST;
#endif //BST_H
