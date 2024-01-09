#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node {
	int index;
	struct Node *next;
}Node;
typedef struct Vertex {
	int id;
	int d;
	int p;
	Node *adjacent;
}Vertex;
typedef struct Edge {
	int start;
	int end;
	int weight;
}Edge;
typedef struct Graph {
	Vertex *vertices;
	Edge *edges;
}Graph;
typedef struct Queue {
	int size;
	int max;
	int *key;
	int *value;
}Queue;
Queue Q;
Graph G;
int n, m;
Node *getNode(int i) {
	Node *N = (Node *)malloc(sizeof(Node));
	N->index = i;
	N->next = NULL;
	return N;
}
void insert(int id, int a, int b) {
	Node *H = G.vertices[a].adjacent;
	Node *N;
	while (H->next)
		H = H->next;
	N = getNode(id);
	H->next = N;
}
void edgeMethod(int id, int a, int b, int w) {
	G.edges[id].start = a;
	G.edges[id].end = b;
	G.edges[id].weight = w;
	insert(id, a, b);
	if (a != b)
		insert(id, b, a);
}
void buildGraph() {
	int start, end, weight;
	scanf("%d %d", &n, &m);
	G.edges = (Edge *)malloc(sizeof(Edge) * m);
	G.vertices = (Vertex *)malloc(sizeof(Vertex) * (n + 1));

	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].adjacent = getNode(-1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &start, &end, &weight);
		edgeMethod(i, start, end, weight);
	}
}
int find(int a) {
	for (int i = 0; i < Q.max; i++) 
		if (Q.value[i] == a)
			return 1;
	return 0;
}
void initQueue(int size) {
	Q.max = size;
	Q.size = 0;
	Q.key = (int *)malloc(sizeof(int) * size);
	Q.value = (int *)malloc(sizeof(int) * size);
}
void enqueue(int key, int value) {
	int index;
	index = Q.size;
	Q.key[index] = key;
	Q.value[index] = value;
	Q.size += 1;
}
int isEmpty() {
	if (Q.size == 0)
		return 1;
	else
		return 0;
}
int dequeue() {
	int minOfK, minOfV, index;
	minOfK = Q.key[0];
	minOfV = Q.value[0];
	index = 0;

	for (int i = 1; i < Q.max; i++) {
		if (Q.key[i] < minOfK) {
			minOfK = Q.key[i];
			minOfV = Q.value[i];
			index = i;
		}
	}

	Q.key[index] = 999999;
	Q.value[index] = -1;
	Q.size -= 1;

	return minOfV;
}
int opposite(Node *e, int a) {
	Edge k = G.edges[e->index];
	if (k.start == a)
		return k.end;
	else
		return k.start;
}
void replaceKey(int a, int key) {
	for (int i = 0; i < Q.max; i++) 
		if (Q.value[i] == a)
			Q.key[i] = key;
}
void PrimJarnik(int start) {
    int u;
	Node* tmp;
	int res = 0;
	int z, e;

	for (int i = 1; i <= n; i++) {
		G.vertices[i].d = 999999;
		G.vertices[i].p = -1;
	}
	G.vertices[start].d = 0;
	initQueue(n);
	for (int i = 1; i <= n; i++)
		enqueue(G.vertices[i].d, i);

	while (!isEmpty()) {
		u = dequeue();
		printf(" %d", u);

		res += G.vertices[u].d;
		tmp = G.vertices[u].adjacent;

		while (tmp->next) {
			z = opposite(tmp->next, u);
			e = tmp->next->index;
			if (find(z) && G.edges[e].weight < G.vertices[z].d) {
				G.vertices[z].p = u;
				G.vertices[z].d = G.edges[e].weight;
				replaceKey(z, G.vertices[z].d);
			}
			tmp = tmp->next;
		}
	}
	printf("\n%d", res);
}
int main() {
	buildGraph();
	PrimJarnik(1);
	free(G.vertices);
	free(G.edges);
	free(Q.key);
	free(Q.value);
	return 0;
}

