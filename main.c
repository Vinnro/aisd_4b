#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay_tree.h"

void printTree(Node *root, int space, int level, int *lastLevel);

void visualize_tree(Tree *tree) {
    if (tree->root == NULL) {
        printf("Дерево пустое.\n");
    } else {
        int lastLevel = -1;
        printTree(tree->root, 0, 0, &lastLevel);
    }
}

void printTree(Node *root, int space, int level, int *lastLevel) {
    if (root == NULL) return;

    space += 10;

    // Проходим по правому поддереву
    printTree(root->right, space, level + 1, lastLevel);

    // Печатаем текущий узел после пробела
    if (*lastLevel != level) {
        printf("\n");
        *lastLevel = level;
    }
    for (int i = 10; i < space; i++) printf(" ");
    printf("%u\n", root->key);

    // Проходим по левому поддереву
    printTree(root->left, space, level + 1, lastLevel);
}

void send_command_menu() {
    printf("\033[0;33m____________________________________\n");
    printf("__________Вот ваше меню_____________\n");
    printf("____Выберите один из вариантов ниже___\n");
    printf("[1] Добавить\n");
    printf("[2] Удалить\n");
    printf("[3] Обход\n");
    printf("[4] Поиск\n");
    printf("[5] Специальный поиск\n");
    printf("[6] Визуализация дерева\n");
    printf("[0] Выход\n");
    printf("____________________________________\033[0m\n");
}

void add_node_tree(Tree *tree) {
    unsigned int key;
    char value[256];
    printf("Введите ключ (число): ");
    scanf("%u", &key);
    printf("Введите значение (строка): ");
    scanf("%s", value);
    addNode(tree, key, value);
}

void remove_node_tree(Tree *tree) {
    unsigned int key;
    printf("Введите ключ для удаления (число): ");
    scanf("%u", &key);
    deleteNode(tree, key);
}

void traversal_limit_tree(Tree *tree) {
    unsigned int key;
    printf("Введите ключ для ограничения обхода (число, 0 для обхода всего дерева): ");
    scanf("%u", &key);
    inOrderTraversal(tree->root, key);
}

void search_node_tree(Tree *tree) {
    unsigned int key;
    printf("Введите ключ для поиска (число): ");
    scanf("%u", &key);
    Node *result = findNode(tree, key);
    if (result) {
        printf("Найдено: %u: %s\n", result->key, result->value);
    } else {
        printf("Не найдено\n");
    }
}

void special_search_node_tree(Tree *tree) {
    unsigned int key;
    printf("Введите ключ для специального поиска (число): ");
    scanf("%u", &key);
    spSearchNode(tree, key);
}

int main() {
    Tree *tree = createTree();
    int choice;
    do {
        send_command_menu();
        printf("Выберите опцию: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_node_tree(tree);
                break;
            case 2:
                remove_node_tree(tree);
                break;
            case 3:
                traversal_limit_tree(tree);
                break;
            case 4:
                search_node_tree(tree);
                break;
            case 5:
                special_search_node_tree(tree);
                break;
            case 6:
                visualize_tree(tree);
                break;
            case 0:
                printf("Выход\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);

    freeTree(tree);
    return 0;
}
