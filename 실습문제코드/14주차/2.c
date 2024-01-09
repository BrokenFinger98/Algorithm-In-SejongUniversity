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
	Node *in;
	Node *out;
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
Graph G;
int n, m;
Node *getNode(int i) {
	Node *P = (Node *)malloc(sizeof(Node));
	P->index = i;
	P->next = NULL;
	return P;
}
void insert(Node *header, int id) {
	Node *P = getNode(id);
	while (header->next)
		header = header->next;
	header->next = P;
}
void edge(int id, int s, int e, int w) {
	G.edges[id].start = s;
	G.edges[id].end = e;
	G.edges[id].weight = w;
	insert(G.vertices[s].out, id);
	insert(G.vertices[e].in, id);
}
void buildGraph() {
	int s, e, w;
	G.edges = (Edge *)malloc(sizeof(Edge) * m);
	G.vertices = (Vertex *)malloc(sizeof(Vertex) * (n + 1));
	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].out = getNode(-1);
		G.vertices[i].in = getNode(-1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &s, &e, &w);
		edge(i, s, e, w);
	}
}
void bellman(int start) {
	int u = -1;
	int z, e, weight = 0;
	Node *k;
	for (int i = 1; i <= n; i++) {
		G.vertices[i].d = 999999;
		G.vertices[i].p = -1;
	}
	G.vertices[start].d = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			u = G.edges[j].start;
			z = G.edges[j].end;
			weight = G.edges[j].weight;
			if (G.vertices[u].d != 999999 && (G.vertices[u].d + weight) < G.vertices[z].d) {
				G.vertices[z].p = u;
				G.vertices[z].d = G.vertices[u].d + weight;
			}
		}
	}
}
int main() {
	int start;
	scanf("%d %d %d", &n, &m, &start);
	buildGraph();
	bellman(start);
	for (int i = 1; i <= n; i++) 
		if (G.vertices[i].p != -1)
			printf("%d %d\n", G.vertices[i].id, G.vertices[i].d);
	free(G.vertices);
	free(G.edges);

	return 0;
}