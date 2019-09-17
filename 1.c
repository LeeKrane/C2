#include<stdio.h>
#include<stdlib.h>
#define anz 6
#include<string.h>

const char* cities [anz] = {"Wien","Linz","Graz","Salzburg","Innsbruck","Klagenfurt"};
int weg(int from, int to);
int getIndex(char *city);

const int strecken[anz][anz] = {
    {  0, 188, 204, 302, 468, 310},
    {188,   0, 276, 125, 291, 274},
    {204, 276,   0, 278, 444, 152},
    {302, 125, 278,   0, 166, 242},
    {468, 291, 444, 166,   0, 326},
    {310, 274, 152, 242, 326,   0}
};

int main(int argc, char* argv[]) {
    int i = 0;
    int summe = 0;

    if(argc<=2){
        printf("Fehlerhafte Eingabe!\n");

    return 0;
    }

    for(i=1;i<argc-1;i++){
        summe+=weg(getIndex(argv[i]),getIndex(argv[i+1]));
    }

    printf("Die Strecke ");

    for(i=1;i<argc-1;i++){
        printf("%s --> ",argv[i]);
    }

    printf("%s ",argv[argc-1]);
    printf("betraegt %dkm.\n",summe);

    return 0;
}

int weg(int from, int to){
    int summe=0;
    summe=strecken[from][to];

    return summe;
}

int getIndex(char *city) {
    int i;
    for(i=0; i<anz; i++) {
        if(strcmp(city,cities[i])==0 || (city[0]==cities[i][0] && strlen(city) == 1)){
            return i;
        }
    }
    return -1;
};
