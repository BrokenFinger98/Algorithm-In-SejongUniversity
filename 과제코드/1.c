#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int *buildList(int n, int min, int max);
int findKthSmallest(int *L, int n, int k);
void buildHeap(int *L, int n);
void downHeap(int *L, int i, int n);
int main(){
    clock_t start, end;
    int *L, output[4], e, copy[100001];

    L = buildList(10, 1, 100);
    for(int i = 1; i <= 10; ++i)
        printf(" %d", L[i]);
    printf("\n");

    for(int k = 1; k < 4; ++k)
        output[k] = findKthSmallest(L, 10, k);

    for(int k = 1; k < 4; ++k)
        printf(" %d", output[k]);
    printf("\n");

    free(L);
    L = NULL;
    L = buildList(100000, 1, 1000000);

    int karray[4] = {1, 100, 99900, 99999};
    for(int k = 0; k < 4; ++k){
        for(int i = 1; i <= 100000; ++i)
            copy[i] = L[i];
        start = clock();
        e = findKthSmallest(copy, 100000, karray[k]);
        end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	    printf(" %d %.12fs\n", e, cpu_time_used);
    }
    free(L);

    return 0;
}
int *buildList(int n, int min, int max){
    int *L;
    srand(time(NULL));
    L = (int *)malloc(sizeof(int) * (n+1));
    for(int i = 1; i <= n; ++i){
        L[i] = rand() % (max - min + 1) + min;
    }
    return L;
}
int findKthSmallest(int *L, int n, int k){
    int tmp;
    
    buildHeap(L, n);
    for(int i = 0; i < k; ++i){
        tmp = L[1];
        L[1] = L[n];
        L[n] = tmp;
        --n;
        downHeap(L, 1, n);
    }
    
    return L[n+1];
}
void buildHeap(int *L, int n){
    for(int i = n/2; i >= 1; --i)
        downHeap(L, i, n);
}
void downHeap(int *L, int i, int n){
    if(i*2>n)
        return;
    int smaller = i*2;
    if(i*2+1 <= n)
        if(L[i*2+1] < L[smaller])
            smaller = i*2+1;
    if(L[i] <= L[smaller])
        return;
    int tmp = L[i];
    L[i] = L[smaller];
    L[smaller] = tmp;
    downHeap(L, smaller, n);    
}
