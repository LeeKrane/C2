#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Y 0.001

typedef struct{
    double x;
    double y;
} punkt_t;

typedef struct{
    punkt_t center;
    double radius;
} kreis_t;

void readp(punkt_t* p);
void readk(kreis_t* k);
double pruefe(punkt_t* p, kreis_t* k);

int main(void){
    punkt_t p;
    kreis_t k;

    readp(&p);
    readk(&k);

    if(pruefe(&p, &k))
        printf("Der Punkt liegt im Kreis!\n");
    else
        printf("Der Punkt liegt nicht im Kreis!\n");
    return 0;
}

void readp(punkt_t* p){
    printf("Punkt: ");
    if(scanf("%lf %lf", &p->x, &p->x) != 2)
        printf("Falsche Eingabe!\n");
}

void readk(kreis_t* k){
    printf("Kreis: ");
    if(scanf("%lf %lf %lf", &k->center.x, &k->center.y, &k->radius) != 3)
        printf("Falsche Eingabe!\n");
}

double pruefe(punkt_t* p, kreis_t* k){

    if(abs(sqrt(pow(p->x - k->center.x, 2) + pow(p->y - k->center.y, 2)) - k->radius) < Y){
        return 1;
    }
    return 0;
}
