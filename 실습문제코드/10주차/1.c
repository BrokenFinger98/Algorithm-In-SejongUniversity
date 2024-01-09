#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {	
	int index;
	struct node* next;
}node;
typedef struct vertex {	
	node* ad;
	int id;
}vertex;
typedef struct edge {		
	int weight;
	int	start;
	int end;
	int id;
}edge;
typedef struct graph {		
	vertex* vertices;
	edge* edges;
}graph;
graph g;
int m;					
node* getNode(int index) {
	node *p = (node*)malloc(sizeof(node));
	p->index = index;
	p->next = NULL;
	return p;
}
int opposite(node *p, int a) {
	edge e = g.edges[p->index];
	if (e.start == a)
		return e.end;
	else
		return e.start;
}
void insert(int id, int a, int b) {
	node* p = g.vertices[a].ad;	
	node* q = getNode(id);
	int v1, v2;
	if (p->next == NULL)
		g.vertices[a].ad->next = q;
	else {
		while (1) {
			v1 = opposite(p->next, a);
			if (v1 > b) {
				q->next = p->next;
				g.vertices[a].ad->next = q;
				return;
			}else if (p->next->next != NULL) {
				v2 = opposite(p->next->next, a);
				if (v2 > b) {
					q->next = p->next->next;
					p->next->next = q;
					return;
				}
			}
			p = p->next;
			if (p->next == NULL)
				break;
		}
	}
	p->next = q;
}
void createEdge(int id, int a, int b, int w) {
	g.edges[id].id = id;
	g.edges[id].start = a;
	g.edges[id].end = b;
	g.edges[id].weight = w;
	insert(id, a, b);
	if (a != b) {
		insert(id, b, a);
	}
}
void initGraph() {
	g.vertices = (vertex*)malloc(sizeof(vertex) * 7);
	g.edges = (edge*)malloc(sizeof(edge) * 21);	
	for (int i = 1; i <= 6; i++) {
		g.vertices[i].id = i;
		g.vertices[i].ad = getNode(-1);
	}
	m = 0;
	createEdge(m++, 1, 2, 1);
	createEdge(m++, 1, 3, 1);
	createEdge(m++, 1, 4, 1);
	createEdge(m++, 1, 6, 2);
	createEdge(m++, 2, 3, 1);
	createEdge(m++, 3, 5, 4);
	createEdge(m++, 5, 5, 4);
	createEdge(m++, 5, 6, 3);
}
void print(int a) {
	if (a <= 0 || a > 6) {
		printf("-1\n");
		return;
	}
	int opSide, e;
	node *p = g.vertices[a].ad;
	if (p == NULL)
		return -1;
	while (1) {
		e = p->next->index;
		opSide = opposite(p->next, a);
		printf(" %d %d", g.vertices[opSide].id, g.edges[e].weight);
		p = p->next;
		if (p->next == NULL)
			break;
	}
	printf("\n");
}
void change(int a, int b, int w) {
	if (a <= 0 || a > 6 || b <= 0 || b > 6) {
		printf("-1\n");
		return;
	}
	int destination = -1, start, end;
	int i;
	if (a > b) {
		start = b;
		end = a;
	}else {
		start = a;
		end = b;
	}

	for (i = 0; i < m; i++) {
		if (g.edges[i].id != -1 && g.edges[i].start == start && g.edges[i].end == end) {
			destination = i;
			break;
		}
	}

	if (destination != -1) {
		if (w == 0) {			
			removeCall(a, b, destination);
			return;
		}else				
			g.edges[destination].weight = w;
	}else if (destination == -1) {
		if (w == 0)			
			return;
		else {					
			createEdge(m++, a, b, w);
			return;
		}
	}
}
void removeCall(int a, int b, int destination) {
	g.edges[destination].id = -1;	
	removeE(a, b, destination);
	if (a != b)
		removeE(b, a, destination);
}
void removeE(int a, int b, int destination) {
	node* node1 = g.vertices[a].ad->next;
	node* node2 = g.vertices[a].ad->next->next;
	while (1) {
		if (g.vertices[a].ad->next->index == destination) {	
			free(g.vertices[a].ad->next);
			g.vertices[a].ad->next = node2;
			return;
		}else if (node2->index == destination) {
			node1->next = node2->next;
			free(node2);
			return;
		}
		node1 = node1->next;
		node2 = node2->next;
		if (node1 == NULL)
			break;
	}
}
int main() {
	initGraph();
	char cmd;
	int a, b, w, k;
	while (1) {
		scanf("%c", &cmd);
		if (cmd == 'a') {
			scanf("%d", &k);
			getchar();
			print(k);
		}else if (cmd == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();
			change(a, b, w);
		}else if (cmd == 'q'){
            free(g.vertices);
            free(g.edges);
            return 0;
        }
	}
}

