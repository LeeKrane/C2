#include<stdio.h>
#include<stdlib.h>
#define NOTEN 12

typedef struct{
    char name[31];
    char klasse[6];
    int noten[12];
}schueler_t;

double NoDu(schueler_t sam);

int main(void){
    double NotDurch;
    schueler_t sam={
        "Samuel Braunauer", "2CHIF", { 2,2,1,4,5,3,5,4,5,2,1,3 }
    };
    NotDurch = NoDu(sam);

    printf("Der Schueler %s aus der %s hat den Notendurchschnitt %lf", sam.name, sam.klasse, NotDurch);

    return 0;
}

double NoDu(schueler_t sam){
    double ND=0;
    int i;

    for(i=0; i<NOTEN; i++){
        ND += sam.noten[i];
    }
    return ND/12;
}
