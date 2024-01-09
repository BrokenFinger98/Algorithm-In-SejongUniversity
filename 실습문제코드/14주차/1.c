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
	Node *P = (Node*)malloc(sizeof(Node));
	P->index = i;
	P->next = NULL;
	return P;
}
void insert(int id, int a, int b) {
	Node *header = G.vertices[a].adjacent;
	Node *P;
	while (header->next)
		header = header->next;
	P = getNode(id);
	header->next = P;
}
void edge(int id, int s, int e, int w) {
	G.edges[id].start = s;
	G.edges[id].end = e;
	G.edges[id].weight = w;
	insert(id, s, e);
	if (s != e)
		insert(id, e, s);
}
void buildGraph() {
	int s, e, w;

	G.edges = (Edge *)malloc(sizeof(Edge) * m);
	G.vertices = (Vertex *)malloc(sizeof(Vertex) * (n + 1));	
	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].adjacent = getNode(-1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &s, &e, &w);
		edge(i, s, e, w);
	}
}
void initQueue() {
	Q.max = n;
	Q.size = 0;
	Q.key = (int *)malloc(sizeof(int) * n);
	Q.value = (int *)malloc(sizeof(int) * n);
}
void enqueue(int k, int v) {
	int index;
	index = Q.size;
	Q.key[index] = k;
	Q.value[index] = v;
	Q.size += 1;
}
int dequeue() {
	int minK, minV, index;

	minK = Q.key[0];
	minV = Q.value[0];
	index = 0;
	for (int i = 1; i < Q.max; i++) {
		if (Q.key[i] < minK) {
			minK = Q.key[i];
			minV = Q.value[i];
			index = i;
		}
	}
	Q.key[index] = 999999;
	Q.value[index] = -1;
	Q.size -= 1;

	return minV;
}
int isEmpty() {
	if (Q.size == 0)
		return 1;
	else
		return 0;
}
int find(int ob) {
	for (int i = 0; i < Q.max; i++) 
		if (Q.value[i] == ob)
			return 1;
	return 0;
}
void replaceKey(int ob, int key) {
	for (int i = 0; i < Q.max; i++)
		if (Q.value[i] == ob)
			Q.key[i] = key;
}
int opposite(Node *e, int a) {
	Edge k = G.edges[e->index];
	if (k.start == a)
		return k.end;
	else
		return k.start;
}
void Dijkstra(int s) {
	int u = -1;
	int z, e;
	for (int i = 1; i <= n; i++) {
		G.vertices[i].d = 999999;
		G.vertices[i].p = -1;
	}
	G.vertices[s].d = 0;
	initQueue();
	for (int i = 1; i <= n; i++)
		enqueue(G.vertices[i].d, i);

	Node *k;
	while (!isEmpty()) {
		u = dequeue();
		if (u == -1)
			break;
		k = G.vertices[u].adjacent;
		while (k->next) {
			z = opposite(k->next, u);
			e = k->next->index;
			if (find(z) && (G.edges[e].weight + G.vertices[u].d) < G.vertices[z].d) {
				G.vertices[z].p = u;
				G.vertices[z].d = G.edges[e].weight + G.vertices[u].d;
				replaceKey(z, G.vertices[z].d);
			}
			k = k->next;
		}
	}
}
int main() {
	int s;
	scanf("%d %d %d", &n, &m, &s);
	buildGraph();
	Dijkstra(s);
	for (int i = 1; i <= n; i++) 
		if (G.vertices[i].p != -1)
			printf("%d %d\n", G.vertices[i].id, G.vertices[i].d);
	free(G.vertices);
	free(G.edges);
	free(Q.key);
	free(Q.value);

	return 0;
}