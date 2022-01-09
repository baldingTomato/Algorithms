#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

Node *minValueNode(Node *parent){
  
    Node *current = parent;

    //find the leftmost leaf
    while (current && current->left_child != NULL){
        current = current->left_child;
    }
    
    return current;
}

Node *deleteNode(Node *root, int val){

    //if the tree is empty
    if (root == NULL) return root;

    // Find the node to be deleted
    if (val < root->value){

        root->left_child = deleteNode(root->left_child, val);

    }else if(val > root->value){

        root->right_child = deleteNode(root->right_child, val);

    }else{

        //only one child or no child
        if (root->left_child == NULL){
            Node *temp = root->right_child;
            free(root);
        return temp;

        }else if(root->right_child == NULL){

            Node *temp = root->left_child;
            free(root);
            return temp;

        }

        //if the node has two children
        Node *temp = minValueNode(root->right_child);

        //place the inorder successor in position of the node to be deleted
        root->value = temp->value;

        //delete the inorder successor
        root->right_child = deleteNode(root->right_child, temp->value);

  }

    return root;
}

void padding(char ch, int n){

    for (int i = 0; i < n; i++){
        putchar(ch);
    }

}

void printTree(Node *root, int level){
  
  if(root == NULL){

    padding('\t', level);
    puts ("~");

  }else{

    printTree(root->right_child, level + 1);
    padding('\t', level);
    printf("%d\n", root->value);
    printTree(root->left_child, level + 1);

  }

}

int main(){

    Node *root1 = createNode(7);

    addNode(root1, 3);
    addNode(root1, 5);
    addNode(root1, 10);
    addNode(root1, 1);
    addNode(root1, 9);
    addNode(root1, 8);
    addNode(root1, 12);
    addNode(root1, 22);
    addNode(root1, 20);
    addNode(root1, 4);

    searchNode(root1, 3);
    searchNode(root1, 10);
    searchNode(root1, 5);
    searchNode(root1, 9);
    searchNode(root1, 1);
    searchNode(root1, 7);
/*
    deleteNode(root1, 9);
    deleteNode(root1, 10);
    deleteNode(root1, 3);
    deleteNode(root1, 3);
    deleteNode(root1, 7);

    searchNode(root1, 3);
    searchNode(root1, 10);
    searchNode(root1, 5);
    searchNode(root1, 9);
    searchNode(root1, 1);
    searchNode(root1, 7);
*/

    printf("---------------------\n\n\n\n");

    printTree(root1, 1);

    root1 = deleteNode(root1, 9);
    root1 = deleteNode(root1, 1);
    root1 = deleteNode(root1, 10);
    root1 = deleteNode(root1, 9);
    root1 = deleteNode(root1, 4);
    //root1 = deleteNode(root1, 22);

    printf("---------------------\n\n\n\n");

    printTree(root1, 1);

    searchNode(root1, 3);
    searchNode(root1, 10);
    searchNode(root1, 5);
    searchNode(root1, 9);
    searchNode(root1, 1);
    searchNode(root1, 7);
    searchNode(root1, 12);

    return 0;
}
