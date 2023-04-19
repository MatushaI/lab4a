#ifndef dialog_h
#define dialog_h

#include <stdio.h>
#include "BinaryTree.h"

int dialog(const char *msgs[], int N, int *ifPagePrev);

int addInfo_In(Tree *tree, Node **search);
int delete_In(Tree *tree, Node **search);
int search_In(Tree *tree, Node **search);
int printTable_In(Tree *tree, Node **search);
int counter_In(Tree *tree, Node **search);
int walkTree_In(Tree *tree, Node **search);

void printBirds(void);

#endif 
