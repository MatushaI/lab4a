#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdio.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    unsigned int key;
    unsigned int *info;
} Node;

typedef struct Tree {
    Node *head;
} Tree;

// Создание/удаление дерева

Tree *treeBinaryCreate(void);
void deleteBinaryTree(Tree *tree);

// Основные и специальные функции

int addTree(Tree *tree, unsigned int key, unsigned int info);
int deleteKeyTree(Tree *tree, unsigned int key, int isDeleteTree);
Node *searchTree(Tree *tree, unsigned int key);
Node *specialSearchTree(Tree *tree, unsigned int key);
void printTree(Tree *tree);
void preorderTreeWalk(Tree *tree, unsigned int left, unsigned int right);

// Допы

int counter(void);
void paintBinaryTree(Tree *tree);

#endif 
