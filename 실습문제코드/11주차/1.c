#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node {	
	int index;
	struct Node *next;
}Node;
typedef struct Vertex {	
	Node *adjacent;
	int id;
	int visited;
}Vertex;
typedef struct Edge {	
	int	start;
	int end;
	int id;
}Edge;
typedef struct Graph {		
	Vertex *vertices;
	Edge *edges;
}Graph;
Graph G;
int n, m, s;
Node *getNode(int index) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->index = index;
	p->next = NULL;
	return p;
}
int opposite(Node *q, int a) {
	Edge e = G.edges[q->index];
	if (e.start == a)
		return e.end;
	else
		return e.start;
}
void insert(int index, int a, int b) {
	Node *q = G.vertices[a].adjacent;	
	Node *p = getNode(index);			
	int v1, v2;
	if (q->next == NULL)
		G.vertices[a].adjacent->next = p;
	else {
		while (1) {
			v1 = opposite(q->next, a);
			if (v1 > b) {
				p->next = q->next;
				G.vertices[a].adjacent->next = p;
				return;
			}
			else if (q->next->next != NULL) {
				v2 = opposite(q->next->next, a);
				if (v2 > b) {
					p->next = q->next->next;
					q->next->next = p;
					return;
				}
			}
			q = q->next;
			if (q->next == NULL)
				break;
		}
	}
	q->next = p;
}
void edgeMethod(int i, int a, int b) {
	G.edges[i].id = i;
	G.edges[i].start = a;
	G.edges[i].end = b;
	insert(i, a, b);
	if (a != b) 
		insert(i, b, a);

}
void initGraph() {
	int a, b;
	scanf("%d %d %d", &n, &m, &s);

	G.vertices = (Vertex *)malloc(sizeof(Vertex)*(n+1));
	G.edges = (Edge *)malloc(sizeof(Edge)*m);
	
	for (int i = 1; i <= n; i++) {
		G.vertices[i].id = i;
		G.vertices[i].visited = 0;				
		G.vertices[i].adjacent = getNode(-1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edgeMethod(i, a, b);
	}
}
void DFS(int s) {
	G.vertices[s].visited = 1;
	printf("%d\n", G.vertices[s].id);
	Node* q = G.vertices[s].adjacent;
	int O;
	while (q->next != NULL) {
		O = opposite(q->next, s);
		if (G.vertices[O].visited == 0)
			DFS(O);
		q = q->next;
	}
}
int main() {
	initGraph();
	DFS(s);
	free(G.vertices);
	free(G.edges);

	return 0;
}