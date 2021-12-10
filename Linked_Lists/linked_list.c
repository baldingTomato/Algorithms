/*
This program shows some of the simple functions you can use with linked lists. I put in it functions for ading and deleting nodes, merging lists,
copying lists without repeated strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {

    char *string;
    struct node *next;
    struct node *prev;

};

typedef struct node List;

List *createSentinel(){     //returns node that should be the beginning of a linked list

	List *sentinel = (List*)malloc(sizeof(List));
	
    sentinel->string = NULL;
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	
	return sentinel;
}

List *add_node(char *word, List *sentinel){

	List *item;
	
	item = (List*)malloc(sizeof(List));
	
	item->string = word;

    if(sentinel->next == sentinel){     //if linked list has no nodes besides sentinel
        item->next = sentinel;
	    item->prev = sentinel;

        sentinel->next = item;
        sentinel->prev = item;
    }else{                              //if there are other nodes
        item->next = sentinel->next;
        item->prev = sentinel;

        sentinel->next = item;
    }
	
	
	return item;
}

void *print_list(List *sentinel){

    List *head = sentinel->next;

    while(head->string != NULL){
        printf("%s\n", head->string);
        head = head->next;
    }

}

List *search(char *word, List *sentinel){

    List *head = sentinel->next;
    int index = 1;

    while(head->string != NULL){

        if(head->string == word){
            printf("Word \"%s\" is stored in %d node of your linked list.\n", head->string, index);
            return head;
        }

        head = head->next;
        index++;
    }

    printf("Word \"%s\" isn't stored in your linked list!\n", word);

    return NULL;
}

void *delete_node(char *word, List *sentinel){

    List *head = sentinel->next;
    List *tmp = sentinel;

    while(head->string != NULL){

        if(head->string == word){
            printf("Word \"%s\" has been deleted.\n", head->string);
            
            tmp->next = head->next;
            free(head);
            return NULL;
        }

        head = head->next;
        tmp = tmp->next;
    }

    printf("Word \"%s\" isn't stored in your linked list!\n", word);

}

void *delete_list(List *head){
	
    head = head->next;
    List *next;
	
	while(head->string != NULL){
		next = head->next;
		free(head);
		head = next;
	}
	
	free(head);
}

List *copyWithoutRepetition(List *list){

    List *copy = createSentinel();
    list = list->next;
    int checker = 0;

    add_node(list->string, copy);

    list = list->next;
    copy = copy->next;
    List *copy_head = copy;

    while(list->string != NULL){

        char *word;
        strcpy(word, list->string);
        
        while(copy->string != NULL){
            if(strcmp(word, copy->string) == 0){
                checker = 1;
            }
            copy = copy->next;
        }
        copy = copy_head;
        
        if(checker == 0){
            add_node(list->string, copy);
        }
        checker = 0;
        list = list->next;

    }

    return copy->prev;

}

List *merge_lists(List *list1, List *list2){

    List *sentinel1 = list1;
    while(list1->next->string != NULL){
        list1 = list1->next;
    }

    list1->next = list2->next;
    list2->next->prev = list1;

    while(list2->next->string != NULL){
        list2 = list2->next;
    }

    list2->next = sentinel1;
    sentinel1->prev = list2;


    return sentinel1;
}


int main(){

    List *sentinel_1 = createSentinel();
    List *sentinel_2 = createSentinel();

    add_node("tomek", sentinel_1);
    add_node("piotr", sentinel_1);
    add_node("filip", sentinel_1);
    add_node("filip", sentinel_1);
    add_node("radek", sentinel_1);

    add_node("alicja", sentinel_2);
    add_node("weronika", sentinel_2);
    add_node("alberta", sentinel_2);
    add_node("kasia", sentinel_2);
    add_node("wiktoria", sentinel_2);


    //print_list(sentinel_1);

    //search("radek", sentinel_1);

    //delete_node("filip", sentinel_1);

    //print_list(sentinel_1);

    //search("radek", sentinel_1);
    
    //delete_list(sentinel_1);

    //List *sentinel_2 = createSentinel();

    //add_node("rafal", sentinel_2);
    //add_node("wojtek", sentinel_2);

    //print_list(sentinel_2);

    //search("wojtek", sentinel_2);

    printf("\n\n");

    //List *sentinel_2 = copyWithoutRepetition(sentinel_1);

    print_list(sentinel_1);
    printf("\n\n\n");
    print_list(sentinel_2);

    List *sentinel_3 = merge_lists(sentinel_1, sentinel_2);
    printf("\n\n\n");
    print_list(sentinel_3);


    return 0;
}