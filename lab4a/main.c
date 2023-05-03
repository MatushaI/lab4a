#include <stdio.h>
#include "BinaryTree.h"
#include <stdlib.h>
#include "getFunctions.h"
#include "dialog.h"

int main(void) {
    
    Tree *tree = treeBinaryCreate();
    Node *search = calloc(1, sizeof(Node));
    
    const char *msgs[] = {"0. Выход", "1. Добавить элемент", "2. Поиск", "3. Удаление", "4. Печать дерева", "5. Обход дерева в прямом порядке", "6. Импорт из файла", "7. Подсчёт встречаемости чисел"};
    const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*func[])(Tree *, Node **) = {NULL, addInfo_In, search_In, delete_In, printTable_In, walkTree_In, importFile, counter_In};
    
    int rc;
    while((rc = dialog(msgs, Nmsgs, NULL))){
        if(!func[rc](tree, &search)){
            break;
        }
    }
    free(search);
    deleteBinaryTree(tree);
    return 0;
}



