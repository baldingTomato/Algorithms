#include <stdio.h>
#include <stdlib.h>

struct node {

    char *string;
    struct node *next;
    struct node *prev;

};

typedef struct node List;

List *createSentinel(){

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

    if(sentinel->next == sentinel){
        item->next = sentinel;
	    item->prev = sentinel;

        sentinel->next = item;
        sentinel->prev = item;
    }else{
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

void *delete_list(List *head) {
	
    head = head->next;
    List *next;
	
	while(head->string != NULL) {
		next = head->next;
		free(head);
		head = next;
	}
	
	free(head);
}


List *copyWithoutRepetition(List *list){

    List *copy = createSentinel();
    list = list->next;

    while(list->string != NULL){

        add_node(list->string, copy);

    }

    for(copy->next; copy->next != NULL; copy = copy->next){

        while(copy->string != NULL){

            //probably wrong approach

        }

    }

}


int main(){

    List *sentinel_1 = createSentinel();

    add_node("tomek", sentinel_1);
    add_node("piotr", sentinel_1);
    add_node("filip", sentinel_1);
    add_node("radek", sentinel_1);

    print_list(sentinel_1);

    search("radek", sentinel_1);

    delete_node("filip", sentinel_1);

    print_list(sentinel_1);

    search("radek", sentinel_1);
    
    delete_list(sentinel_1);

    List *sentinel_2 = createSentinel();

    add_node("rafal", sentinel_2);
    add_node("wojtek", sentinel_2);

    print_list(sentinel_2);

    search("wojtek", sentinel_2);




    return 0;
}