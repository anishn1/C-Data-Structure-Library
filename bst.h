
#ifndef BST_H
#define BST_H
#include <stdbool.h>

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

BST *createBST(int (*compare)(void *, void *));
void destroyBST(BST *bst);
void addBST(BST *bst, void *data);
bool isEmptyBST(BST *bst);
int sizeBST(BST *bst);
void *minBST(BST *bst);
void *maxBST(BST *bst);
int heightBST(BST *bst);
BSTNode *searchBST(BST *bst, void *data);

#endif //BST_H
