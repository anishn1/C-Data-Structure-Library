
#include "bst.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

BST *createBST(int (*compare)(void *, void *)) {
  BST *bst = malloc(sizeof(BST));
  bst->root = NULL;
  bst->size = 0;
  return bst;
}

static void destroyBSTNode(BSTNode *node) {
  if (node != NULL) {
    destroyBSTNode(node->left);
    destroyBSTNode(node->right);
    free(node);
  }
}

void destroyBST(BST *bst) {
  destroyBSTNode(bst->root);
  free(bst);
}

static BSTNode *createBSTNode(void *data) {
  BSTNode *newNode = malloc(sizeof(BSTNode));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

static BSTNode *insertBST(BSTNode *root, void *data, int (*compare)(void *, void *)) {
  if (root == NULL) {
    return createBSTNode(data);
  }
  int cmp = compare(data, root->data);
  if (cmp < 0) {
    root->left = insertBST(root->left, data, compare);
  } else {
    root->right = insertBST(root->right, data, compare);
  }
  return root;
}

void addBST(BST *bst, void *data) {
  bst->root = insertBST(bst->root, data, bst->compare);
  bst->size++;
}

bool isEmptyBST(BST *bst) {
  return bst->size == 0;
}

int sizeBST(BST *bst) {
  return bst->size;
}

void *minBST(BST *bst) {
  assert(bst->size > 0);
  BSTNode *curr = bst->root;
  while (curr->left != NULL) {
    curr = curr->left;
  }
  return curr->data;
}

void *maxBST(BST *bst) {
  assert(bst->size > 0);
  BSTNode *curr = bst->root;
  while (curr->right != NULL) {
    curr = curr->right;
  }
  return curr->data;
}

static int heightBSTNode(BSTNode *root) {
  if (root == NULL) {
    return 0;
  }
  int leftHeight = heightBSTNode(root->left);
  int rightHeight = heightBSTNode(root->right);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int heightBST(BST *bst) {
  if (bst->size == 0) {
    return 0;
  }
  return heightBSTNode(bst->root);
}

static BSTNode *searchBSTNode(BSTNode *root, void *data, int (*compare)(void *, void *)) {
  if (root == NULL) {
    return NULL;
  }
  int cmp = compare(data, root->data);
  if (cmp < 0) {
    return searchBSTNode(root->left, data, compare);
  }
  if (cmp > 0) {
    return searchBSTNode(root->right, data, compare);
  }
  return root;

}

BSTNode *searchBST(BST *bst, void *data) {
  return searchBSTNode(bst->root, data, bst->compare);
}

static void forEachBSTNode(BSTNode *root, void (*func)(void *)) {
    if (root == NULL) {
		return;
	}
	func(root->data);
	forEachBSTNode(root->left, func);
	forEachBSTNode(root->right, func);
}

void forEachBST(BST *bst, void (*func)(void *data)) {
	forEachBSTNode(bst->root, func);
}

static void forEachBSTNode(BSTNode *root, void (*func)(void *)) {
    if (root == NULL) {
		return;
	}
	func(root->data);
	forEachBSTNode(root->left, func);
	forEachBSTNode(root->right, func);
}

void forEachBST(BST *bst, void (*func)(void *data)) {
	forEachBSTNode(bst->root, func);
}

static void forEachBSTNode(BSTNode *root, void (*func)(void *)) {
    if (root == NULL) {
		return;
	}
	func(root->data);
	forEachBSTNode(root->left, func);
	forEachBSTNode(root->right, func);
}

void forEachBST(BST *bst, void (*func)(void *data)) {
	forEachBSTNode(bst->root, func);
}


// Need to add forEach method for each traversal type