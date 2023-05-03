#include "dialog.h"
#include "getFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include "BinaryTree.h"
#include <time.h>
#include <unistd.h>
#include <string.h>

int dialog(const char *msgs[], int N, int *ifPagePrev) {
    
    char *errorMessage = "";
    int n = 0;
    char *string = NULL;
    
    do {
        printf("%s\n", errorMessage);
        
        for (int i = 0; i < N; i++) {
            printf("%s\n", msgs[i]);
        }
        
        string = myreadline("> ");
        
        if(string == NULL) {
            if(ifPagePrev != NULL) {
                *ifPagePrev = -1;
            }
            return 0;
        }
        
        n = getIntUnsignt(string);
        errorMessage = "\n(!) Пункт меню не найден. Попробуйте ещё раз\n";
        free(string);
        
    } while (n < 0 || n >= N);
    
    return n;
}

int addInfo_In(Tree *tree, Node **search) {
    char *errorMessage = "";
    char *string = NULL;
    unsigned int key = 0;
    unsigned int info = 0;
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите ключ добавляемого элемента\n> ");
        key = getIntUnsignt(string);
        if(string == NULL) {
            return 0;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(key == -1);
    
    errorMessage = "";
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите информацию\n> ");
        info = getIntUnsignt(string);
        if(string == NULL) {
            return 0;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(info == -1);
    
    if(!addTree(tree, key, info)) {
        printf("\n(OK) Успешно\n");
    } else {
        printf("\n(X) Ошибка добавления элемента\n");
    }
    
    return 1;
}

int delete_In(Tree *tree, Node **search) {
    unsigned int key = 0;
    char *string = NULL;
    char *errorMessage = "";
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите ключ удаляемого элемента\n> ");
        key = getIntUnsignt(string);
        if(string == NULL) {
            break;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(key == -1);
    
    if(!deleteKeyTree(tree, key, 0)) {
        printf("\n(OK) Успешно\n");
    } else {
        printf("\n(X) Ключ не найден\n");
    }
    
    return 1;
}

int printTable_In(Tree *tree, Node **search) {
    printTree(tree);
    return 1;
}

void printTreeSearch_In(Tree *tree, Node **search) {
    if(*search) {
        printf("Ключ: %d, информация: %d", (*search)->key, *(*search)->info);
    } else {
        printf("\n(X) Результат поиска пуст\n");
    }
}

void searchKey_In(Tree *tree, Node **search) {
    Node *searchN = NULL;
    unsigned int key = 0;
    char *string = NULL;
    char *errorMessage = "";
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите искомый ключ\n> ");
        key = getIntUnsignt(string);
        if(string == NULL) {
            break;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(key == -1);
        
    if(!(searchN = searchTree(tree, key))){
        printf("\n(X) Элемент не найден или дерево пустое\n");
    } else {
        printf("Результат поиска:\n");
        printf("Ключ: %d, информация: %d\n", searchN->key, *searchN->info);
    }
}

void searchSpecial_In(Tree *tree, Node **search) {
    Node *searchN = NULL;
    char *errorMessage = "";
    char *string = NULL;
    unsigned int key = 0;
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите версию искомого элемента\n> ");
        key = getIntUnsignt(string);
        if(string == NULL) {
            break;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(key == -1);
    
    if(!(searchN = specialSearchTree(tree, key))){
        printf("\n(X) Дерево пустое\n");
    } else {
        printf("Результат поиска:\n");
        printf("Ключ: %d, информация: %d\n", searchN->key, *searchN->info);
    }
}

int search_In(Tree *tree, Node **search) {
    void (*func[])(Tree *, Node **) = {NULL, searchKey_In, searchSpecial_In, printTreeSearch_In};
    const char *msgs[] = {"0. В основное меню", "1. Поиск по значению ключа", "2. Поиск максимально дальнего элемента"};
    int checkZero = 0;
    int n = dialog(msgs, sizeof(msgs) / sizeof(msgs[0]), &checkZero);
    
    if(checkZero == -1) {
        return 0;
    }
    
    if(n == 0 || n == 3) {
        return 1;
    }
    
    func[n](tree, search);
    
    return 1;
}

int counter_In(Tree *tree, Node **search) {
    if(counter()) {
        return 0;
    } else {
        return 1;
    }
}

int walkTree_In(Tree *tree, Node **search) {
    printf("\nЗадание: вывод всего содержимого дерева в прямом порядке следования ключей, не входящих в заданный диапазон. \n");
    
    char *errorMessage = "";
    char *string = NULL;
    unsigned int left = 0;
    unsigned int right = 0;
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите левую границу обхода\n> ");
        left = getIntUnsignt(string);
        if(string == NULL) {
            return 0;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(left == -1);
    
    errorMessage = "";
    
    do {
        printf("%s\n", errorMessage);
        string = myreadline("Введите правую границу обхода\n> ");
        right = getIntUnsignt(string);
        if(string == NULL) {
            return 0;
        }
        errorMessage = "\n(!) Неверный ввод. Попробуйте ещё раз\n";
        free(string);
    } while(right == -1);
    printf("\n");
    preorderTreeWalk(tree, left, right);
    printf("\n");
    
    return 1;
}

void printCat(void) {
    
    const char *cat[] = {"  ╭━━━╮  ╱╲   ╱╲", "  ┃╭━━╯  ▏▔▔▔▔▔▕ ", "  ┃╰━━━━━▏╭▆┊╭▆▕ ", "  ╰┫╯╯╯╯╯▏╰╯▼╰╯▕ ", "   ┃╯╯╯╯╯▏╰━┻━╯▕", "   ╰┓┏┳━┓┏┳┳━━━╯","    ┃┃┃ ┃┃┃┃","    ┗┻┛ ┗┛┗┛\n\n"};
    
    for (int i = 0; i < 45; i++) {
        system("clear");
        for (int b = 0; b < 8; b++) {
            for (int c = 0; c < i; c++) {
                printf(" ");
            }
            printf("%s\n", cat[b]);
            
        }
        printf("  Бегу сдавать лабу после ночи с valgrind\n");
        usleep(50000);
    }
    system("clear");
}

void print_reverse(const char *string) {
    int otstup = 150;
    for (int i = 0; i < otstup - strlen(string); i++) {
        printf(" ");
    }
    printf("%s <\n", string);
}

void printBirds(void) {
    
    const char *text[] = {"Папа! Папа! А прочитай мне сказку перед сном", "Хорошо, сынок", "Как-то раз...", "Снова делал лабу всю ночь???", "Нет, слушай до конца: Сделал он как-то раз лабу заранее...", "Не верю"};
    const char *birds[] = {
"                       .-\"\"\"-.          ",
"              ____   /   __   `\\     __   ",
"           .'`  __'. | o/__\\o   |   / /|",
"          /  o /__\\o;\\  \\\\//   /_  // /",
" ._      _|    \\\\// |`-.__.-'|\\  `;  /",
"/  \\   .'  \\-.____.'|   ||   |/    \\/",
"`._ '-/             |   ||   '.___./",
".  '-.\\_.-'      __.'-._||_.-' _ /",
".`\"\"===(||).___.(||)(||)----'(||)===...__",
"`\"   \"`\"\"=====\"\"\"\"========\"\"\"====...__  `\"\"==._",
"                                  `\"=.     `\"=.",
"                  `\"=."};
    int tale = sizeof(text)/sizeof(text[0]);
    int lenght = sizeof(birds) / sizeof(birds[0]);
    
    for (int i = 0; i < tale; i++) {
        
        system("clear");
        
        for (int i = 0; i < lenght; i++) {
            printf("%s", birds[i]);
            printf("\n");
        }
        
        if(i%2 == 1) {
            printf("> %s", text[i]);
        } else {
            print_reverse(text[i]);
        }
        
        usleep(1500000);
    }
    printf("И птенчик, так сильно обманутый, с грустью пошёл спать.\n *** КОНЕЦ ***\n");
}
