#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void *a, const void *b);

int main(int argc, char *argv[]){
    int i;

    qsort(argv+1, argc-1, sizeof(int), cmp);
    for(i=1;i<argc;i++){
        printf("%s\n",argv[i]);
    }

    return 0;
}

int cmp(const void *a, const void *b){
    const char *a1= *(const char **) a;
    const char *b1= *(const char **) b;

    if(a1[0] == '-' && !(b1[0] == '-')){
        return -1;
    }else if(!(a1[0] == '-') && b1[0] == '-'){
        return 1;
    }
    if(a1[0] > b1[0]){
        return 1;
    }else if(a1[0] < b1[0]){
        return -1;
    }
    return strcmp(a1, b1);
}
