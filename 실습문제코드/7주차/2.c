#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    struct node *lChild, *rChild, *parent;
    int k, h;
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
    node *l = getNode();
    node *r = getNode();

    l->parent = w;
    r->parent = w;

    w->lChild = l;
    w->rChild = r;
    w->h = 1;
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
int updateHeight(node* w) {
    if (w == NULL)
        return 0;
    int leftHeight = (w->lChild != NULL) ? w->lChild->h : 0;
    int rightHeight = (w->rChild != NULL) ? w->rChild->h : 0;
    w->h = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    return w->h;
}
int isBalanced(node* w) {
    int leftHeight = (w->lChild != NULL) ? w->lChild->h : 0;
    int rightHeight = (w->rChild != NULL) ? w->rChild->h : 0;
    return abs(leftHeight - rightHeight) <= 1;
}
node* restructure(node* x, node* y, node* z) {
    node *a, *b, *c;
    node *t0, *t1, *t2, *t3;
    if(z->k < y->k  && z->k < x->k && y->k < x->k){
        a = z; b = y; c = x;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = c->lChild;
        t3 = c->rChild;
    }else if(x->k < y->k  && x->k < z->k && y->k < z->k){
        a = x; b = y; c = z;
        t0 = a->lChild;
        t1 = a->rChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }else if(z->k < y->k  && z->k < x->k && x->k < y->k){
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

    if(!z->parent){
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
    w->lChild->h = 0;
    w->rChild->h = 0;
    w->h = 1;
    if(!w->parent)
        return;
    z = w->parent;
    while (updateHeight(z) && isBalanced(z)){
        if(!z->parent)
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
    w->k = k;
    expandExternal(w);
    searchAndFixAfterInsertion(w);
}
void findElement(int k){
    node *w = treeSearch(tree, k);
    if(isInternal(w))
        printf("%d\n", k);
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