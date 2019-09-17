#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char buchNummer[11];
    char *titel;
    int bestand;
    double preis;
}buch_t;

buch_t *sucheBuch(buch_t *buecher, int n, char *suchText,int titelOderNummer);
buch_t *fuegeBuecherFeldHinzu(char *dateipfad, buch_t *feld,int *n, int *maximal);
int menue();
int erstelleNeuesBuch(char *textzeile, buch_t *buecher, int anzahlAkt);
int gueltigeBuchNummer(char *text);
void buchEntnahme(buch_t *buecher, int anzahl);
void buchEntfernen(buch_t *buecher, int anzahl, char *buchNummer);
void aendereTitel(buch_t *buchAdresse);
void listeBuchbestand(buch_t *buecher, int anzahl);
void listeBuchbestandGeordnet(buch_t *buecher, int anzahl, int ordnungNach);
void bestellListe(buch_t *buecher, int anzahl);
double lagerWert(buch_t *buecher, int anzahl);
void titelFilter(buch_t *buecher, int anzahl, char *suchText);
void nummerFilter(buch_t *buecher, int anzahl, char *suchText);
void preisFilter(buch_t *buecher, int anzahl, double vergleichsPreis, int mehrOderWeniger);
int speichereBuecher (char *dateipfad, buch_t *buecher, int anzahl);
void toCSVText(const buch_t* buch, char *csvText);
void freeData(buch_t *buecher, int anzahl);
int buchZugang(buch_t *buecher, int anzahlAkt);
int cmpt(const void *a, const void *b);
int cmpp(const void *a, const void *b);
int cmpb(const void *a, const void *b);

