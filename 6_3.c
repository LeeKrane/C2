#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
    double x;
    double y;
}pt_t;  /// Punkte

typedef struct{
    pt_t start;
    pt_t stop;
}tr_t;  /// Strecken

double len(const tr_t *s);                      /// Länge
double umfg(const pt_t *nEck, size_t n);        /// Umfang

int main(void){
    size_t n = 3;
    pt_t pts[] = {{1,1}, {4,1}, {4,5}};
    double umf = umfg(pts, n);

    printf("Der Umfang aller Strecken --> %.3lf", umf);

    return 0;
}

/// Diese Funktion dient zur Berechnung der Strecke zwischen zwei Punkten

double len(const tr_t *s){
    double leng;

    /// Absoluter Wert des Abstandes der Punkte
    leng = abs(sqrt(pow(s->start.x - s->stop.x,2) + pow(s->start.y - s->stop.y,2)));

    return leng;
}

/// Diese Funktion dient zur Berechnung des Umfangs

double umfg(const pt_t *nEck, size_t n){
    double umfng;
    int i;
    tr_t a[n];

    /// Setzung der Punkte der ersten beiden Strecken
    for(i=0; i<n-1; i++){
        a[i].start.x=nEck[i].x;
        a[i].start.y=nEck[i].y;
        a[i].stop.x=nEck[i+1].x;
        a[i].stop.y=nEck[i+1].y;
    }

    /// Setzung der Punkte der letzten Strecke
    a[i].start.x=nEck[i].x;
    a[i].start.y=nEck[i].y;
    a[i].stop.x=nEck[0].x;
    a[i].stop.y=nEck[0].y;

    /// Berechnung des Umfangs per "len" Funktion
    for(i=0; i<n; i++){
        umfng+=len(&a[i]);
    }
    return umfng;
}
