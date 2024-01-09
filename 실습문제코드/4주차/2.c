#include<stdio.h>
#include<stdlib.h>
int H[100], n, k;
void buildHeap();
void downHeap(int i);
void inPlaceHeapSort();
void printHeap();
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &H[i]);
    buildHeap();
    k = n;
    inPlaceHeapSort();
    printHeap();
    return 0;
}
void buildHeap(){
    for(int i = n/2; i >= 1; --i)
        downHeap(i);
}
void downHeap(int i){
    if(i*2>n)
        return;
    int bigger = i*2;
    if(i*2+1 <= n)
        if(H[i*2+1] > H[bigger])
            bigger = i*2+1;
    if(H[i] >= H[bigger])
        return;
    int tmp = H[i];
    H[i] = H[bigger];
    H[bigger] = tmp;
    downHeap(bigger);    
}
void inPlaceHeapSort(){
    int tmp;
    for(int i = n; i > 1; --i){
        tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        --n;
        downHeap(1);
    }
}
void printHeap(){
    for(int i = 1; i <= k; ++i)
        printf(" %d", H[i]);
    printf("\n");
}