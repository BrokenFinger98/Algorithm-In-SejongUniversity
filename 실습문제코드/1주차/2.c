#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    struct node *left;
    struct node *right;
    int data;
}node;

typedef struct tree{
    node *root;
}tree;

node *getnode(int data){
    node *p = (node *)malloc(sizeof(node));
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

node *findNode(node *p, int data){
    if (p == NULL)
        return NULL;
    
    if (p->data == data)
        return p;

    node* leftResult = findNode(p->left, data);
    if (leftResult != NULL)
        return leftResult;

    node* rightResult = findNode(p->right, data);
    if (rightResult != NULL)
        return rightResult;

    return NULL;
}

void findPath(node *p, char *s){
    char tmp;
    int len = strlen(s);
    int i;
    
    printf(" %d", p->data);
    for(i = 0; i < len; ++i){
        tmp = s[i];
        if(tmp == 'R'){
            p = p->right;
            printf(" %d", p->data);
        }
        if(tmp == 'L'){
            p = p->left;
            printf(" %d", p->data);
        }
    }
    printf("\n");
}

void freeTree(node *p){
    if(p){
        freeTree(p->left);
        freeTree(p->right);
        free(p);
    }
}

int main(){
    int n, i, parent, leftchild, rightchild;
    char s[101];
    tree T;
    node *p;

    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        scanf("%d %d %d", &parent, &leftchild, &rightchild);
        if(i == 0){
            T.root = getnode(parent);
            T.root->left = getnode(leftchild);
            T.root->right = getnode(rightchild);
        }
        else{
            p = findNode(T.root, parent);
            if(leftchild != 0)
                p->left = getnode(leftchild);
            if(rightchild != 0)
                p->right = getnode(rightchild);
        }
    }

    scanf("%d", &n);
    for(i = 0; i < n; ++i){
        scanf("%s", s);
        getchar();
        findPath(T.root, s);
    }
    freeTree(T.root);
    return 0;
}

// 9↦ 노드 개수
// 5 3 9
// 3 8 15
// 8 0 2
// 2 0 0
// 15 0 0
// 9 7 10
// 7 12 0
// 12 0 0
// 10 0 0
// 3↦ 탐색 횟수
// RLL
// LL
// LR