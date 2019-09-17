#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int cmp(const void *a, const void *b);
int zs(int zahl);
void out(int z[], int n);

int main(void){
    int zahl[] = {17, 123, 33, 8, 99};
    int n = sizeof(zahl)/sizeof(int);

    out(zahl, n);
    putchar('\n');
    qsort(zahl, n, sizeof(int), cmp);
    out(zahl, n);

    return 0;
}

int cmp(const void *a, const void *b){
    int *z1 = *(int*) a;
    int *z2 = *(int*) b;

    if(zs(z1)>zs(z2)){
        return 1;
    }else if(zs(z1)<zs(z2)){
        return -1;
    }else if(z1>z2){
        return 1;
    }else if(z1<z2){
        return -1;
    }
    return 0;
}

int zs(int zahl){
    int i=zahl, zs=0;

    while(i>0){
        zs += i%10;
        i /= 10;
    }
    return zs;
}

void out(int z[], int n){
    int i;

    for(i=0; i<n; i++){
        printf("%d ", z[i]);
    }
}
