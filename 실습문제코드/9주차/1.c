#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int x;
    struct node *next;
} node;

node *hashTable;
int M;

void initHashTable() {
    hashTable = (node *)malloc(M * sizeof(node));
    for (int i = 0; i < M; ++i)
        (hashTable + i)->next = NULL;
}

int h(int x) {
    return x % M;
}

int findElement(int x) {
    int v = h(x);
    node *p = (hashTable + v)->next;
    int ret = 0;
    while (p != NULL) {
        ++ret;
        if (p->x == x)
            return ret;
        p = p->next;
    }
    return 0;
}

void insertItem(int x) {
    int v = h(x);
    node *p = (node *)malloc(sizeof(node));
    p->x = x;
    p->next = (hashTable + v)->next;
    (hashTable + v)->next = p;
}

int removeElement(int x) {
    int v = h(x);
    node *p = (hashTable + v);
    node *q = p->next;
    int ret = 0;

    while (q != NULL) {
        ++ret;
        if (q->x == x) {
            p->next = q->next;
            free(q);
            return ret;
        }
        p = q;
        q = q->next;
    }
    return 0;
}

void printHashTable() {
    for (int i = 0; i < M; ++i) {
        node *p = (hashTable + i)->next;
        while (p != NULL) {
            printf(" %d", p->x);
            p = p->next;
        }
    }
    printf("\n");
}

void freeTable(int M) {
    for (int i = 0; i < M; ++i) {
        node *p = (hashTable + i)->next;
        while (p != NULL) {
            node *q = p;
            p = p->next;
            free(q);
        }
    }
    free(hashTable);
}

int main() {
    int x;
    char cmd;
    scanf("%d", &M);
    initHashTable();

    while (1) {
        scanf(" %c", &cmd); 
        if (cmd == 'i') {
            scanf("%d", &x);
            insertItem(x);
        } else if (cmd == 's') {
            scanf("%d", &x);
            printf("%d\n", findElement(x));
        } else if (cmd == 'd') {
            scanf("%d", &x);
            printf("%d\n", removeElement(x));
        } else if (cmd == 'p') {
            printHashTable();
        } else if (cmd == 'e') {
            freeTable(M);
            return 0;
        }
    }
    return 0;
}
