#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int *foo(int a, int b);

int main(void)
{
    int a=0, b=0, i;
    int *c = NULL;
    int n;

    printf("Wert 1 = ");
    scanf("%d", &a);
    printf("Wert 2 = ");
    scanf("%d", &b);

    c = foo(a,b);

    if(a>b)
    {
        n=(a-b)+1;
    }
    else if(a<b)
    {
        n=(b-a)+1;
    }
    else
    {
        n=1;
    }

    for(i=0; i<n; i++)
    {
        printf("%d ", c[i]);
    }

    free(c);

    return 0;
}

int *foo(int a, int b)
{
    int *speicher = NULL;
    int i, j;

    if(a>b)
    {
        speicher = malloc(((a-b)+1) * sizeof(int));

        for(i=a, j=0; i>=b; i--, j++)
        {
            speicher[j] = i;
        }
    }
    else if(b>a)
    {
        speicher = malloc(((b-a)+1) * sizeof(int));

        for(i=a, j=0; i<=b; i++, j++)
        {
            speicher[j] = i;
        }
    }
    else
    {
        speicher = malloc(1*sizeof(int));
        speicher[0] = a;
    }
    if(speicher == NULL)
    {
        printf("Zu wenig Speicher zur Verfuegung!");
        return 0;
    }
    return speicher;
}
