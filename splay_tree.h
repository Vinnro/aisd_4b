#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdbool.h>

typedef struct Node {
    unsigned int key;
    char *value;
    struct Node *left, *right, *parent;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

Tree* createTree();
Node* addNode(Tree *tree, unsigned int key, const char *value);
Node* findNode(Tree *tree, unsigned int key);
Node* deleteNode(Tree *tree, unsigned int key);
void inOrderTraversal(Node *root, unsigned int key);
void freeTree(Tree *tree);

void spSearchNode(Tree *tree, unsigned int key);

#endif // SPLAY_TREE_H
