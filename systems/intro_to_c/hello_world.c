#include <stdio.h>

/*
    argc - is a count of arguments from the command line
    char - an array of strings
*/
int main(int argc, char **argv) {
    printf("Hello \n");
    printf("world \n");   
    char* c;
    *c = "A";
    printf("char %s = %d\n", *c);
}