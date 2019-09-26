#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

void init(int arr[], int n);
int merge_sort(int arr[], int n);
int merge(int arr[], int n, int m);

int main(void){
    int arr[100] = {};
    int n = sizeof(arr)/sizeof(arr[0]);
    int sortcount, c=0, i;

    srand((unsigned)time(NULL));

    init(arr, n);
    sortcount = merge_sort(arr, n);

    printf("sortcount: %d\n\n", sortcount);

    for(i=0; i<n; i++){
        printf("%3d", arr[i]);
        c++;
        if(c%10==0){
            putchar('\n');
        }
    }

    return 0;
}

void init(int arr[], int n){
    int i;

    for(i=0; i<(signed)n; i++){
        arr[i] = rand()%100;
    }
}

int merge_sort(int arr[], int n){
    int counter = 0;

    counter++;

    if(n > 1){
        counter += merge_sort(arr, n/2);
        counter += merge_sort(arr+n/2, n-n/2);
        counter += merge(arr, n/2, n-n/2);
    }

    return counter;
}

int merge(int arr[], int n, int m){
    int count = 0, i = 0, j = 0;
    int x[1000] = {0};
    int y[1000] = {0};

    memcpy(x, arr, n*sizeof(int));
    memcpy(y, arr+n, m*sizeof(int));

    while(i<n && j<m){
        if(x[i]<y[j]){
            arr[i+j] = x[i];
            i++;
        }else{
            arr[i+j] = y[j];
            j++;
        }
        count++;
    }

    memcpy(arr+i+j, x+i, (n-i)*sizeof(int));
    /*  Selbes Ergebnis wie:
    for(; i<n; i++){
        a[i+j] = x[i];
    } */
    memcpy(arr+i+j, y+j, (m-j)*sizeof(int));
    /*  Selbes Ergebnis wie:
    for(; j<m; j++){
        a[i+j] = y[j];
    } */

    return count;
}
