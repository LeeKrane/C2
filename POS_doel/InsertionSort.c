#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void s_sat(int *a, size_t n);
void init2(int a[], size_t n);

int main() {
    int a[1000],i;
    size_t n= sizeof(a)/sizeof(a[0]);
    srand((unsigned)time(NULL));

    init2(a,1000);
    for(i=0; i<n;i++)
        printf("%d\n",a[i]);

    printf("Sortiert");
	
    for(i=0; i<n;i++)
        printf("%d\n",a[i]);

    return 0;
}
void s_sat(int *a, size_t n) {
    int akt, help,i;
    for(akt=1; akt<n; akt++) {
        help=a[akt];

        for(i=akt-1; i>=0 && a[i]>help;i--)
            a[i+1]=a[i];
		
        a[i+1]=help;
    }
}

void init2(int a[], size_t n) {
    int i, x=0;
    for(i=0; i<(signed)n; i++) {
        x+= rand()%1000;
        a[i]= x;
    }
}
