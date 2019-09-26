//	Author: Christian Kranabetter
//	Klasse: 2CHIF

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void quicksort(int t[], int n);

int main()
{
    int t[] = {8,3,1,2,6,7,0,9,4,5};
    int i;
    for (i=0; i<10; i++)
        printf("%2d", t[i]);
    putchar('\n');
    quicksort(t, 10);
    for (i=0; i<10; i++)
        printf("%2d", t[i]);
    return 0;
}

void quicksort(int t[], int n)
{
    int l = n - 1, r = 0, h;

    //solange l und r nicht zusammensto�en
    while (l > r)
    {
        //gehe von links solange nach rechts, bis ein Element gefunden wird,
        //das gr��er als das Pivot-Element t[n-1] ist
        while (l > r && t[l] >= t[0]) l--;
        //gehe von rechts solange nach linkss, bis ein Element gefunden wird,
        //das kleiner als das Pivot-Element t[n-1] ist
        while (l > r && t[r] <= t[0]) r++;
        //wenn l und r nicht auf das gleiche Element zeigen
        if (l > r)
        {
            //vertausche die beiden Elemente
            h = t[l];
            t[l] = t[r];
            t[r] = h;
        }
    }
    //vertausche das Pivotelement mit dem Element, wo l und r zusammengesto�en sind
    h = t[l];
    t[l] = t[0];
    t[0] = h;

    //wenn n�tig, sortiere den linken Teil
    if (l > 1)
        quicksort(t, l);

    //wenn n�tig, sortiere den rechten Teil
    if (n - l - 1 > 1)
        quicksort(t + l + 1, n - l - 1);
}

