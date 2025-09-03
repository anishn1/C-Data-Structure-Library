
#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct {
  int size;
  Node *head;
} Stack;

Stack *createStack();
static void destroyNode(Node *node);
void destroyStack(Stack *stack);
void *popStack(Stack *stack);
void pushStack(Stack *stack, void *data);
void *peekStack(Stack *stack);
bool isEmptyStack(Stack *stack);
int sizeStack(Stack *stack);
void clearStack(Stack *stack);
void forEachStack(Stack *stack, void (*func)(void *));


#endif //STACK_H
