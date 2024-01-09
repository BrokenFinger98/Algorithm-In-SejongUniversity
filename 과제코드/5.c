#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Vertex {
    char e;
    int d;
    int count;
    struct Vertex *left, *right;
}Vertex;
typedef struct Incidence {
    struct Incidence *down, *next;
}Incidence;
typedef struct Edge {
    int w;
    struct Edge *left, *right;
    struct Edge *next;
}Edge;
typedef struct Queue {
    Vertex *v;
    struct Queue *next, *prev;
}Queue;
Queue *Q = NULL, *rear = NULL;
Vertex *head = NULL;
Edge *header = NULL;
int isEmpty(Queue *q) {
    if (q->next == NULL) 
        return 1;
    else
        return 0;
}
Vertex *opposite(Vertex *u, Incidence *e) {
    Edge *e1 = e->down;
    if (e1->left == u) 
        return e1->right;
    else 
        return e1->left;
}
void makeVertex(char E) {
    Vertex *newNode = NULL;
    newNode = (Vertex *)malloc(sizeof(Vertex));
    newNode->e = E;
    newNode->left = NULL;
    newNode->right = NULL;
    Vertex *tmp = head;
    if (head == NULL) 
        head = newNode;
    else {
        while (tmp->right != NULL) 
            tmp = tmp->right;
        tmp->right = newNode;
    }
}
void makeEdges(char leftN, char rightN, int weight) {
    Edge *newNode;
    newNode = (Edge *)malloc(sizeof(Edge));
    newNode->w = weight; 
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL; 
    if (header == NULL) 
        header = newNode;
    else {
        Edge *t = header;
        while (t->next != NULL) 
            t = t->next;
        t->next = newNode;
    } 
    Vertex *p = head; 
    while (p != NULL) {
        if (p->e == leftN) {
            Incidence *newLine = (Incidence *)malloc(sizeof(Incidence));
            newNode->left = p;
            newLine->down = NULL;
            newLine->next = NULL;
            int cnt = 0;

            if (p->left == NULL) 
                p->left = newLine;
            else {
                Incidence *tmp = p->left;
                while (tmp != NULL) {
                    Edge *sequence = tmp->down;
                    Vertex *AnswerF = sequence->left;
                    Vertex *AnswerS = sequence->right;
                    if (AnswerF->e == leftN) {
                        char correct = AnswerS->e; 
                        if (correct > rightN) {
                            if (tmp == p->left) { 
                                newLine->next = p->left;
                                p->left = newLine;
                                break;
                            }else {
                                Incidence *past = p->left;
                                while (1) {
                                    if (past->next == tmp) 
                                        break;
                                    past = past->next;
                                }
                                newLine->next = tmp;
                                past->next = newLine;
                                break;
                            } 
                            cnt++; 
                        }
                    }else if (AnswerS->e == leftN) {
                        char correct = AnswerF->e; 
                        if (correct > rightN) {
                            if (tmp == p->left) { 
                                newLine->next = p->left;
                                p->left = newLine;
                                break;
                            }else {
                                Incidence *past = p->left;
                                while (1) {
                                    if (past->next == tmp)
                                        break;
                                    past = past->next;
                                }
                                newLine->next = tmp;
                                past->next = newLine;
                                break;
                            } 
                            cnt++; 
                        }
                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newLine;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newLine->down = newNode;
        } else if (p->e == rightN) {
            Incidence *newLine = (Incidence *)malloc(sizeof(Incidence)); 
            newNode->right = p;
            newLine->down = NULL;
            newLine->next = NULL;
            int cnt = 0;
            if (p->left == NULL) 
                p->left = newLine; 
            else { 
                Incidence *tmp = p->left; 
                while (tmp != NULL) {
                    Edge *sequence = tmp->down;
                    Vertex *AnswerF = sequence->left;
                    Vertex *AnswerS = sequence->right;
                    if (AnswerF->e == rightN) {
                        char correct = AnswerS->e; 
                        if (correct > leftN) {
                            if (tmp == p->left) { 
                                newLine->next = p->left;
                                p->left = newLine;
                                break;
                            }else {
                                Incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) 
                                        break;
                                    past = past->next;
                                }
                                newLine->next = tmp;
                                past->next = newLine;
                                break;
                            } 
                            cnt++;
                        }
                    }else if (AnswerS->e == rightN) {
                        char correct = AnswerF->e; 
                        if (correct > leftN) { 
                            if (tmp == p->left) { 
                                newLine->next = p->left;
                                p->left = newLine;
                                break;
                            }else {
                                Incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp)
                                        break;
                                    past = past->next;
                                }
                                newLine->next = tmp;
                                past->next = newLine;
                                break;
                            }
                            cnt++;
                        }
                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newLine;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newLine->down = newNode;
        }
        p = p->right;
    }
}
void enQueue(Vertex *e) {
    Queue *newNode = (Queue *)malloc(sizeof(Queue));
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->v = e;
    newNode->next = Q->next;
    if (rear == NULL) {
        Q->next = newNode;
        newNode->prev = Q;
        rear = newNode;
    }
    else {
        Q->next->prev = newNode;
        newNode->prev = Q;
        Q->next = newNode;
    }
}
Vertex *removeMin() {
    Queue *q = Q->next;
    int min = 10000000; 
    Vertex *tmp = NULL;
    Queue *temp = NULL;
    while (q != NULL) {
        Vertex *v1 = q->v;
        if (min > v1->d) {
            tmp = v1;
            min = v1->d;
            temp = q;
        }
        q = q->next;
    }
    Queue *p = Q;
    while (p != NULL) {
        if (p->next == temp) {
            if (temp->next == NULL) 
                p->next = NULL;
            else {
                p->next = p->next->next;
                p->next->prev = p;
            }
            Vertex *t = temp->v;
            free(temp);
            break;
        }
        p = p->next;
    }
    return tmp;
}
void DijkstraShortestPathsSSSTC(int n, char search, char target) { // 의사코드와 동일하게 작성
    Vertex *p = head;
    while (p != NULL) {
        p->d = 30000;
        p->count = 0; 
        p = p->right;
    }
    Vertex *s = head;
    while (s != NULL) {
        if (s->e == search)
            break;
        s = s->right;
    }
    Vertex *start = s;
    s->d = 0;

    Q = (Queue *)malloc(sizeof(Queue));
    Q->next = NULL; Q->prev = NULL;
    Q->v = NULL;
    s = head;
    for (int i = 0; i < n; i++) {
        enQueue(s);
        s = s->right;
    }
    while (!isEmpty(Q)) {
        Vertex *u = removeMin();
        Incidence *e = u->left;
        while (e != NULL) {
            Vertex *z = opposite(u, e);
            Edge *tmp = e->down;
            Queue *q = Q->next;
            int cnt = 0;
            while (q != NULL) { 
                Vertex *tt = q->v;
                if (tt->e == z->e) 
                    cnt++;
                q = q->next;
            }
            if (u == start) 
                z->count++; 
            if (cnt == 1 && tmp->w + u->d < z->d)
                z->d = tmp->w + u->d;
            if (tmp->w + u->d == z->d) 
                z->count += u->count; 
            e = e->next;
        }
    }
    Vertex *t = head;
    while (t != NULL) {
        if (t->e == target)
            printf("%c, %c : 최단거리 =  %d, 최단경로 수 = %d\n", search, target, t->d, t->count);
        t = t->right;
    }
    Queue *L = Q; 
    while (L != NULL) {
        Queue* tmp = L;
        L = L->next;
        free(tmp);
    }
    Q = NULL;
    rear = NULL;
}
int main() {
    int n = 6, m = 9;
    for (char i = 'A'; i <= 'F'; i++) 
        makeVertex(i);
    makeEdges('A', 'B', 8);
    makeEdges('A', 'C', 1);
    makeEdges('A', 'D', 4);
    makeEdges('B', 'C', 7);
    makeEdges('B', 'E', 4);
    makeEdges('C', 'D', 5);
    makeEdges('C', 'E', 3);
    makeEdges('C', 'F', 9);
    makeEdges('D', 'F', 4);
    DijkstraShortestPathsSSSTC(n, 'C', 'A');
    DijkstraShortestPathsSSSTC(n, 'C', 'F');
    DijkstraShortestPathsSSSTC(n, 'F', 'C');
    DijkstraShortestPathsSSSTC(n, 'B', 'D');
    Vertex *p = head;
    while (p != NULL) {
        Vertex *tmpV = p;
        p = p->right;
        Incidence *tmpI = tmpV->left;
        while (tmpI != NULL) {
            Incidence *tmpIi = tmpI;
            tmpI = tmpI->next;
            free(tmpIi);
        }
        free(tmpV);
    }
    Edge *q = header;
    while (p != NULL) {
        Edge *tmpE = q;
        q = q->right;
        free(tmpE);
    }
    return 0;
}