int main(int argc, char * argv[]){
    buch_t *buecher;
    buch_t *z;
    char buchNummer[1000];
    char suchText[100];
    char suchNummer[11];
    char s[1000];
    char csvText[1000];
    double preis,erg;
    int titeloderNummer;
    int n=0,ok,x,i;
    int maximal=10,auswahl;

    ///Auf korrekte Anzahl der Kommandozeilen-Paramater prüfen
    if(argc == 2){
        ///Erzeugung des dynamischen Feldes
        buecher = (buch_t *)malloc(maximal * sizeof(buch_t));
        if(buecher != NULL){
            printf("Speicherplatz wurde erfolgreich reserviert!\n");
            buecher = fuegeBuecherFeldHinzu(argv[1],buecher,&n,&maximal);
            ///Menü aufrufen
            do{
                auswahl = menue();

                switch(auswahl){
                    case 1:
                        buchEntnahme(buecher, n);
                        printf("Buecher wurden erfolgreich Entnommen!\n");
                        break;
                    case 2:
                        if(buchZugang(buecher,n)!=0){
                            printf("Buch wurde erfolgreich hinzugefuegt!\n");
                            n++;
                        }else{
                            printf("Falsche Eingabe!\n");
                        }
                        break;
                    case 3:
                        printf("Nummer des Buches eingeben!\n");
                        scanf("%s",&buchNummer);
                        buchEntfernen(buecher, n, buchNummer);
                        printf("Buecher erfolgreich entfernt!\n");
                        n--;
                        break;
                    case 4:
                        ok =0;
                        printf("Wollen Sie nach einem Titel suchen? -->       1\n");
                        printf("Wollen Sie nach einer Buchnummer suchen? -->  2\n");
                        scanf("%d",&titeloderNummer);
                        if(titeloderNummer == 1){
                            printf("Nach was fuer einem Titel wollen Sie suchen? --> \n");
                            scanf("%s",&suchText);
                        }else if(titeloderNummer == 2){
                            printf("Nach was fuer einer Buchnummer wollen Sie suchen? --> \n");
                            scanf("%s",&suchText);
                        }else{
                            printf("Falsche Eingabe!\n");
                            ok =1;
                        }
                        z = sucheBuch(buecher,n,suchText,titeloderNummer);
                        printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
                        printf("------------|-----------|-------------|-------------\n");
                        printf("%10s  |  %7d  |  %9.2lf  |  %s\n", z[0].buchNummer, z[0].bestand, z[0].preis, z[0].titel);
                        break;
                    case 5:
                        printf("Geben Sie die Buchnummer des Buches ein, von welchem der Titel geaendert werden soll!\n");
                        gets(s);
                        for(i=0;i<n;i++){
                            if(strcmp(s,buecher[i].buchNummer)==0){
                                aendereTitel(&buecher[i]);
                                break;
                            }
                        }
                        break;
                    case 6:
                        listeBuchbestand(buecher,n);
                        break;
                    case 7:
                        printf("Nach was soll sortiert werden:\n");
                        printf("Titel...1\n");
                        printf("Preis...2\n");
                        printf("Nummer...3\n");
                        scanf("%d",&x);
                        listeBuchbestandGeordnet(buecher, n, x);
                        break;
                    case 8:
                        bestellListe(buecher, n);
                        break;
                    case 9:
                        printf("Filtern nach Titel -->          1\n");
                        printf("Filtern nach Preis -->          2\n");
                        printf("Filtern nach Buchnummer -->     3\n");
                        scanf("%d",&x);
                    switch(x){
                        case 1:
                            printf("Bitte geben Sie den gewuenschten Titel ein --> \n");
                            scanf("%s",&suchText);
                            titelFilter(buecher,n,suchText);
                            break;
                        case 2:
                            printf("Nach welchem Preis soll gefiltert werden?\n");
                            scanf("%lf",&preis);
                            printf("Mehr...1\n");
                            printf("Weniger...2\n");
                            scanf("%d",&x);
                            preisFilter(buecher, n, preis, x);
                            break;
                        case 3:
                            printf("Bitte geben Sie die gewuenschte Nummer ein --> \n");
                            scanf("%s",&suchNummer);
                            nummerFilter(buecher,n,suchNummer);
                            break;
                        default:
                            printf("Falsche Eingabe!\n");
                            return 0;
                        }
                    case 10:
                        freeData(buecher, n);
                        break;
                    case 11:
                        printf("Geben Sie die Buchnummer des Buches ein, welches in die Csv Datei geschrieben werden soll!\n");
                        gets(s);
                        for(i=0;i<n;i++){
                            if(strcmp(s,buecher[i].buchNummer)==0){
                                toCSVText(&buecher[i],csvText);
                            }
                        }
                        break;
                    case 12:
                        erg = lagerWert(buecher,n);
                        printf("Lagerwert: %g\n",erg);
                        break;
                    case 13:
                        printf("Dateipfad eingeben: \n");
                        gets(s);
                        speichereBuecher(s,buecher,n);
                        break;
                    }
            }while(auswahl != 14);

            freeData(buecher,n);
        }else{
            printf("Speicherplatz konnte nicht reserviert werden!\n");
            return 1;
        }
    }else{
        printf("Ungueltige Eingabe! Zuviele oder Zuwenig Parameter!\n");
        printf("Moeglicher Aufruf: %s DATEINAME.csv\n",argv[0]);
        return 1;
    }
    ///Programm wird ohne Fehler beendet
    return 0;
}

/// Fügt Bücher mit der übergebenen Datei hinzu

buch_t *fuegeBuecherFeldHinzu(char *dateipfad, buch_t *feld,int *n, int *maximal){
    FILE *    fp = fopen(dateipfad,"r");
    char ein[2000];
    char s[1000];
    if(fp != NULL){
        printf("Datei erfolgreich geoeffnet!\n");
        fgets(s,sizeof(s),fp);
        while(fgets(ein,sizeof(ein),fp)){
            ///Kontrolle ob n bereits größer als 80% ist
            if(*n >= (*maximal)*0.8){
                ///Maximal um 10 Einheiten vergrößern
                (*maximal) += 10;
                ///weitere 10 Einheiten zuum Feld hinzufügen
                feld = (buch_t *)realloc(feld,(*maximal) * sizeof(buch_t));
            }
            if((erstelleNeuesBuch(ein,feld,*n))==0){
                (*n)--;
            }
            (*n)++;
        }
        fclose(fp);
    }else{
        printf("Oeffnen der Datei (%s) hat nicht funktioniert!\n",dateipfad);
        return 0;
    }
    return feld;
}

/// Menü

