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

void addNode(Node *parent, int val){

    bool inserted = false;

    while(inserted == false){

        if(val < parent->value){

            if(parent->left_child == NULL){
                parent->left_child = createNode(val);
                inserted = true;
            }
            parent = parent->left_child;

        }else if(val > parent->value){

            if(parent->right_child == NULL){
                parent->right_child = createNode(val);
                inserted = true;
            }
            parent = parent->right_child;

        }else if(val == parent->value){
            parent->repetition++;
            inserted = true;
        }

    }
    
}

void searchNode(Node *parent, int val){

    bool found = false;

    while(found == false){

        if(val < parent->value){

            if(parent->left_child != NULL){
                parent = parent->left_child;
            }else{
                printf("The tree has no such value like %d!\n", val);
                return;
            }


        }else if(val > parent->value){

            if(parent->right_child != NULL){
                parent = parent->right_child;
            }else{
                printf("The tree has no such value like %d!\n", val);
                return;
            }

        }else if(val == parent->value){
            found = true;
            printf("Found value %d!\n", parent->value);
        }

    }

}

Node *minValue(Node *parent){

    while(0 == 0){

        if(parent->left_child == NULL){
            return parent;
        }

        parent = parent->left_child;

    }

    return parent;
}

void deleteNode(Node *parent, int val){

    bool deleted = false;

    while(deleted == false){

        if(val < parent->value){

            if(parent->left_child == NULL){
                printf("The tree has no such value like %d!\n", val);
                return;
            }else{
                parent = parent->left_child;
            }


        }else if(val > parent->value){

            if(parent->right_child == NULL){
                printf("The tree has no such value like %d!\n", val);
                return;
            }else{
                parent = parent->right_child;
            }

        }else if(val == parent->value){
            
            if(parent->left_child == NULL && parent->right_child == NULL){
                parent = NULL;
                deleted = true;
            }else if(parent->left_child != NULL && parent->right_child == NULL){
                parent->value = parent->left_child->value;
                parent->left_child = NULL;
                deleted = true;
            }else if(parent->left_child == NULL && parent->right_child != NULL){
                parent->value = parent->right_child->value;
                parent->right_child = NULL;
                deleted = true;
            }else if(parent->left_child != NULL && parent->right_child != NULL){
                Node *successor = createNode(0);
                successor = minValue(parent->right_child);
                printf("%d", successor->value);
                parent->value = successor->value;
                deleteNode(parent->right_child, successor->value);
                successor = NULL;
                deleted = true;
            }

        }

    }

    printf("Value %d was successfully deleted!\n", val);

}

int main(){

    Node *root1 = createNode(7);
    
    addNode(root1, 3);
    addNode(root1, 5);
    addNode(root1, 10);
    addNode(root1, 1);
    addNode(root1, 9);
    addNode(root1, 8);
    
    searchNode(root1, 3);
    searchNode(root1, 10);
    searchNode(root1, 5);
    searchNode(root1, 9);
    searchNode(root1, 1);
    searchNode(root1, 7);
    
    return 0;
}
