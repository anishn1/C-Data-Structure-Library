
#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  void **data;
  int size;
  int capacity;
} GeneralArray;

GeneralArray *createGeneralArray(int capacity);
void destroyGeneralArray(GeneralArray *arr);
void addGeneralArray(GeneralArray *arr, void *element);
void removeGeneralArray(GeneralArray *arr, int index);
void *getGeneralArray(GeneralArray *arr, int index);
void setGeneralArray(GeneralArray *arr, void *element, int index);
bool isEmptyGeneralArray(GeneralArray *arr);
int sizeGeneralArray(GeneralArray *arr);
void *popGeneralArray(GeneralArray *arr);
void insertGeneralArray(GeneralArray *arr, void *element, int index);
void clearGeneralArray(GeneralArray *arr);
void resizeGeneralArray(GeneralArray *arr, int newCapacity);
void printGeneralArray(GeneralArray *arr, void (*printFunc)(void *));
bool containsGeneralArray(GeneralArray *arr, void *element, int (*compareFunc)(void *, void *));
int indexOfGeneralArray(GeneralArray *arr, void *element, int (*compareFunc)(void *, void*));
void forEachGeneralArray(GeneralArray *arr, void (*func)(void *));
void sortGeneralArray(GeneralArray *arr, int (*compareFunc)(void *, void *));

#endif //ARRAY_H
