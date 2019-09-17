#include<stdio.h>
#include<stdlib.h>

int *makeTeilFeld(int *ursprungsFeld, int lang, int von, int bis, int *p);

int main(){

    int f[] = {1,12,3,23,34,54,44,33,12};
    int laengeTeilfeld;
    int i;

    int *p = makeTeilFeld(f, 9, 1, 25, &laengeTeilfeld);

    if(p!=0){
        for(i=0;i<5;i++){
            printf("%d ",p[i]);
        }

    }
    else{
        printf("Fehler.");
        return 0;
    }
    free(p);
    return 0;

}

int *makeTeilFeld(int *ursprungsFeld, int lang, int von, int bis, int *p){

    int i=0,j=0;

    *p = 0;

    for(i=0;i<lang;i++){
        if(ursprungsFeld[i]<=bis && ursprungsFeld[i]>=von){
            (*p)++;
        }
    }

    //p=malloc(x);



    if(p!=NULL){
        for(i=0;i<lang;i++){
            if(ursprungsFeld[i]<=bis && ursprungsFeld[i]>=von){
                p[j++]= ursprungsFeld[i];
            }
        }
    }
    else{
        return 0;
    }
    return p;
}
