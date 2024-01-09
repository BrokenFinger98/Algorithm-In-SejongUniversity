#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    struct node* parent, * lChild, * rChild;
    int k, h;
}node;
int isExternal(node *w){
    if(w->lChild == NULL && w->rChild == NULL)
        return 1;
    else
        return 0;
}
node* getNode(){
    return (node*)calloc(1, sizeof(node));
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
int findElement(node *root, int k){
    node *w = treeSearch(root, k);
    if(k == w->k)
        return k;
    else
        return 0;
}
void expandExternal(node* w){
    w->rChild = getNode();
    w->rChild->parent = w;
    w->lChild = getNode();
    w->lChild->parent = w;
}
int isBalanced(node* w) {
    return abs(w->lChild->h - w->rChild->h) < 2;
}
int updateHeight(node* w) {
    int h = w->lChild->h > w->rChild->h ? w->lChild->h + 1 : w->rChild->h + 1;
    if(h != w->h){
        w->h = h;
        return 1;
    }
    return 0;
}
node *sibling(node* v){
    if (v == v->parent->lChild) 
        return v->parent->rChild;
    else if (v == v->parent->rChild)
        return v->parent->lChild;
}
node* restructure(node* x, node* y, node* z, node** root){
    node* a = NULL, * b = NULL, * c = NULL;
    node* t0 = NULL, * t1 = NULL, * t2 = NULL, * t3 = NULL;

    if (z->k < y->k && y->k < x->k){
        a = z; b = y; c = x;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = c->lChild;
        t3 = c->rChild;
    }else if (x->k < y->k && y->k < z->k){
        a = x; b = y; c = z;
        t0 = a->lChild;
        t1 = a->rChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }else if (z->k < x->k && x->k < y->k){
        a = z; b = x; c = y;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }else if (y->k < x->k && x->k < z->k){
        a = y; b = x; c = z;
        t0 = a->lChild;
        t1 = b->lChild;
        t2 = b->rChild;
        t3 = c->rChild;
    }

    if (*root == z){
        *root = b;
        b->parent = NULL;
    }else if (z == z->parent->lChild){
        z->parent->lChild = b;
        b->parent = z->parent;
    }else if (z == z->parent->rChild){
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
void searchAndFixAfterInsertion(node* v, node** root){
    v->h = 1;
    v->lChild->h = 0;
    v->rChild->h = 0;
    if (v == *root)
        return;
    node* z = v->parent, * y = NULL, * x = NULL;
    while (updateHeight(z) && isBalanced(z)){
        if (z == *root) 
            return;
        z = z->parent;
    }
    if (isBalanced(z)) 
        return;
    if (z->lChild->h > z->rChild->h)
        y = z->lChild;
    else
        y = z->rChild;
    if (y->lChild->h > y->rChild->h)
        x = y->lChild;
    else
        x = y->rChild;
    restructure(x, y, z, root);
}
void insertItem(node** v, int k){
    node* w = treeSearch(*v, k);
    if (isExternal(w)){
        w->k = k;
        expandExternal(w);
        searchAndFixAfterInsertion(w, v);
    }
}
node* inOrderSucc(node* v){
    node* w = v->rChild;
    while (!isExternal(w->lChild)) 
            w = w->lChild;
    return w;
}
void reduceExternal(node* v, node** root){
    node *vs = sibling(v);
    node *vp = v->parent;

    if (vp == *root)
        *root = vs;
    else{
        node* g = vp->parent;
        vs->parent = g;
        if (vp == g->lChild)
            g->lChild = vs;
        else 
            g->rChild = vs;
    }
    free(v);
    free(vp);
}
void searchAndFixAfterRemoval(node* z, node** root){
    node* y = NULL, * x = NULL, * b = NULL;
    while (updateHeight(z) && isBalanced(z)){
        if (z == *root) 
            return;
        z = z->parent;
    }
    if (isBalanced(z)) 
        return;
    if (z->lChild->h > z->rChild->h)
        y = z->lChild;
    else
        y = z->rChild;
    if (y->lChild->h > y->rChild->h)
        x = y->lChild;
    else if (y->lChild->h < y->rChild->h)
        x = y->rChild;
    else{
        if (z->lChild == y) 
            x = y->lChild;
        else if (z->rChild == y) 
            x = y->rChild;
    }
    b = restructure(x, y, z, root);
    if (*root == b) 
        return;
    searchAndFixAfterRemoval(b->parent, root);
}
int removeElement(node** v, int k){
    node* w = treeSearch(*v, k);
    if (isExternal(w)) 
        return -1;
    int e = w->k;
    node* z = NULL;
    if (w == *v) 
        z = w;
    node* x = w->lChild;
    if (!isExternal(x)) 
        x = w->rChild;
    if (isExternal(x)){
        z = w->parent;
        reduceExternal(x, v);
    }else{
        node* y = inOrderSucc(w);
        w->k = y->k;
        z = y->parent;
        reduceExternal(y->lChild, v);
    }
    searchAndFixAfterRemoval(z, v);
    return e;  
}
int main(){
    node *root = getNode();
    char order; 
    int k;

    while (1){
        scanf("%c", &order);
        switch (order){
        case 'i':
            scanf("%d", &k);
            getchar();
            insertItem(&root, k);
            break;
        case 'd':
            scanf("%d", &k);
            getchar();
            if(k == removeElement(&root, k))
                printf("%d\n", k);
            else
                printf("X\n");
            break;
        case 's':
            scanf("%d", &k);
            getchar();
            if(k == findElement(root, k))
                printf("%d\n", k);
            else
                printf("X\n");
            break;
        case 'p':
            preOrder(root);
            printf("\n");
            break;
        case 'q':
            freeNode(root);
            return 0;
        default:
            break;
        }
    }
}
