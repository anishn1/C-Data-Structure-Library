
#include "dllist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

DLL *createDLL() {
  DLL *dll = malloc(sizeof(DLL));
  dll->head = NULL;
  dll->tail = NULL;
  dll->size = 0;
  return dll;
}

void destroyDLL(DLL *dll) {
  DLLNode *curr = dll->head;
  while (curr != NULL) {
    DLLNode *temp = curr->next;
    free(curr);
    curr = temp;
  }
  free(dll);
}

void addHeadDLL(DLL *dll, void *data) {
  DLLNode *node = malloc(sizeof(DLLNode));
  node->data = data;
  if (dll->size == 0) {
    dll->tail = node;
  }
  node->next = dll->head;
  node->prev = NULL;
  dll->head = node;
  dll->size++;
}

static DLLNode *createDLLNode(DLL *dll, void *data) {
  DLLNode *node = malloc(sizeof(DLLNode));
  node->data = data;
  return node;
}

void addTailDLL(DLL *dll, void *data) {
  DLLNode *node = createDLLNode(dll, data);
  if (dll->size == 0) {
    dll->head = node;
  }
  node->prev = dll->tail;
  node->next = NULL;
  dll->tail = node;
  dll->size++;
}

void *removeHeadDLL(DLL *dll) {
  assert(dll->size > 0);
  void *data = dll->head->data;
  DLLNode *oldHead = dll->head;
  DLLNode *newHead = oldHead->next;
  free(dll->head);
  dll->head = newHead;
  if (newHead != NULL) {
    dll->head->prev = NULL;
  } else {
    dll->tail = NULL;
  }
  dll->size--;
  return data;
}

void *removeTailDLL(DLL *dll) {
  assert(dll->size > 0);
  void *data = dll->tail->data;
  DLLNode *oldTail = dll->tail;
  DLLNode *newTail = oldTail->prev;
  free(dll->tail);
  dll->tail = newTail;
  if (newTail != NULL) {
    dll->tail->next = NULL;
  } else {
    dll->head = NULL;
  }
  dll->size--;
  return data;
}

bool isEmptyDLL(DLL *dll) {return dll->size == 0;}
int sizeDLL(DLL *dll) {return dll->size;}
void forEachDLL(DLL *dll, void (*func)(void *)) {
  DLLNode *curr = dll->head;
  while (curr != NULL) {
    func(curr->data);
    curr = curr->next;
  }
}

void *peekHeadDLL(DLL *dll) {
  assert(dll->size > 0);
  return dll->head->data;
}

void *peekTailDLL(DLL *dll) {
  assert(dll->size > 0);
  return dll->tail->data;
}

void insertAtDLL(DLL *dll, void *data, int index) {
  assert(index >= 0 && index <= dll->size);
  if (index == 0) {addHeadDLL(dll, data);}
  else if (index == dll->size) {addTailDLL(dll, data);}
  else {
    DLLNode *node = createDLLNode(dll, data);
    DLLNode *curr = dll->head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }
    curr->prev->next = node;
    node->prev = curr->prev;
    node->next = curr;
    curr->prev = node;
    dll->size++;
  }
}

void *deleteAtDLL(DLL *dll, int index) {
  assert(index >= 0 && index < dll->size && dll->size > 0);
  DLLNode *curr = dll->head;
  if (index == 0) {return removeHeadDLL(dll);}
  if (index == dll->size - 1) {return removeTailDLL(dll);}
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }
  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  void *data = curr->data;
  free(curr);
  dll->size--;
  return data;
}