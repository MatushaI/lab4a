#ifndef getFunctions_h
#define getFunctions_h

#include <stdio.h>
#include "BinaryTree.h"

FILE* getFile(const char* invite, char choose[4], int *check);
char *readString(FILE *file);
int getIntUnsignt(char *number);
char *myreadline(const char* invite);
int importFile(Tree *tree, Node **node);


#endif 
