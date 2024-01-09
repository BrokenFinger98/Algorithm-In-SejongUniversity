#include <stdio.h>
#include <stdlib.h>
int M, n, q;
int *hashTable;
void initHashTable() {
    hashTable = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) 
        *(hashTable + i) = 0;
}
int h1(int x) {
    return x % M;
}
int h2(int x) {
    return q - (x % q);
}
int getNextIndex(int v, int i, int k) {
    return (v + i * h2(k)) % M;
}
void insertItem(int x) {
    int index;
    int v = h1(x);
    int i = 0;

    while (i < M) {
        index = getNextIndex(v, i, x);
        if (hashTable[index] == 0) {
            for (int j = 0; j < i; j++) 
                printf("C");
            hashTable[index] = x;
            printf("%d\n", index);
            return;
        } else 
            i++;
    }
}
void findElement(int x) {
    int v = h1(x);
    int index;
    int i = 0;

    while (i < M) {
        index = getNextIndex(v, i, x);
        if (hashTable[index] == 0) {
            printf("-1\n");
            return;
        } else if (hashTable[index] == x) {
            printf("%d %d\n", index, hashTable[index]);
            return;
        } else 
            i++;
    }
    printf("-1\n");
}
void printHashTable(){
    for (int i = 0; i < M; ++i)
        printf(" %d", hashTable[i]);
    printf("\n");
}
int main() {
    char cmd;
    int x, n;

    scanf("%d %d %d", &M, &n, &q);
    getchar();
    initHashTable();

    while (1) {
        scanf(" %c", &cmd); 
        if (cmd == 'i') {
            scanf("%d", &x);
            insertItem(x);
        } else if (cmd == 's') {
            scanf("%d", &x);
            findElement(x);
        } else if (cmd == 'p')
            printHashTable(); 
        else if (cmd == 'e') {
            printHashTable(); 
            free(hashTable);
            return 0;
        }
    }
}
