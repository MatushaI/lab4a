#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "getFunctions.h"

Tree *treeBinaryCreate(void) {
    Tree *tree = calloc(1, sizeof(Tree));
    tree->head = NULL;
    paintBinaryTree(tree);
    return tree;
}

// Поиск

Node *searchTree(Tree *tree, unsigned int key) {
    if(!tree) {
        return NULL;
    }
    Node *node = tree->head;
    while (node && key != node->key) {
        if(key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

// Добавление

int addTree(Tree *tree, unsigned int key, unsigned int info) {
    if(key < 0 || info < 0) {
        return 1;
    }
    Node *newnode = calloc(1, sizeof(Node));
    unsigned int *infoadd = calloc(1, sizeof(unsigned int));
    infoadd[0] = info;
    Node *node = tree->head;
    Node *place = NULL;
    
    if(searchTree(tree, key) == NULL) {
        
        while (node) {
            place = node;
            if(key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->key = key;
        newnode->info = infoadd;
        
        if(tree->head == NULL) {
            tree->head = newnode;
        } else {
            if(key < place->key) {
                place->left = newnode;
            } else {
                place->right = newnode;
            }
        }
    } else {
        free(infoadd);
        free(newnode);
        return 1;
    }
    
    paintBinaryTree(tree);
    
    return 0;
}

// Печать дерева

int depthN(Tree *tree, Node *node) {
    int depth = 0;
    Node *start = tree->head;
    if(start == node) {
        return 0;
    }
    while (start != node) {
        
        if(node->key < start->key) {
            start = start->left;
            depth++;
        } else {
            start = start->right;
            depth++;
        }
        
    }
    return depth;
}

void printElement(Node *node, int *i, int *lr, Tree *tree) {
    if(node){
        *i = *i + 4;
        printElement(node->right, i, lr, tree);
        
        for (int b = 0; b < depthN(tree, node)*4; b++) {
            printf(" ");
        }
        
        printf("|- %d\n", node->key);
        printElement(node->left, i, lr, tree);
        
        *i = *i - 4;
    }
}

void printTree(Tree *tree) {
    if(tree) {
        int i = -4;
        int lr = 0;
        if(tree->head != NULL) {
            printElement(tree->head, &i, &lr, tree);
        }
    }
}

// Удаление

Node *findNext(Node *node) {
    if(node->right) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    return node;
}

int deleteKeyTree(Tree *tree, unsigned int key, int isDeleteTree) {
    if(!tree) {
        return 1;
    }
    Node *node = tree->head;
    Node *prev = NULL;
    Node *delNode = NULL;
    unsigned int keySwap;
    unsigned int infoSwap;
    
    while (node) {
        if(key == node->key) {
            break;
        }
        prev = node;
        if(key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    
    if(!node) {
        return 1;
    }
    
    if(node->left != NULL && node->right != NULL) {
        
        delNode = findNext(node);
        keySwap = delNode->key;
        node->info[0] = delNode->info[0];
        deleteKeyTree(tree, delNode->key, isDeleteTree);
        node->key = keySwap;
        
        if(isDeleteTree == 0) {
            paintBinaryTree(tree);
        }
        
        return 0;
    }
    
    if(node->left == NULL || node->right == NULL) {
        if(tree->head == node) {
            if(node->left) {
                tree->head = node->left;
            } else if(node->right) {
                tree->head = node->right;
            } else {
                tree->head = NULL;
            }
            
        } else if(prev->left == node) {
            if(node->left) {
                prev->left = node->left;
            } else {
                prev->left = node->right;
            }
        } else {
            if(node->left) {
                prev->right = node->left;
            } else {
                prev->right = node->right;
            }
        }
        
        free(node->info);
        free(node);
        
        if(isDeleteTree == 0) {
            paintBinaryTree(tree);
        }
        
        return 0;
    }
    
    return 1;
}

// Graphviz

void preorderPaintPrint(Node *node, FILE *file) {
    if(node) {
        
        fprintf(file, "%d [shape=record,label = \"%d |{%d}\"]\n", node->key, node->key, *node->info);
        
        preorderPaintPrint(node->left, file);
        preorderPaintPrint(node->right, file);
    }
}

void paintPrint(Node *node, FILE *file) {
    if(node) {
        if(node->left) {
            fprintf(file, "%d", node->key);
            fprintf(file, ":sw->%d;\n", node->left->key);
        }
        if(node->right){
            fprintf(file, "%d", node->key);
            fprintf(file, ":se->%d;\n", node->right->key);
        }
        paintPrint(node->left, file);
        paintPrint(node->right, file);
    }
}

void paintBinaryTree(Tree *tree) {
    FILE *file = fopen("test.dot", "w");
    fprintf(file, "digraph G {\n");
    if(tree) {
        preorderPaintPrint(tree->head, file);
        paintPrint(tree->head, file);
    }
    fprintf(file, "}");
    fclose(file);
}

// Обход

void preorderPrint(Node *node, unsigned int left, unsigned int right) {
    if(node) {
        if(node->key < left || node->key > right) {
            printf("%d - %d | ", node->key, *node->info);
        }
        preorderPrint(node->left, left, right);
        preorderPrint(node->right, left, right);
    }
}

void preorderTreeWalk(Tree *tree, unsigned int left, unsigned int right) {
    if(tree->head) {
        preorderPrint(tree->head, left, right);
    }
}

// Специальный поиск

Node *findMax(Node *node) {
    while (node->right) {
        node = node->right;
    }
    return node;
}

Node *findMin(Node *node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

Node *specialSearchTree(Tree *tree, unsigned int key) {
    if(tree->head){
        Node *min = findMin(tree->head);
        Node *max = findMax(tree->head);
        if(labs(key - (long) min->key) >= labs(key - (long) max->key)) {
            return min;
        } else {
            return max;
        }
    }
    return NULL;
}

// Удаление дерева

void deleteBinaryTree(Tree *tree) {
    while (tree->head) {
        deleteKeyTree(tree, tree->head->key, 1);
    }
    free(tree);
}

// Доп. задание

void writeFileDop(Node *node, FILE *file) {
    if(node) {
        fprintf(file, "%d - %d\n", node->key, *node->info);
        writeFileDop(node->left, file);
        writeFileDop(node->right, file);
    }
}

int counter(void) {
    Tree *tree = treeBinaryCreate();
    Node *node = NULL;
    unsigned int read = 0;
    int flag = 1;
    int i = 0;
    FILE *binaryFile = getFile("Введите название бинарного файла\n> ", "r+", NULL); // заглушка
    FILE *resultFile = NULL;
    if(binaryFile) {
        resultFile = getFile("Введите название итогового файла\n> ", "w", NULL);
        if(resultFile) {
            fseek(binaryFile, 0, SEEK_SET);
            while (flag) {
                flag = (int) fread(&read, sizeof(unsigned int), 1, binaryFile);
                if(flag) {
                    node = searchTree(tree, read);
                    if(node) {
                        node->info[0] = node->info[0] + 1;
                    } else {
                        addTree(tree, read, 1);
                    }
                }
                i++;
            }
        } else {
            deleteBinaryTree(tree);
            fclose(binaryFile);
            return 1;
        }
    } else {
        deleteBinaryTree(tree);
        return 1;
    }
    
    if(tree->head){
        writeFileDop(tree->head, resultFile);
    }
    deleteBinaryTree(tree);
    fclose(resultFile);
    fclose(binaryFile);
    return 0;
}

// Личное -_-

void recurseCount(Node *node, FILE *file, Tree *newTree) {
    if(node) {
        Node *newnode = NULL;
        unsigned int read = node->key;
        newnode = searchTree(newTree, read);
        if(newnode) {
            newnode->info[0] = newnode->info[0] + 1;
            
        } else {
            addTree(newTree, read, 1);
        }
        recurseCount(node->left, file, newTree);
        recurseCount(node->right, file, newTree);
    }
}

int counterTest(Tree *tree) {
    Tree *newTree = treeBinaryCreate();
    
    FILE *resultFile = fopen("testFunc.txt", "w");
    
    recurseCount(tree->head, resultFile, newTree);
    
    if(tree->head){
        writeFileDop(newTree->head, resultFile);
    }
    deleteBinaryTree(newTree);
    
    return 0;
}
