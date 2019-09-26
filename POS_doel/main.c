#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void init(int a[], size_t n);
int lin_suche(int a[], size_t n, int wert);
int bin_suche(int a[], size_t n, int wert);

int main(){
    int a[1000], lin, bin, wert, num;

    srand((unsigned)time(NULL));

    init(a, 1000);

    printf("linear(1) oder binaer(2)?");
    scanf("%d", &num);

    switch(num){
        case 1:
            do{
                printf("Welchen Wert soll ich linear suchen? ");
                fflush(stdin);
                scanf("%d", &wert);
                lin = lin_suche(a, 1000, wert);
            }while(!lin);

            printf("Der Wert wurde nach %d(lin) Vergleichen gefunden.\n", lin);
        case 0: return 0;
        case 2:
            do{
                printf("Welchen Wert soll ich binaer suchen? ");
                fflush(stdin);
                scanf("%d", &wert);
                bin = bin_suche(a, 1000, wert);
            }while(!lin);

            printf("Der Wert wurde nach %d(bin) Vergleichen gefunden.\n", bin);
        default: return 0;
    }

    return 0;
}

void init(int a[], size_t n){
    int i, x=0;

    for(i=0; i<(signed)n; i++){
        x += rand()%3+1;
        a[i] = x;
    }
}

int lin_suche(int a[], size_t n, int wert){
    int i;

    for(i=0; i<(signed)n; i++){
        if(a[i] == wert)           /// Keine Klammern bedeutet, dass nur die nächste Zeile genommen wird.
            return i+1;
    }
    return 0;
}

int bin_suche(int a[], size_t n, int wert){
    int ober=n-1, unter=0, vergleiche=0, akt;

    while(unter<=ober){
        vergleiche++;
        akt = (ober+unter)/2;
        if(a[akt] == wert){
            return vergleiche;
        }else if(a[akt] < wert){
            unter = akt+1;
        }else{
            ober = akt-1;
        }
    }

    return 0;
}
