#include<stdio.h>
#include<stdlib.h>
int H[101], n;
void buildHeap();
void downHeap(int i);
void printHeap();
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &H[i]);
    buildHeap();
    printHeap();
    return 0;
}
void buildHeap(){
    for(int i = n/2; i >= 1; --i)
        downHeap(i);
}
void downHeap(int i){
    if(H[i*2] == 0 && H[i*2+1] == 0)
        return;
    int bigger = i*2;
    if(H[i*2+1] != 0)
        if(H[i*2+1] > H[bigger])
            bigger = i*2+1;
    if(H[i] >= H[bigger])
        return;
    int tmp = H[i];
    H[i] = H[bigger];
    H[bigger] = tmp;
    downHeap(bigger);    
}
void printHeap(){
    for(int i = 1; i <= n; ++i)
        printf(" %d", H[i]);
    printf("\n");
}