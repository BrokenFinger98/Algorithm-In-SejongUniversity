#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    struct node *lChild, *rChild, *parent;
    int k, h;
}node;
node *tree;
node *getNode(){
    node *p = (node*)malloc(sizeof(node));
    p->lChild = NULL;
    p->rChild = NULL;
    p->parent = NULL;
    p->h = 0;
    return p;
}
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
node *sibling(node *z){
    if(tree == z)
        return tree;
    if(z->parent->lChild == z)
        return z->parent->rChild;
    else
        return z->parent->lChild;
}
int updateHeight(node* w) {
    int h = w->lChild->h > w->rChild->h ? w->lChild->h + 1 : w->rChild->h + 1;
    if(h != w->h){
        w->h = h;
        return 1;
    }
    return 0;
}
int isBalanced(node* w) {
    return abs(w->lChild->h - w->rChild->h) < 2;
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
void expandExternal(node *w){
    node *l = getNode();
    node *r = getNode();

    l->parent = w;
    r->parent = w;

    w->lChild = l;
    w->rChild = r;
    w->h = 1;
}
node *inOrderSucc(node *w){
    w = w->rChild;
    if(isExternal(w))
        return NULL;
    while (isInternal(w->lChild))
        w = w->lChild;
    return w;
}
node* restructure(node* x, node* y, node* z) {
    node *a, *b, *c;
    node *t0, *t1, *t2, *t3;
    if(z->k < y->k  &&  y->k < x->k){
        a = z; b = y; c = x;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = c->lChild;
        t3 = c->rChild;
    }else if(x->k < y->k  &&  y->k < z->k){
        a = x; b = y; c = z;
        t0 = a->lChild;
        t1 = a->rChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }else if(z->k < x->k  &&  x->k < y->k){
        a = z; b = x; c = y;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }else{
        a = y; b = x; c = z;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }

    if(z == tree){
        tree = b;
        b->parent = NULL;
    }else if(z->parent->lChild == z){
        z->parent->lChild = b;
        b->parent = z->parent;
    }else{
        z->parent->rChild = b;
        b->parent = z->parent;
    }

    a->lChild = t0;
    a->rChild = t1;
    t0->parent = a;
    t1->parent = a;
    updateHeight(a);

    c->lChild = t2;
    c->rChild = t3;
    t2->parent = c;
    t3->parent = c;
    updateHeight(c);

    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

    return b;
}
void searchAndFixAfterInsertion(node* w) {
    node *x, *y, *z;

    if(w == tree)
        return;
    z = w->parent;
    while (updateHeight(z) && isBalanced(z)){
        if(z == tree)
            return;
        z = z->parent;
    }
    if(isBalanced(z))
        return;
    if(z->lChild->h > z->rChild->h)
        y = z->lChild;
    else
        y = z->rChild;
    if(y->lChild->h > y->rChild->h)
        x = y->lChild;
    else
        x = y->rChild;
    restructure(x, y, z);
}
void insertItem(int k){
    node *w = treeSearch(tree, k);
    if(isInternal(w))
        return;
    else{
        w->k = k;
        expandExternal(w);
        searchAndFixAfterInsertion(w);
    }
}
node *reduceExternal(node *z){
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
    return zs;
}
void searchAndFixAfterRemoval(node *z){
    node *y, *x, *b;
    while (updateHeight(z) && isBalanced(z)){
        if(z == tree)
            return;
        z = z->parent;
    }
    if(isBalanced(z))
        return;
    
    if(z->lChild->h > z->rChild->h)
        y = z->lChild;
    else
        y = z->rChild;
    if(y->lChild->h > y->rChild->h)
        x = y->lChild;
    else if(y->lChild->h < y->rChild->h)
        x = y->rChild;
    else{
        if(z->lChild == y)
            x = y->lChild;
        else if(z->rChild == y)
            x = y->rChild;
    }
    b = restructure(x, y, z);
    if(b == tree)
        return;
    searchAndFixAfterRemoval(b->parent);
}
void removeElement(int k){
    node *w = treeSearch(tree, k);
    node *zs, *y;
    if(isExternal(w)){
        printf("X\n");
        return;
    }
    node *z = w->lChild;
    if(!isExternal(z))
        z = w->rChild;
    if(isExternal(z))
        zs = reduceExternal(z);
    else{
        y = inOrderSucc(w);
        z = y->lChild;
        w->k = y->k;
        zs = reduceExternal(z);
    }
    searchAndFixAfterInsertion(zs->parent);
    printf("%d\n", k);        
}
void findElement(int k){
    node *w = treeSearch(tree, k);
    if(isInternal(w))
        printf("%d\n", w->k);
    else
        printf("X\n");
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