#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Graph {
	int **adjacent;
}Graph;
Graph G;
int F = 0;
int R = 0;
int *Q;
int n, m, s;
void edge(int x, int y) {
	G.adjacent[x][y] = 1;
	G.adjacent[y][x] = 1;
}
void initGraph() {
	int x, y;
	scanf("%d %d %d", &n, &m, &s);

	G.adjacent = (int **)malloc(sizeof(int *)*(n+1));
	for (int i = 0; i <= n; i++) {
		G.adjacent[i] = (int *)malloc(sizeof(int)*(n+1));
		for (int j = 0; j < n + 1; j++)
			G.adjacent[i][j] = 0;
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		edge(x, y);
	}
}
void enqueue(int k) {
	R++;
	Q[R] = k;
}
int dequeue() {
	F++;
	return Q[F];
}
void BFS(int s) {
	int *v;

	Q = (int *)malloc(sizeof(int)*(n+1));
	v = (int *)malloc(sizeof(int)*(n+1));
	for (int i = 0; i < n + 1; i++)
		v[i] = 0;
	v[s] = 1;	
	printf("%d\n", s);
	enqueue(s);

	while (F != R) {		
		s = dequeue();
		for (int i = 1; i <= n; i++) {
			if (G.adjacent[s][i] == 1 && v[i] == 0) {	
				v[i] = 1; 
				printf("%d\n", i);
				enqueue(i);
			}
		}
	}
	free(Q);
	free(v);
}
int main() {
	initGraph();
	BFS(s);
	for (int i = 0; i <= n; i++)
		free(G.adjacent[i]);
	free(G.adjacent);
	return 0;
}