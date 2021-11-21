#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char *test = "tomek";

    printf("%s, %c, %d", test, *(test+2), *(test+2));

    return 0;
}