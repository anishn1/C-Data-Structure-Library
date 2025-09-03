
#ifndef DLLIST_H
#define DLLIST_H
#include <stdbool.h>

typedef struct DLLNode {
  struct DLLNode *prev;
  struct DLLNode *next;
  void *data;
} DLLNode;

typedef struct {
  struct DLLNode *head;
  struct DLLNode *tail;
  int size;
} DLL;

DLL *createDLL();
void destroyDLL(DLL *);
void addHeadDLL(DLL *dll, void *data);
void addTailDLL(DLL *dll, void *data);
void *removeHeadDLL(DLL *dll);
void *removeTailDLL(DLL *dll);
bool isEmptyDLL(DLL *dll);
int sizeDLL(DLL *dll);
void forEachDLL(DLL *dll, void (*func)(void *));
void *peekHeadDLL(DLL *dll);
void *peekTailDLL(DLL *dll);
void insertAtDLL(DLL *dll, void *data, int index);
void *deleteAtDLL(DLL *dll, int index);

#endif //DLLIST_H
