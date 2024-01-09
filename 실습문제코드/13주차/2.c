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
typedef struct Set {
	int size;
	int k;
	int *data;
}Set;
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
Set *initSet(int a, int k) {
	Set *new = (Set *)malloc(sizeof(Set));
	new->size = a + 1;
	new->k = k;
	new->data = (int *)malloc(sizeof(int) * (a + 1));
	for (int i = 0; i < new->size; i++)
		new->data[i] = i;
	return new;
}
int setIndex(Set *s, int e) {
	return s->data[e];
}
void unionSet(Set *s, int a, int b) {
	s->k -= 1;
	for (int i = 0; i < s->size; i++) 
		if (s->data[i] == b)
			s->data[i] = a;
}
void kruskal() {
	Set *s;
	int index;
	int a, b;
	int result = 0;
	initQueue(m);
	for (int i = 0; i < m; i++)
		enqueue(G.edges[i].weight, i);
	s = initSet(n, n);
	for (int i = 1; i <= n; i++)
		s->data[i] = i;
	while (Q.size != 0) {
		index = dequeue();
		a = G.edges[index].start;
		b = G.edges[index].end;

		if (setIndex(s, a) != setIndex(s, b)) {
			result += G.edges[index].weight;
			printf(" %d", G.edges[index].weight);
			unionSet(s, setIndex(s, a), setIndex(s, b));
		}
	}
	printf("\n%d", result);
	free(s->data);
	free(s);
}
int main() {
	buildGraph();
	kruskal();
	free(G.vertices);
	free(G.edges);
	free(Q.key);
	free(Q.value);
	return 0;
}

