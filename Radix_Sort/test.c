#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char **test;
    *test = malloc(4 * sizeof(char*));

    for(int i = 0; i < 3; i++){
        test[i] = malloc(4 * sizeof(char));
        strcpy(test[i], "uno");
    }

    char **test2;
    *test2 = malloc(4 * sizeof(char*));

    for(int i = 0; i < 3; i++){
        test2[i] = malloc(4 * sizeof(char));
        strcpy(test2[i], "dos");
    }

    printf("%s", test2[0]);

    return 0;
}