
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

Stack *createStack() {
  Stack *stack = malloc(sizeof(Stack));
  assert(stack != NULL);
  stack->head = NULL;
  stack->size = 0;
  return stack;
}

static void destroyNode(Node *node) {
  free(node);
}

void destroyStack(Stack *stack) {
  Node *curr = stack->head;
  while (curr != NULL) {
    Node *temp = curr->next;
    destroyNode(curr);
    curr = temp;
  }
  free(stack);
}

void *popStack(Stack *stack) {
  assert(stack->size > 0);
  void *data = stack->head->data;
  Node *next = stack->head->next;
  destroyNode(stack->head);
  stack->head = next;
  stack->size--;
  return data;
}

void pushStack(Stack *stack, void *data) {
  Node *node = malloc(sizeof(Node));
  assert(node != NULL);
  node->data = data;
  node->next = stack->head;
  stack->head = node;
  stack->size++;
}

void *peekStack(Stack *stack) {
  assert(stack->size > 0);
  return stack->head->data;
}

bool isEmptyStack(Stack *stack) {
  return stack->size == 0;
}

int sizeStack(Stack *stack) {return stack->size;}

void clearStack(Stack *stack) {
  while (stack->size > 0) {
    popStack(stack);
  }
}

void forEachStack(Stack *stack, void (*func)(void *)) {
  Node *curr = stack->head;
  while (curr != NULL) {
    func(curr->data);
    curr = curr->next;
  }
}