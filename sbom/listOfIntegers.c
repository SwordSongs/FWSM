// listOfIntegers.c

#include "listOfIntegers.h"
#include <stdio.h>
#include <stdlib.h>

ListOfIntegers newListOfIntegers(int element) {
   ListOfIntegers newL;

   newL = (ListOfIntegers)malloc(sizeof(struct _listOfIntegers));
   setListOfIntegersElement(newL, element);
   setListOfIntegersNext(newL, NULL);
   return newL;
}

void setListOfIntegersElement(ListOfIntegers list, int element) {
   list->element = element;
}


int getListOfIntegersElement(ListOfIntegers list) {
   return list->element;
}


void setListOfIntegersNext(ListOfIntegers list, ListOfIntegers next) {
   list->next = next;
}


ListOfIntegers getListOfIntegersNext(ListOfIntegers list) {
   return list->next;
}

void freeListOfIntegers(ListOfIntegers list) {
   ListOfIntegers old;
   old = list;
   while (list != NULL) {
      list = list->next;
      free(old);
      old = list;
   }
}
