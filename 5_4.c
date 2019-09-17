#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int cmp(const void *a, const void *b);

int main(void){
    char str[] = "a7B(5A)b";

    puts(str);
    qsort(str, strlen(str), sizeof(char), cmp);
    puts(str);

    return 0;
}

int cmp(const void *a, const void *b){
    const char a1= *(const char*) a;
    const char b1= *(const char*) b;

    if(isdigit(a1) && !isdigit(b1)){
        return -1;
    }else if(!isdigit(a1) && isdigit(b1)){
        return 1;
    }else if(isdigit(a1) && isdigit(b1)){
        if(a1>b1){
            return 1;
        }else{
            return -1;
        }
    }
    if(isalpha(a1)&&!isalpha(b1)){
        return -1;
    }else if(!isalpha(a1) && isalpha(b1)){
        return 1;
    }else if(a1>b1){
        return 1;
    }else if(a1<b1){
        return -1;
    }else{
        return a-b;
    }
    return 0;
}
