#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int n = 100000;
int Limits[4] = {1, 100, 500, 1000};
int Limit;
int mode;
int *createArray();
void quickSort(int *A, int k);
void rQuickSort(int *A, int l, int r);
int inPlacePartition(int *A, int l, int r, int k);
void swap(int *A, int i, int j);
void insertSort(int *A, int k);
int findPivot(int *A, int l, int r);
int findIndexOfMedianOfThree(int *A, int a, int b, int c);
int *copyArray(int *A);
int main(){
    int *A = createArray();
    int *tmp;
    clock_t start, end;
    srand(time(NULL));
    for(int i = 0; i < 4; ++i){
        Limit = Limits[i];
        printf("%d", Limits[i]);
        for(int  j = 0; j < 4; ++j){
            mode = j;
            tmp = copyArray(A);

            start = clock();
            quickSort(tmp, n);
            end = clock();
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
            printf("\t%.8fms", cpu_time_used);
        }
        free(tmp);
        printf("\n");
    }
    free(A);
    return 0;
}
int *createArray(){
    int *A = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        A[i] = rand() % n + 1;
    return A; 
}
void quickSort(int *tmp, int k){
    rQuickSort(tmp, 0, k-1);
    if(Limit > 1)
        insertSort(tmp, k);
}
void rQuickSort(int *A, int l, int r){
    int k, a;
    if(r - l >= Limit){
        k = findPivot(A, l, r);
        a = inPlacePartition(A, l, r, k);
        rQuickSort(A, l, a-1);
        rQuickSort(A, a+1, r);
    }
}
int inPlacePartition(int *A, int l, int r, int k){
    int p = A[k];
    swap(A, k, r);
    int i = l;
    int j = r-1;
    while (i<=j){
        while (i<=j && A[i]<=p)
            i++;
        while (j>=i && A[j]>=p)
            --j;
        if(i<j)
            swap(A, i, j);
    }
    swap(A, i, r);
    return i;
}
void swap(int *A, int i, int j){
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
void insertSort(int *A, int k){
    int save, tmp, i, j;
    for(i = 1; i < n; ++i){
        save = A[i];
        j = i-1;
        while ((j>=0) && (A[j] > save)){
            A[j+1] = A[j];
            --j;
        }
        A[j+1] = save;
    }
}
int findPivot(int *A, int l, int r){
    int a, b, c;
    if(mode == 0)
        return r;
    if(mode == 2)
        return rand() % (r - l + 1) + l;
    if(r - l == 1)
        return l;
    switch (mode){
    case 1: 
        a = l; b = (l+r)/2; c = r;
        break;
    case 3:
        a = rand() % (r - l + 1) + l;
        b = rand() % (r - l + 1) + l;
        c = rand() % (r - l + 1) + l;
        break;
    default:
        break;
    }
    return findIndexOfMedianOfThree(A, a, b, c);
}
int findIndexOfMedianOfThree(int *A, int a, int b, int c){
    int x = A[a], y = A[b], z = A[c];
    if(x > y && x > z){
        if(y > z)
            return b;
        else
            return c;
    }else if(y > x && y > z){
        if(x > z)
            return a;
        else   
            return c;
    }else{
        if(x > y)
            return a;
        else
            return b;
    }
}
int *copyArray(int *A){
    int *tmp = (int *)malloc(sizeof(int)*n);
    for(int i = 0; i < n; ++i)
        tmp[i] = A[i];
    return tmp;
}