int menue(){
    // system("cls");
    int auswahl,ok;
    char enter;
    do{
        printf("-----------------------------------------------------------------------\n");
        printf("                            Menue\n");
        printf("-----------------------------------------------------------------------\n");
        printf("Auswahlm%cglichkeiten: \n",148);
        printf("Buecher entnehmen -->                                             1\n");
        printf("Buecher hinufuegen -->                                             2\n");
        printf("Buchnummer loeschen -->                                           3\n");
        printf("Bestimmtes Buch suchen -->                                       4\n");
        printf("Aendern des Buchtitels -->                                        5\n");
        printf("Ausgabe des gesamten Buchbestandes -->                           6\n");
        printf("Ausgabe des sortierten Buchbestandes -->                         7\n");
        printf("Ausgabe von den Bestellisten -->                                 8\n");
        printf("Filtern nach bestimmten Kriterien -->                            9\n");
        printf("Freigeben von allen angeforderten Speichern -->                 10\n");
        printf("Speichern des aktuellen Feldes in einer neuen csv- Datei -->    11\n");
        printf("Ausgabe des aktuellen Wertes des Gesamtlagers -->               12\n");
        printf("Speichern aller Daten is csv Datei -->                          13\n");
        printf("Programm beenden -->                                            14\n");
        printf("-----------------------------------------------------------------------\n");

        printf("Was moechten Sie tun? --> ");
        ok = scanf("%d%c",&auswahl,&enter);
        fflush(stdin);
        //  system("cls");

        if(ok != 2 || enter != '\n' || auswahl < 1 || auswahl > 14){
            printf("Auswahl hat nicht funktioniert! Versuchen Sie es erneut!\n");
            continue;
        }
    }while(ok != 2 || enter != '\n');

    return auswahl;
}

/// Buch suchen

buch_t *sucheBuch(buch_t *buecher, int n, char *suchText,int titelOderNummer){
    int i, j, k, l;
    size_t count=0;

    if(titelOderNummer==1){
        for(i=0; i<n; i++){
            for(j=0; j<strlen(buecher[i].titel); j++){
                for(k=j, l=0; k<(strlen(buecher[i].titel)-j); k++, l++){
                    if(buecher[i].titel[k] == suchText[l]){
                        count++;
                    }
                    if(count==strlen(suchText)){
                        return &buecher[i];
                    }
                }
            }
        }
    }else if(titelOderNummer==2){
        for(i=0; i<n; i++){
            for(j=0; j<strlen(buecher[i].buchNummer); j++){
                for(k=j, l=0; k<(strlen(buecher[i].buchNummer)-j); k++, l++){
                    if(buecher[i].buchNummer[k] == suchText[l]){
                        count++;
                    }
                    if(count==strlen(suchText)){
                        return &buecher[i];
                    }
                }
            }
        }
    }
    return 0;
}

/// Neues Buch erstellen

int erstelleNeuesBuch(char *textzeile, buch_t *buecher, int anzahlAkt){
    char cpy[1000] = "";
    int test,i;
    double test2;

    strcpy(cpy,textzeile);

    if((gueltigeBuchNummer(strtok(cpy,";")))==0){
        return 0;
    }
    strtok(NULL,";");
    sscanf(strtok(NULL,";"),"%d",&test);
    sscanf(strtok(NULL,";"),"%lf",&test2);
    strcpy(buecher[anzahlAkt].buchNummer,strtok(textzeile,";"));
    strcpy(cpy, strtok(NULL,";"));
    buecher[anzahlAkt].titel = calloc(strlen(cpy)+1,sizeof(char)); ///Speicher allokieren
    strcpy(buecher[anzahlAkt].titel, cpy);
    buecher[anzahlAkt].bestand = atoi(strtok(NULL,";"));
    buecher[anzahlAkt].preis = atof(strtok(NULL,";"));
    if(buecher[anzahlAkt].preis <= 0 || buecher[anzahlAkt].bestand <= 0){
        return 0;
    }
    for(i=0;i<anzahlAkt;i++){
        if(strcmp(buecher[anzahlAkt].titel,buecher[i].titel)==0){
            buecher[i].bestand+=buecher[anzahlAkt].bestand;
            return 0;
        }
    }
    for(i=0;i<anzahlAkt;i++){
       if(strcmp(buecher[anzahlAkt].buchNummer,buecher[i].buchNummer)==0){
           return 0;
        }
    }
    return 1;
}

/// Gueltige Buchnummer

