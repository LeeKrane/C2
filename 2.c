#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int bintodez(char *str);
int deztobin(int zahl,char *str);

int main(int argc, char *argv[]){
    char str[32] = "";
    int x1 = bintodez(argv[1]);
    int x2 = bintodez(argv[3]);
    int x3 = 0;

    if(argc > 4){
        printf("Zuviele Argumente wurden eingegeben!\n");
        return 1;
    }else if(argc < 4){
        printf("Zuwenige Argumente wurden eingegeben!\n");
        return 1;
    }

    switch(argv[2][0]){
        case '+': x3 = x1 + x2;
        break;
        case 'x': x3 = x1 * x2;
        break;
        default:
            printf("Falscher Rechenoperator!\n");
            return 1;
    }

    deztobin(x3,str);

    printf("%s %c %s = %s (%d %c %d = %d)\n",
        argv[1], argv[2][0], argv[3], str,
        x1, argv[2][0], x2, x3);
    return 0;
}

int bintodez(char *str){
    int i;
    int dez=0;
    size_t n = strlen(str);

    if(n==0){
        printf("Es wurden zu wenige Zeichen eingegeben!\n");return-1;
    }

    for(i=0; i<n; i++) {
        if(str[i]!='0' && str[i]!='1'){
            printf("Falsche Eingabe!\n");return -1;
        }
    }

    for(i=0;i<n;i++){
        if(str[i]=='1'){
            dez+=pow(2,n-(i+1));
        }
    }
    return dez;
}

int deztobin(int zahl,char *str) {
    int i=0;

    if(zahl<0){
        printf("Falsche Eingabe!\n");return -1;
    }
    for(i=0; zahl>=1; i++){
        str[i] = zahl%2+'0';
        zahl /= 2;
    }

    str[i] = '\0';
    strrev(str);

    return 0;
}
