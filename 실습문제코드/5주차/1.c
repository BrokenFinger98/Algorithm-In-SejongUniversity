#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int elem;
    struct node *next;
}node;
int n, e;
node *getnode(int e);
node *addLast(node *p, int e); 
void writeList(node *p);
void mergeSort(node **L, int size);
node *merge(node *L1, node *L2);
void partition(node *L, node **L1, node **L2, int size);
void freeList(node *L);
int main(){
    node* L = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        scanf("%d", &e);
        L = addLast(L, e); 
    }
    mergeSort(&L, n);
    writeList(L);
    freeList(L);
    return 0;
}
node *getnode(int e){
    node *p = (node *)malloc(sizeof(node));
    p->elem = e;
    p->next = NULL;
    return p;
}
node *addLast(node *p, int e){
    if(p == NULL){
        return getnode(e); 
    }else{
        node* current = p;
        while(current->next != NULL)
            current = current->next;
        current->next = getnode(e);
        return p; 
    }
}
void writeList(node *p){
    while(p != NULL){
        printf(" %d", p->elem);
        p = p->next;
    }
    printf("\n");
}
void mergeSort(node **L, int size){
	node *L1, *L2, *p = *L;
	if(size <= 1)
		return;
	partition(p, &L1, &L2, size);
	if(size % 2 == 0){
		mergeSort(&L1, size/2);
		mergeSort(&L2, size/2);
	}
	else{
		mergeSort(&L1, size/2);
		mergeSort(&L2, size/2+1);
	}
	*L = merge(L1, L2);
}
node *merge(node *L1, node *L2){
	node* p = NULL;
	if(L1 == NULL)
		return L2;
	else if(L2 == NULL)
		return L1;
	if(L1->elem < L2->elem){
		p = L1;
		p->next = merge(L1->next, L2);
	}
	else{
		p = L2;
		p->next = merge(L1, L2->next);
	}
	return p;
}
void partition(node *L, node **L1, node **L2, int size){
	node *p = L;
	*L1 = L;
	for(int i = 0; i < size/2 - 1; i++)
		p = p->next;
	*L2 = p->next;
	p->next = NULL;
}
void freeList(node *L){
	node *p = L;
	while(p != NULL){
		L = L->next;
		free(p);
		p = L;
	}
}

