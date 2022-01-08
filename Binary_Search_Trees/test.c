#include <stdio.h>
#include <stdlib.h>

struct Node {

    int repetition;
    int value;
    struct Node *right_child;
    struct Node *left_child;

};

typedef struct Node Node;

int main(){

    Node *node = NULL;

    if((node = (Node*)malloc(sizeof(Node) * 1)) == NULL){
        printf("Couldn't allocate new node!\n");
        return 0;
    }

    node->repetition = 3;
    node->value = 6;
    node->left_child = NULL;
    node->right_child = NULL;

    printf("%d\n", node->value);
    printf("%d\n", node->repetition);
    printf("%d\n", node->left_child);
    printf("%d\n", node->right_child);
    
    printf("---------------");

    node = NULL;

    printf("%d\n", node->value);
    printf("%d\n", node->repetition);
    printf("%d\n", node->left_child);
    printf("%d\n", node->right_child);

   

    return 0;
}
