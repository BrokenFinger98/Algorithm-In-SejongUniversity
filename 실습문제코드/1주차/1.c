#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char elem;
    struct node *prev;
    struct node *next;
}node;

typedef struct list{
    int n;
    node *header;
    node *trailer;
}list;

node *getnode();
list *initlist();
void add(list *list, int r, char e);
void delete(list *list, int r);
void print(list *list);
char get(list *list, int r);
void invalidRankException();

int main(){
    list *list = initlist();
    int N, i, r;
    char ch, e, c;

    scanf("%d", &N);
    getchar();
    for(i = 0; i < N; ++i){
        scanf("%c", &ch);
        if(ch == 'A'){
            scanf("%d %c", &r, &e);
            add(list,r,e);
            getchar();
        }
        else if(ch == 'D'){
            scanf("%d", &r);
            delete(list,r);
            getchar();
        }
        else if(ch == 'G'){
            scanf("%d", &r);
            c = get(list, r);
            if(c != '\0')
                printf("%c\n", c);
            getchar();
        }
        else if(ch == 'P'){
            print(list);
            getchar();
        }
    }
    printf("\n");
    node *p = list->header;
    node *q;
    while (p){
        q = p->next;
        free(p);
        p = q;
    }
    free(list);
    return 0;
}

list *initlist(){
    list *p = (list *)malloc(sizeof(list));

    node *header = getnode();
    node *trailer = getnode();
    p->n = 0;
    header->next = trailer;
    trailer->prev = header;
    p->header = header;
    p->trailer = trailer;
    header->prev = NULL;
    trailer->next = NULL;

    return p;
}

node *getnode(){
    node *p = (node *)malloc(sizeof(node));

    p->elem = '\0';
    p->next = NULL;
    p->prev = NULL;

    return p;
}

void add(list *list, int r, char e){
    node *p = list->header;
    node *q = getnode();
    int i;
    ++list->n;

    if((r<1) || (r>list->n)){
        invalidRankException();
        --list->n;
    }
    else{
        for(i = 0; i < r; ++i)
            p = p->next;
        
        q->elem = e;
        q->prev = p->prev;
        q->next = p;
        p->prev->next = q;
        p->prev = q;
    }
}

void delete(list *list, int r){
    node *p = list->header;
    int n = 0, i = 0;
    char ch;
    
    if((r<1) || (r>list->n))
        invalidRankException();
    else{
        for(i=0;i<r;++i)
            p = p->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        --list->n;
    }
}

void print(list *list){
    node *p = list->header;
    int i;

    for(i=0;i<list->n;++i){
        p = p->next;
        printf("%c", p->elem);
    }
    printf("\n");
}

char get(list *list, int r){
    node *p = list->header;
    int i;
    char ch;

    if((r<1) || (r>list->n)){
        invalidRankException();
        return '\0';
    }
    else{
        for(i=0;i<r;++i)
            p = p->next;
        ch = p->elem;
        return ch;
    }
}

void invalidRankException(){
    printf("invalid position\n");
}
