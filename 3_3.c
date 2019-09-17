#include<stdio.h>
#include<string.h>

int speicher(char *str);

int main(int argc, char *argv[]){
    int i, len=0;

    for(i=1; i<argc; i++){
        len += speicher(argv[i]);
    }
    char *a = calloc(len+1, sizeof(char));

    for(i=1; i<argc; i++){
        strcat(a, argv[i]);
    }
    puts(a);
    free(a);

    return 0;
}

int speicher(char *str){
    return strlen(str);
}
