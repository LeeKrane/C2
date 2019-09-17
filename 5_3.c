#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define len 200

int cmp(const void *a, const void *b);
void out(int a[], int n);

int main(void){
    int *arr=malloc(len*sizeof(int));
    int i;

    if(arr==NULL){
        printf("Zu wenig Speicher!");
        return 0;
    }

    srand(time(NULL));

    for(i=0; i<len; i++){
        arr[i] = rand()%21;
    }

    out(arr, len);
    putchar('\n');
    qsort(arr, len, sizeof(int), cmp);
    out(arr, len);

    free(arr);

    return 0;
}

int cmp(const void *a, const void *b){
    const int *z1 = (const int *) a;
    const int *z2 = (const int *) b;

    if(*z1>*z2){
        return -1;
    }else if(*z1<*z2){
        return 1;
    }
    return 0;
}

void out(int a[], int n){
    int i;

    for(i=0; i<n; i++){
        printf("%d ", a[i]);
    }
}