int gueltigeBuchNummer(char *text){
    int i;
    int n = strlen(text);
    if(n!=10){
        return 0;
    }
    for(i=0; i<3; i++){
        if(text[i] < 'A' || text[i] > 'Z')
        return 0;
    }
    for(i=3; i<n; i++){
        if(text[i] < '0' || text[i] > '9')
        return 0;
    }
    return 1;
}

/// Buch Zugang

int buchZugang(buch_t *buecher, int anzahlAkt){
    char y[1000];
    printf("Daten eines neuen Buches eingeben: \n");
    printf("Neues Buch eingeben: (Nummer;Titel;Bestand;Preis)\n");
    gets(y);
    if(erstelleNeuesBuch(y,buecher,anzahlAkt)==0){
        return 0;
    }

    return 1;
}

/// Buch entnahme

void buchEntnahme(buch_t *buecher, int anzahl){
    char x[1000];
    int i,y;
    printf("Wieviele Buecher sollen entnommen werden?\n");
    scanf("%d",&y);
    if(isdigit(y)){
        printf("Falsche Eingabe!\n");
        fflush(stdin);
    }
    printf("Welches Buch soll entnommen werden?\n");
    printf("Buchnummer eingeben: \n");
    scanf("%s",&x);
    fflush(stdin);
    if(gueltigeBuchNummer(x)==0){
        printf("Falsche Buchnummer!\n");

    }
    for(i=0; i<anzahl; i++){
        if(strcmp(x,buecher[i].buchNummer)==0){
            buecher[i].bestand-=y;

            break;
        }else if(strcmp(x,buecher[i].buchNummer)!=0&&i==anzahl-1){
            printf("Das Buch ist nich vorhanden!\n");
        }
    }
    if(buecher[i].bestand<0){
        printf("Es wurden zu viele Buecher entnommen!\n");
        buecher[i].bestand+=y;

    }
}

/// Buch entfernen

void buchEntfernen(buch_t *buecher, int anzahl, char *buchNummer){
    int i,j;
    for(i=0; i<anzahl; i++){
        if(strcmp(buecher[i].buchNummer,buchNummer)==0){
            for(j=i; j<anzahl; j++){
                buecher[j]=buecher[j+1];
            }
            break;
        }else if(strcmp(buecher[i].buchNummer,buchNummer)!=0&&i==anzahl-1){
            printf("Es gibt kein Buch mit dieser Nummer!\n");
        }
    }
}

/// Titel ändern

void aendereTitel(buch_t *buchAdresse){
    char s[1000]={};

    printf("Neuer Titel: ");
    gets(s);

    buchAdresse->titel = realloc(buchAdresse->titel, strlen(s)*sizeof(char));
    strcpy(buchAdresse->titel,s);

    if(buchAdresse==NULL){
    printf("Zu wenig Speicher!\n");
    }
}

/// Buch bestand auflisten

void listeBuchbestand(buch_t *buecher, int anzahl){
    int i;
    printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
    printf("------------|-----------|-------------|-------------\n");
    for(i=0; i<anzahl; i++){
        printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
    }
//    getchar(); - Führt zur benötigung eines Zweiten Enters nach der Ausgabe
}

/// Buch bestand sortiert auflisten

void listeBuchbestandGeordnet(buch_t *buecher, int anzahl, int ordnungNach){
    switch(ordnungNach){
        case 1:
            qsort(buecher,anzahl,sizeof(buch_t),cmpt);
            break;
        case 2:
            qsort(buecher,anzahl,sizeof(buch_t),cmpp);
            break;
        case 3:
            qsort(buecher,anzahl,sizeof(buch_t),cmpb);
            break;
        default:
            printf("Falsche Eingabe!\n");
    }
    int i;
    printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
    printf("------------|-----------|-------------|-------------\n");
    for(i=0; i<anzahl; i++){
        printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
    }
    getchar();
}

/// Bestell Liste ausgeben

void bestellListe(buch_t *buecher, int anzahl){
    int i;
    for(i=0; i<anzahl; i++){
        if(buecher[i].bestand<5){
            printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
        }
    }
}

/// Lagerwert

