#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {

    int repetition;
    int value;
    struct Node *right_child;
    struct Node *left_child;

};

typedef struct Node Node;

Node *createNode(int val){

    Node *node = NULL;

    if((node = (Node*)malloc(sizeof(Node) * 1)) == NULL){
        printf("Couldn't allocate new node!\n");
        return 0;
    }

    node->repetition = 0;
    node->value = val;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}
