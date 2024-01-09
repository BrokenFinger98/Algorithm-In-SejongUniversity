#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    struct node *lChild, *rChild, *parent;
    int k;
}node;
node *tree;
int isExternal(node *w){
    if(w->lChild == NULL && w->rChild == NULL)
        return 1;
    else
        return 0;
}
int isInternal(node *w){
    if(w->lChild != NULL || w->rChild != NULL)
        return 1;
    else
        return 0;
}
node *getNode(){
    node *p = (node*)malloc(sizeof(node));
    p->lChild = NULL;
    p->rChild = NULL;
    p->parent = NULL;
    return p;
}
void expandExternal(node *w){
    w->lChild = getNode();
    w->rChild = getNode();
    w->lChild->parent = w;
    w->rChild->parent = w;
}
node *treeSearch(node *v, int k){
    if(isExternal(v))
        return v;
    if(k == v->k)
        return v;
    else if(k < v->k)
        return treeSearch(v->lChild, k);
    else
        return treeSearch(v->rChild, k);
}
void insertItem(int k){
    node *w = treeSearch(tree, k);
    if(isInternal(w))
        return;
    else{
        w->k = k;
        expandExternal(w);
        return;
    }
}
void findElement(int k){
    node *w = treeSearch(tree, k);
    if(isInternal(w))
        printf("%d\n", k);
    else
        printf("X\n");
}
node *sibling(node *z){
    if(tree == z)
        return tree;
    if(z->parent->lChild == z)
        return z->parent->rChild;
    else
        return z->parent->lChild;
}
node *inOrderSucc(node *w){
    node *y = w->rChild;
    if(isExternal(y))
        return y;
    while (isInternal(y->lChild)){
        y = y->lChild;
    }
    return y;
}
void reduceExternal(node *z){
    node *w = z->parent;
    node *zs = sibling(z);
    node *g;

    if(w == tree){
        tree = zs;
        zs->parent = NULL;
    }else{
        g = w->parent;
        zs->parent = g;
        if(w == g->lChild)
            g->lChild = zs;
        else
            g->rChild = zs;
    }
    free(z);
    free(w);
}
void removeElement(int k){
    node *w = treeSearch(tree, k);
    if(isExternal(w)){
        printf("X\n");
        return;
    }

    node *z = w->lChild;
    if(!isExternal(z))
        z = w->rChild;
    if(isExternal(z))
        reduceExternal(z);
    else{
        node *y = inOrderSucc(w);
        z = y->lChild;
        w->k = y->k;
        reduceExternal(z);
    }
    printf("%d\n", k);
}
void preOrder(node* p){
    if (isExternal(p))
        return;
    else{
        printf(" %d", p->k);
        preOrder(p->lChild);
        preOrder(p->rChild);
    }
}
void freeNode(node *p){
    if(isExternal(p))
        return;
    else{
        freeNode(p->lChild);
        freeNode(p->rChild);
        free(p);
    }
}
int main(){
    tree = getNode();
    char order; 
    int k;

    while (1){
        scanf("%c", &order);
        switch (order){
        case 'i':
            scanf("%d", &k);
            getchar();
            insertItem(k);
            break;
        case 'd':
            scanf("%d", &k);
            getchar();
            removeElement(k);
            break;
        case 's':
            scanf("%d", &k);
            getchar();
            findElement(k);
            break;
        case 'p':
            preOrder(tree);
            printf("\n");
            break;
        case 'q':
            freeNode(tree);
            return 0;
        default:
            break;
        }
    }
}