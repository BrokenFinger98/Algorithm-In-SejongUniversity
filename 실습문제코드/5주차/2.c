#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void inPlaceQuickSort(int *y, int l, int r);
int findPivot(int *y, int l, int r);
int inPlacePartition(int *y, int l, int r, int k);
void swap(int *y, int i, int j);
int n;
int *x;
int main(){
    srand(time(NULL));
    scanf("%d", &n);
    x = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &x[i]);
    inPlaceQuickSort(x, 0, n-1);
    for(int i = 0; i < n; ++i)
        printf(" %d", x[i]);
    printf("\n");
    free(x);
    return 0;
}
void inPlaceQuickSort(int *y, int l, int r){
    if(l>=r)
        return;
    int k = findPivot(y, l, r);
    int a = inPlacePartition(y, l, r, k);
    inPlaceQuickSort(y, l, a-1);
    inPlaceQuickSort(y, a+1, r);
}
int findPivot(int *y, int l, int r){
    return rand() % (r - l + 1) + l;
}
int inPlacePartition(int *y, int l, int r, int k){
    int p = y[k];
    swap(y, k, r);
    int i = l;
    int j = r-1;
    while (i<=j){
        while (i<=j && y[i]<=p)
            i++;
        while (j>=i && y[j]>=p)
            --j;
        if(i<j)
            swap(y, i, j);
    }
    swap(y, i, r);
    return i;
}
void swap(int *y, int i, int j){
    int tmp = y[i];
    y[i] = y[j];
    y[j] = tmp;
}
