#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
    int name;
}vertex;
typedef struct edge {
    int w;
    int start, end;
}edge;
typedef struct graph {
    vertex *vertex;
    edge *Edge;
    int **matrix;
}graph;
graph *g;
int findNum(int a, int b) {
    for (int i = 0; i<21; ++i) {
        if (g->Edge[i].start == a && g->Edge[i].end == b) 
            return i;
    }
}
void initMatrix(int a, int b, int w) {
    int A, B, EN;
    if (a<b) {
        A = a;
        B = b;
    }else {
        A = b;
        B = a;
    }
    EN = findNum(A, B);
    g->Edge[EN].w = w;
    g->matrix[a - 1][b - 1] = EN;
    g->matrix[b - 1][a - 1] = EN;
}
void search(int n) {
    int EN;
    if (n>6 || n <= 0) {
        printf("-1");
        return;
    }
    for (int i = 0; i < 6; i++) {
        EN = g->matrix[n - 1][i];
        if (EN == -1) 
            continue;
        if (g->Edge[EN].start == n) 
            printf("%d %d ", g->Edge[EN].end, g->Edge[EN].w);
        else if (g->Edge[EN].end == n) 
            printf("%d %d ", g->Edge[EN].start, g->Edge[EN].w);
    }
}
void change(int a, int b, int w) {
    int EN, A, B;
    if ((a>6 || a <= 0) || (b>6 || b <= 0)) {
        printf("-1\n");
        return;
    }
    if (a<b) {
        A = a;
        B = b;
    }else {
        A = b;
        B = a;
    }
    EN = findNum(A, B);
    if (w == 0) {
        w = -1;
        g->matrix[a - 1][b - 1] = -1;
        g->matrix[b - 1][a - 1] = -1;
    }else {
        g->matrix[a - 1][b - 1] = EN;
        g->matrix[b - 1][a - 1] = EN;
    }
    g->Edge[EN].w = w;
}
void startMatrix(){
    int tmp = 0;
    g = (graph *)malloc(sizeof(graph));
    g->vertex = (vertex *)malloc(sizeof(vertex) * 6);
    g->Edge = (edge *)malloc(sizeof(edge) * 21);
    g->matrix = (int **)malloc(sizeof(int *) * 21); 

    for (int i = 0; i < 6; i++) {
        g->matrix[i] = (int *)malloc(sizeof(int) * 6);
        for (int j = 0; j < 6; j++) {
            g->matrix[i][j] = -1;
        }
    }
    for (int i = 0; i < 6; i++) 
        g->vertex[i].name = i + 1;
    for (int i = 0; i < 6; i++) {
        for (int j = i; j < 6; j++) {
            g->Edge[tmp].start = i + 1;
            g->Edge[tmp].end = j + 1;
            tmp++;
        }
    }
    initMatrix(1, 2, 1);
    initMatrix(1, 3, 1);
    initMatrix(1, 4, 1);
    initMatrix(1, 6, 2);
    initMatrix(2, 3, 1);
    initMatrix(3, 5, 4);
    initMatrix(5, 5, 4);
    initMatrix(5, 6, 3);
}
int main() {
    int a, b, w;
    char cmd;
    startMatrix();
    
    while (1) {
        scanf("%c", &cmd);
        if (cmd == 'a') {
            scanf("%d", &a);
            getchar();
            search(a);
            printf("\n");
        }
        else if (cmd == 'm') {
            scanf("%d %d %d", &a, &b, &w);
            getchar();
            change(a, b, w);
        }
        else if (cmd == 'q') {
            return 0;
        }
    }
}