double lagerWert(buch_t *buecher, int anzahl){
    int i;
    double preis=0;

    for(i=0; i<anzahl; i++){
        preis+=buecher[i].preis*buecher[i].bestand;
    }
    return preis;
}

/// Filtern nach Titel

void titelFilter(buch_t *buecher, int anzahl, char *suchText){
    int i;
    printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
    printf("------------|-----------|-------------|-------------\n");
    for(i=0; i<anzahl; i++){
        if(strcmp(buecher[i].titel,suchText)==0){
            printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
        }
    }
}

/// Filtern nach Preis

void preisFilter(buch_t *buecher, int anzahl, double vergleichsPreis, int mehrOderWeniger){
    int i;
    printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
    printf("------------|-----------|-------------|-------------\n");
    switch(mehrOderWeniger){
        case 1:
            for(i=0; i<anzahl; i++){
                if(buecher[i].preis>=vergleichsPreis){
                    printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
                }
            }
            break;
        case 2:
            for(i=0; i<anzahl; i++){
                if(buecher[i].preis<=vergleichsPreis){
                    printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
                }
            }
            break;
        default:
            printf("Falsche Eingabe!\n");
            break;
    }

}

/// Filtern nach Buchnummer

void nummerFilter(buch_t *buecher, int anzahl, char *suchText){
    int i;
    printf("Buchnummer  |  Bestand  |    Preis    |  Titel\n");
    printf("------------|-----------|-------------|-------------\n");
    for(i=0; i<anzahl; i++){
        if(strcmp(buecher[i].buchNummer,suchText)==0){
            printf("%10s  |  %7d  |  %9.2lf  |  %s\n", buecher[i].buchNummer, buecher[i].bestand, buecher[i].preis, buecher[i].titel);
        }
    }
}

/// Speichere Buecher

int speichereBuecher (char *dateipfad, buch_t *buecher, int anzahl){
    int x,i;
    FILE *fp;
    printf("Daten sollen an der Datei angehaengt werden...1\n");
    printf("Daten sollen ueberschrieben werden...2\n");
    printf("Neue Datei soll erstellt werden...3\n");
    scanf("%d",&x);
    switch(x){
        case 1: fp = fopen(dateipfad,"a");
            for(i=0;i<anzahl;i++){
                fprintf(fp,"%s;%s;%d;%lf\n",buecher[i].buchNummer,buecher[i].titel,buecher[i].bestand,buecher[i].preis);
            }
            break;
        case 2: fp = fopen(dateipfad,"w");
            for(i=0;i<anzahl;i++){
                fprintf(fp,"%s;%s;%d;%lf\n",buecher[i].buchNummer,buecher[i].titel,buecher[i].bestand,buecher[i].preis);
            }
            break;
        case 3: fp = fopen(dateipfad,"w");
            for(i=0;i<anzahl;i++){
                fprintf(fp,"%s;%s;%d;%lf\n",buecher[i].buchNummer,buecher[i].titel,buecher[i].bestand,buecher[i].preis);
            }
            break;
        default:
            printf("Falsche Eingabe!\n");
            break;
    }
    return 0;
}

/// Speichert das aktuelle Feld in csv Datei

void toCSVText(const buch_t* buch, char *csvText){
    sprintf(csvText,"%s, %s, %d, %lf",buch->buchNummer,buch->titel,buch->bestand,buch->preis);
}

/// Gibt alle dynamisch angeforderten Speicher frei

void freeData(buch_t *buecher, int anzahl){
    int i;

    if(buecher != NULL){
        for(i=0; i<anzahl; i++){
            free((buecher+i)->titel);
        }
        free(buecher);
    }
}

int cmpt(const void *a, const void *b){
    buch_t *a1 = (buch_t*) a;
    buch_t *b1 = (buch_t*) b;

    return strcmp(a1->titel,b1->titel);
}

int cmpp(const void *a, const void *b){
    buch_t *a1 = (buch_t*) a;
    buch_t *b1 = (buch_t*) b;

    if(a1->preis>b1->preis){
        return -1;
    }
    else if(a1->preis<b1->preis){
        return 1;
    }

    return 0;
}

int cmpb(const void *a, const void *b){
    buch_t *a1 = (buch_t*) a;
    buch_t *b1 = (buch_t*) b;

    return strcmp(a1->buchNummer,b1->buchNummer);
}
