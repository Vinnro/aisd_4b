#include "splay_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Node* createNode(unsigned int key, const char *value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = strdup(value);
    node->left = node->right = node->parent = NULL;
    return node;
}

Tree* createTree() {
    Tree *tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

void rotateRight(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->left = x;
    x->parent = y;
}

void splay(Node **root, Node *x) {
    while (x->parent != NULL) {
        if (x->parent->parent == NULL) {
            if (x->parent->left == x) rotateRight(root, x->parent);
            else rotateLeft(root, x->parent);
        } else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            rotateRight(root, x->parent->parent);
            rotateRight(root, x->parent);
        } else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            rotateLeft(root, x->parent->parent);
            rotateLeft(root, x->parent);
        } else if (x->parent->left == x && x->parent->parent->right == x->parent) {
            rotateRight(root, x->parent);
            rotateLeft(root, x->parent);
        } else {
            rotateLeft(root, x->parent);
            rotateRight(root, x->parent);
        }
    }
}

Node* addNode(Tree *tree, unsigned int key, const char *value) {
    Node *z = tree->root;
    Node *p = NULL;

    while (z != NULL) {
        p = z;
        if (key < z->key) z = z->left;
        else if (key > z->key) z = z->right;
        else {
            free(z->value);
            z->value = strdup(value);
            splay(&tree->root, z);
            return z;
        }
    }

    Node *newNode = createNode(key, value);
    newNode->parent = p;

    if (p == NULL) tree->root = newNode;
    else if (key < p->key) p->left = newNode;
    else p->right = newNode;

    splay(&tree->root, newNode);
    return newNode;
}

Node* findNode(Tree *tree, unsigned int key) {
    Node *z = tree->root;
    while (z != NULL) {
        if (key < z->key) z = z->left;
        else if (key > z->key) z = z->right;
        else {
            splay(&tree->root, z);
            return z;
        }
    }
    return NULL;
}

Node* subtreeMaximum(Node *u) {
    while (u->right != NULL) u = u->right;
    return u;
}

Node* deleteNode(Tree *tree, unsigned int key) {
    Node *z = findNode(tree, key);
    if (z == NULL) return NULL;

    splay(&tree->root, z);

    if (z->left == NULL) {
        tree->root = z->right;
        if (z->right != NULL) z->right->parent = NULL;
    } else if (z->right == NULL) {
        tree->root = z->left;
        if (z->left != NULL) z->left->parent = NULL;
    } else {
        Node *y = subtreeMaximum(z->left);
        if (y->parent != z) {
            if (y->left != NULL) y->left->parent = y->parent;
            y->parent->right = y->left;
            y->left = z->left;
            y->left->parent = y;
        }
        tree->root = y;
        y->right = z->right;
        y->right->parent = y;
        y->parent = NULL;
    }

    free(z->value);
    free(z);
    return tree->root;
}

void inOrderTraversal(Node *root, unsigned int key) {
    if (!root) return;
    inOrderTraversal(root->left, key);
    if (root->key <= key) printf("%u: %s\n", root->key, root->value);
    inOrderTraversal(root->right, key);
}

void freeNode(Node *node) {
    if (node) {
        free(node->value);
        free(node);
    }
}

void freeTree(Tree *tree) {
    while (tree->root != NULL) {
        deleteNode(tree, tree->root->key);
    }
    free(tree);
}

void spSearchNodeHelper(Node *root, unsigned int key, Node **result, int *maxDiff) {
    if (!root) return;
    spSearchNodeHelper(root->left, key, result, maxDiff);

    int currentDiff = abs((int)root->key - (int)key);
    if (currentDiff > *maxDiff) {
        *maxDiff = currentDiff;
        *result = root;
    }

    spSearchNodeHelper(root->right, key, result, maxDiff);
}

void spSearchNode(Tree *tree, unsigned int key) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Node *result = NULL;
    int maxDiff = -1;
    spSearchNodeHelper(tree->root, key, &result, &maxDiff);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result) {
        printf("Найдено: %u: %s\n", result->key, result->value);
    } else {
        printf("Не найдено\n");
    }
    printf("Время выполнения: %f секунд\n", cpu_time_used);
}
