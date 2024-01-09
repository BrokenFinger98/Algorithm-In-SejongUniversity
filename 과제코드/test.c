#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct vertices {
    char e;
    int d;
    int count; //                         ִ                 
    struct vertices* left, * right;
}vertices;

typedef struct incidence {
    struct incidence* down, * next;
}incidence;

typedef struct edges {
    int w;
    struct edges* left, * right;
    struct edges* next;
}edges;

typedef struct queue {
    vertices* v;
    struct queue* next, * prev;
}queue;

queue* Q = NULL, * rear = NULL;
vertices* head = NULL;
edges* header = NULL;

void makeVertex(char ee) {
    vertices* newnode = NULL;
    newnode = (vertices*)malloc(sizeof(vertices));
    newnode->e = ee;
    newnode->left = NULL;
    newnode->right = NULL;

    vertices* p = head;

    if (head == NULL) {
        head = newnode;
    }
    else {
        while (p->right != NULL) {
            p = p->right;
        }
        p->right = newnode;
    }

}

void makeEdges(char leftn, char rightn, int weight) {
    edges* newnode;
    newnode = (edges*)malloc(sizeof(edges));
    newnode->w = weight; // add weight
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->next = NULL; //       ʱ ȭ

    if (header == NULL) {
        header = newnode;
    }
    else {
        edges* t = header;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = newnode;
    } //                  Ʈ       

    vertices* p = head; // p         
    while (p != NULL) {



        if (p->e == leftn) {
            incidence* newline = (incidence*)malloc(sizeof(incidence));
            newnode->left = p;

            newline->down = NULL;
            newline->next = NULL;
            int cnt = 0;
            //                  
            if (p->left == NULL) { // p    ƹ           ϾȵǾ        
                p->left = newline; //                      ̰ 
            }
            else { //  ƴ϶                            ־  ش 
                incidence* tmp = p->left; // tmp           
                while (tmp != NULL) {
                    edges* sequence = tmp->down;
                    //  ̹                            ޸                  ˾ƺ   
                    vertices* fAnswer = sequence->left;
                    vertices* sAnswer = sequence->right;
                    if (fAnswer->e == leftn) {
                        char correct = sAnswer->e; //     ã  
                        if (correct > rightn) {
                            //           Ϸ                         ã              
                            //    ũ      ʿ   ٿ     ϹǷ               ٿ  ش 
                            if (tmp == p->left) { //  ̰    ù             տ        Ѵٸ 
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } //  ƴ϶      ̿     ش 
                            cnt++; //        ƴٸ   ÷  ش 
                        }

                    }
                    else if (sAnswer->e == leftn) {
                        char correct = fAnswer->e; //     ã  
                        if (correct > rightn) {
                            //           Ϸ                         ã              
                            //    ũ      ʿ   ٿ     ϹǷ               ٿ  ش 
                            if (tmp == p->left) { //  ̰    ù             տ        Ѵٸ 
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } //  ƴ϶      ̿     ش 
                            cnt++; //        ƴٸ   ÷  ش 
                        }

                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newline;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newline->down = newnode; //                                 δ 
        }




        else if (p->e == rightn) {
            incidence* newline = (incidence*)malloc(sizeof(incidence)); //       
            newnode->right = p;
            //                    

            newline->down = NULL;
            newline->next = NULL;
            int cnt = 0;
            //                    
            if (p->left == NULL) { // p    ƹ           ϾȵǾ        
                p->left = newline; //                      ̰ 
            }
            else { //  ƴ϶                            ־  ش 
                incidence* tmp = p->left; // tmp           
                while (tmp != NULL) {
                    edges* sequence = tmp->down;
                    //  ̹                            ޸                  ˾ƺ   
                    vertices* fAnswer = sequence->left;
                    vertices* sAnswer = sequence->right;
                    if (fAnswer->e == rightn) {
                        char correct = sAnswer->e; //     ã  
                        if (correct > leftn) {
                            //           Ϸ                         ã              
                            //    ũ      ʿ   ٿ     ϹǷ               ٿ  ش 
                            if (tmp == p->left) { //  ̰    ù             տ        Ѵٸ 
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } //  ƴ϶      ̿     ش 
                            cnt++; //        ƴٸ   ÷  ش 
                        }
                    }
                    else if (sAnswer->e == rightn) {
                        char correct = fAnswer->e; //     ã  
                        if (correct > leftn) {
                            //           Ϸ                         ã              
                            //    ũ      ʿ   ٿ     ϹǷ               ٿ  ش 
                            if (tmp == p->left) { //  ̰    ù             տ        Ѵٸ 
                                newline->next = p->left;
                                p->left = newline;
                                break;
                            }
                            else {
                                incidence* past = p->left;
                                while (1) {
                                    if (past->next == tmp) {
                                        break;
                                    }
                                    past = past->next;
                                }
                                newline->next = tmp;
                                past->next = newline;
                                break;
                            } //  ƴ϶      ̿     ش 
                            cnt++; //        ƴٸ   ÷  ش 
                        }
                    }
                    if (tmp->next == NULL && cnt == 0) {
                        tmp->next = newline;
                        break;
                    }
                    tmp = tmp->next;
                }
            }
            newline->down = newnode; //                                 δ 
        }




        p = p->right;
    }
}

void enqueue(vertices* e) {
    queue* newnode = (queue*)malloc(sizeof(queue));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->v = e;
    newnode->next = Q->next;
    if (rear == NULL) {
        Q->next = newnode;
        newnode->prev = Q;
        rear = newnode;
    }
    else {
        Q->next->prev = newnode;
        newnode->prev = Q;
        Q->next = newnode;
    }
}

int isEmpty(queue* q) {
    if (q->next == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

vertices* opposite(vertices* u, incidence* e) {
    edges* e1 = e->down;
    if (e1->left == u) {
        return e1->right;
    }
    else {
        return e1->left;
    }
}

vertices* removeMin() {
    queue* q = Q->next;
    int min = 10000000; //  ּҸ     Ѵ 
    vertices* tmp = NULL;
    queue* temp = NULL;
    while (q != NULL) {
        vertices* v1 = q->v;
        if (min > v1->d) { //  ּҶ        صα 
            tmp = v1;
            min = v1->d;
            temp = q;
        }
        q = q->next;
    }
    queue* p = Q;
    while (p != NULL) { //  ּ  ΰ  ť         
        if (p->next == temp) {
            if (temp->next == NULL) {
                p->next = NULL;
            }
            else {
                p->next = p->next->next;
                p->next->prev = p;
            }
            vertices* t = temp->v;
            free(temp); // ť  Ҵ     
            break;
        }
        p = p->next;
    }

    return tmp;
}

void DijkstraShortestPathsSSSTC(int n, char search, char target) { //  ǻ  ڵ        ϰ   ۼ 
    vertices* p = head;
    while (p != NULL) { //1
        p->d = 30000;
        p->count = 0; //           ʱ ȭ
        p = p->right;
    }
    vertices* s = head;
    while (s != NULL) {
        if (s->e == search) {
            break;
        }
        s = s->right;
    }
    vertices* start = s; // oigin     
    s->d = 0; //2

    Q = (queue*)malloc(sizeof(queue)); //3 ť  ʱ ȭ
    Q->next = NULL; Q->prev = NULL;
    Q->v = NULL;
    s = head;
    for (int i = 0; i < n; i++) {
        enqueue(s);
        s = s->right;
    }
    while (!isEmpty(Q)) { // 4
        vertices* u = removeMin();
        incidence* e = u->left;
        while (e != NULL) {
            vertices* z = opposite(u, e);
            edges* tmp = e->down;
            queue* q = Q->next;
            int cnt = 0;
            while (q != NULL) { //      ť         Ѵٸ  cnt++
                vertices* tt = q->v;
                if (tt->e == z->e) {
                    cnt++;
                }
                q = q->next;
            }
            if (u == start) { //         ŵ       search   
                z->count++; //  ׿   ش  ϴ                        1          ش 
            }
            if (cnt == 1 && tmp->w + u->d < z->d) { //  ǻ  ڵ       
                z->d = tmp->w + u->d; //     ִܰ θ          
            }
            if (tmp->w + u->d == z->d) {
                z->count += u->count; //  ִ   Ÿ             
            } //                              ش .
            e = e->next;
        }
    }
    vertices* t = head;
    while (t != NULL) {
        if (t->e == target)
            printf("%c, %c :  ִܰŸ  =  %d,  ִܰ      = %d\n", search, target, t->d, t->count);
        t = t->right;
    }
    queue* L = Q; // ť  ʱ ȭ
    while (L != NULL) {
        queue* tmp = L;
        L = L->next;
        free(tmp);
    }
    Q = NULL;
    rear = NULL;
}

int main() {
    int n = 6, m = 9;
    for (char i = 'A'; i <= 'F'; i++) {
        makeVertex(i);
    }

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
    vertices* p = head; //     ,     ,                  
    while (p != NULL) {
        vertices* tmpv = p;
        p = p->right;
        incidence* tmpi = tmpv->left;
        while (tmpi != NULL) {
            incidence* tmpii = tmpi;
            tmpi = tmpi->next;
            free(tmpii);
        }
        free(tmpv);
    }
    
    edges* q = header;
    while (p != NULL) {
        edges* tmpe = q;
        q = q->right;
        free(tmpe);
    }

    return 0;
}