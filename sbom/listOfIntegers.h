// listOfIntegers.h

struct _listOfIntegers {
   int element;
   struct _listOfIntegers *next;
};

typedef struct _listOfIntegers *ListOfIntegers;

ListOfIntegers newListOfIntegers(int element);
void setListOfIntegersElement(ListOfIntegers list, int element);
int getListOfIntegersElement(ListOfIntegers list);
void setListOfIntegersNext(ListOfIntegers list, ListOfIntegers next);
ListOfIntegers getListOfIntegersNext(ListOfIntegers list);
void freeListOfIntegers(ListOfIntegers list);
