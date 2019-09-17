#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int *merge(int *f1, size_t n1, int *f2, size_t n2);
int cmp(const void *a, const void *b);
void out(int *p, size_t n);

int main(void){
    int f1[] = {3, 7, 5, 3, 9, 1};
    int f2[] = {1, 2, 7, 4};
    size_t n1 = sizeof( f1 ) / sizeof( int );
    size_t n2 = sizeof( f2 ) / sizeof( int );
    int *p;

    p = merge( f1, n1, f2, n2 );
    if(p){
        out( p, n1 + n2 );
        free( p );
    }
    return 0;
}

int *merge(int *f1, size_t n1, int *f2, size_t n2){
    int *speicher = calloc(n1+n2, sizeof(int));

    if(speicher == NULL){
        printf("Fehler beim Reservieren des benoetigten Speichers!");
        return 0;
    }

    memcpy(speicher, f1, n1 * sizeof(int));
    memcpy(speicher+n1, f2, n2 * sizeof(int));

    qsort(speicher, n1+n2, sizeof(int), cmp);

    return speicher;
}

int cmp(const void *a, const void *b){
    const int *a1 = (const int*)a;
    const int *b1 = (const int*)b;

    if((*a1)<(*b1)){ return -1; }
    else if((*a1)>(*b1)){ return 1; }
    return 0;
}

void out(int *p, size_t n){
    int i;

    for(i=0; i<n; i++){
        printf("%d ", p[i]);
    }
}
