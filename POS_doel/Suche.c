#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void init(int a[], size_t n);
int lin_suche(int a[], size_t n, int wert);
int bin_suche(int a[], size_t n, int wert);


int main1() {
    int a[1000],lin, bin, wert;

    srand((unsigned)time(NULL));

    init(a, 1000);

    do {
        printf("Welchen wert wollen sie?");
        fflush(stdin);
        scanf("%d",&wert);
        bin =  bin_suche(a,1000,wert);
    } while(!bin);

    printf("Der Wert wurde nach %d(lin) vergleichen gefunden.\n",bin);

    return 0;
}

void init(int a[], size_t n) {
    int i, x=0;
    for(i=0; i<(signed)n; i++) {
        x+= rand()%3+1;
        a[i]= x;
    }
}
int lin_suche(int a[], size_t n, int wert) {
    int i;
    for(i=0; i<(signed)n; i++) {
        if(a[i] == wert)
            return i+1;
    }
    return 0;
}
int bin_suche(int a[], size_t n, int wert) {
    int ober = n-1;
    int unter= 0;
    int vergleiche =0;
    int akt=0;

    while(unter<=ober) {
        vergleiche++;
        akt=(ober+unter)/2;
        if(a[akt]== wert)
            return vergleiche;
        else if(a[akt]<wert)
            unter= akt+1;
        else
			ober= akt-1;
    }

    return 0;
}
