#include<stdio.h>
#include<stdlib.h>
typedef struct hashTable{
    int e;
    int activeStatus;
    /*
    inactive = -1;
    empty = 0;
    active = 1;
    */
}hashTable;
int M = 23;
int q = 11;
hashTable *H;
void initHashTable() {
    H = (hashTable *)malloc(M * sizeof(hashTable));
    for (int i = 0; i < M; i++){
        H[i].e = 0;
        H[i].activeStatus = 0;
    }
}
int h1(int k) {
    return k % M;
}
int h2(int k) {
    return q - (k % q);
}
int getNextIndex(int v, int i, int k) {
    return (v + i * h2(k)) % M;
}
void insertItem(int k) {
    int index;
    int v = h1(k);
    int i = 0;

    while (i < M) {
        index = getNextIndex(v, i, k);
        if (H[index].activeStatus == 0 || H[index].activeStatus == -1) {
            H[index].e = k;
            H[index].activeStatus = 1;
            return;
        }else if(H[index].e == k){
            printf("sameKeyErrorException\n");
            return;
        }else 
            i++;
    }
    printf("overflowException\n");
}
int findElement(int k){
    int index;
    int v = h1(k);
    int i = 0, e;

    while (i < M) {
        index = getNextIndex(v, i, k);
        e = H[index].e;
        if (e == 0) 
            return -1;
        else if (e == k && H[index].activeStatus == 1) {
            return e;
        } else 
            i++;
    }
    return -1;
}
int removeElement(int k){
    int index;
    int v = h1(k);
    int i = 0, e;

    while (i < M) {
        index = getNextIndex(v, i, k);
        e = H[index].e;
        if (e == 0) 
            return -1;
        else if (e == k && H[index].activeStatus == 1) {
            H[index].e = 0;
            H[index].activeStatus = -1;
            return e;
        } else 
            i++;
    }
    return -1;
}
void printHashTable(){
    int e;
    for(int i = 0; i < M; ++i){
        printf(" %2d", i);
    }
    printf("\n");
    for(int i = 0; i < M; ++i){
        e = H[i].e;
        if(e == 0)
            printf("  .");
        else
            printf(" %2d", e);
    }
    printf("\n");
}
int main(){
    char cmd;
    int k, e;
    initHashTable();

    while (1){
        scanf(" %c", &cmd);
        if(cmd == 'f'){
            scanf("%d", &k);
            e = findElement(k);
            if(e == -1)
                printf("NoSuchKey\n");
            else
                printf("%d\n", e);
        }else if(cmd == 'i'){
            scanf("%d", &k);
            if(k > 0 && k < 99)
                insertItem(k);
        }else if(cmd == 'r'){
            scanf("%d", &k);
            e = removeElement(k);
            if(e == -1)
                printf("NoSuchKey\n");
            else
                printf("%d\n", e);
        }else if(cmd == 'p')
            printHashTable(); 
        else if(cmd == 'q'){
            free(H);
            return 0;
        }
    }
}