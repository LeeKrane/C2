#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *makeSubstring(char *text, int von, int bis, int del);

int main(){

    char text[] = "Dies ist ein Test";
    int von=2;
    int bis=7;
    int del=1;

    char *rueck=makeSubstring(text,von,bis,del);
    puts(rueck);

    return 0;
}

char *makeSubstring(char *text, int von, int bis, int del){

    size_t n = strlen(text);
    char *text2=text;
    int i,j;

    for(i=0;i<von;i++){
        text[i]=text2[i];
    }

    for(i=von,j=bis;i<n-(bis-von),j<n;i+=del,j++){
        text[i]=text2[j];
    }
    text[n-(bis-von)+1]='\0';
    return text;
}
