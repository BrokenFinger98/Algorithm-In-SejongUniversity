#include<stdio.h>
#include<stdlib.h>
int H[101], n = 0;
void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();
int main(){
    char order;
    int key;
    while (1){
        scanf("%c", &order);
        if(order == 'i'){
            scanf("%d", &key);
            insertItem(key);
            printf("0\n");
        }else if(order == 'd')
            printf("%d\n", removeMax());
        else if(order == 'p')
            printHeap();
        else if(order == 'q')
            return 0;
        getchar();
    }
}
void insertItem(int key){
    ++n;
    H[n] = key;
    upHeap(n);
}
int removeMax(){
    int key = H[1];
    H[1] = H[n];
    H[n] = 0;
    --n;
    downHeap(1);
    return key;
}
void upHeap(int i){
    if(i == 1)
        return;
    if(H[i] <= H[i/2])
        return;
    int tmp = H[i];
    H[i] = H[i/2];
    H[i/2] = tmp;
    upHeap(i/2);
}
void downHeap(int i){
    if(H[i*2] == 0 && H[i*2+1] == 0)
        return;
    int bigger = i*2+1;
    if(H[i*2] != 0)
        if(H[i*2] > H[bigger])
            bigger = i*2;
    if(H[i] > H[bigger])
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

