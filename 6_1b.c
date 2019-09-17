#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NOTEN 12
#define ANZ 5

typedef struct{
    char name[31];
    char klasse[6];
    int noten[12];
}schueler_t;

void pre_out();
void out(schueler_t a1[], double NotDu);
double NoDu(schueler_t a1[], int n);
int cmp(const void *a, const void *b);

int main(void){
    srand(time(NULL));
    double NotDurch[ANZ];
    int i, j;
    schueler_t a1[ANZ];

    strcpy(a1[0].name,"Christian Kranabetter");
    a1[0].klasse[0] = "2CHIF";
    a1[1].name[0] = "Samuel Braunauer";
    a1[1].klasse[0] = "2CHIF";
    a1[2].name[0] = "Lukas Mattes";
    a1[2].klasse[0] = "2CHIF";
    a1[3].name[0] = "Fabian Stiefsohn";
    a1[3].klasse[0] = "2CHIF";
    a1[4].name[0] = "Matteo Heindl";
    a1[4].klasse[0] = "2CHIF";

    for(i=0;i<ANZ;i++){
        for(j=0;j<12;j++){
            a1[i].noten[j]=rand()%5+1;
        }
    }
    for(i=0; i<ANZ; i++){
        NotDurch[i] = NoDu(a1, i);
    }
    qsort(NotDurch, ANZ, sizeof(double), cmp);

    pre_out();
    for(i=0; i<ANZ; i++){
        out(&a1[i], NotDurch[i]);
    }

    return 0;
}

double NoDu(schueler_t a1[], int n){
    double ND=0;
    int i;

    for(i=0; i<NOTEN; i++){
        ND += a1[n].noten[i];
    }
    return ND/12;
}

int cmp(const void *a, const void *b){
    double *a1 = (double*) a;
    double *b1 = (double*) b;

    if(*a1 > *b1){
        return 1;
    }else if(*a1 < *b1){
        return -1;
    }
    return 0;
}

void pre_out(){
    printf("Sch%cler                         | Class | Notendurchschnitt\n", 129);
    printf("--------------------------------|-------|------------------\n");
}

void out(schueler_t a1[], double NotDu){
    printf("%31s | %5s | %lf\n", a1->name, a1->klasse, NotDu);
}
