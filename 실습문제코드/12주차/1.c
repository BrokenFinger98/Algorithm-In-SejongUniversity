#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Incident {
	int element;
	struct Incident *next;
}Incident;
typedef struct Edge {
	int start;
	int end;
}Edge;
typedef struct Vertex {
    int inDegree;
	char name;
	Incident *inEdges;
	Incident *outEdges;
}Vertex;
typedef struct Graph {
    Edge *edges;
	Vertex *vertices;
}Graph;

Graph G;
int front, rear;
int queue[100];
int n, m;
int topOrder[100];

int isEmpty() {
	if (front == rear)
		return 1;
	else
		return 0;
}
void enqueue(int p) {
	queue[rear] = p;
	rear = (rear + 1) % 100;
}
int dequeue() {
	int p;
	p = queue[front];
	front = (front + 1) % 100;
	return p;
}
void initQueue() {
	for (int i = 0; i < 100; i++) {
		queue[i] = 0;
	}
}
int index(char vName) {
	for (int i = 0; i < n; i++) 
		if (G.vertices[i].name == vName)
			return i;
}
void topologicalSort() {
	int x[100] = { 0 };
	int t = 1, u, w;
	Incident *e;

	initQueue();
	for (int i = 0; i < n; i++) {
		x[i] = G.vertices[i].inDegree;
		if (x[i] == 0)
			enqueue(i);
	}
	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		++t;
		e = G.vertices[u].outEdges;
		e = e->next;
		while (e != NULL) {
			w = G.edges[e->element].end;
			--x[w];
			if (x[w] == 0)
				enqueue(w);
			e = e->next;
		}
	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}
void addFirst(Incident *H, int i) {
	Incident *node = (Incident *)malloc(sizeof(Incident));
	node->element = i;
	node->next = H->next;
	H->next = node;
}
void insertVertex(char vName, int i) {
	G.vertices[i].name = vName;
	G.vertices[i].outEdges = (Incident *)malloc(sizeof(Incident));
	G.vertices[i].inEdges = (Incident *)malloc(sizeof(Incident));
	G.vertices[i].outEdges->next = NULL;
	G.vertices[i].inEdges->next = NULL;
	G.vertices[i].inDegree = 0;
}
void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;
	u = index(uName);
	w = index(wName);
	G.edges[i].start = u;
	G.edges[i].end = w;
	addFirst(G.vertices[u].outEdges, i);
	addFirst(G.vertices[w].inEdges, i);
	G.vertices[w].inDegree++;
}
void buildGraph() {
	char vName, uName, wName;

	G.vertices = (Vertex*)malloc(sizeof(Vertex) * 100);
	G.edges = (Edge*)malloc(sizeof(Edge) * 1000);

	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}

	scanf("%d", &m);
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}
}
int main() {
	buildGraph();
	topologicalSort();

	if (topOrder[0] == 0)
		printf("0\n");
	else
		for (int i = 1; i <= n; i++)
			printf("%c ", G.vertices[topOrder[i]].name);
	for (int i = 0; i < n; i++) {
		free(G.vertices[i].inEdges);
		free(G.vertices[i].outEdges);
	}
	free(G.vertices);
	free(G.edges);
	return 0;
}

