#include <string.h>
#include "graph.h"
#include "heap.h"

Graph initGraph(int V) {
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->V = V;
	g->adjLists = (List*) malloc(V * sizeof(List));
	for (i = 0; i < V; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(V, sizeof(int));
	g->start = malloc(V * sizeof(int));
	g->end = malloc(V * sizeof(int));
	return g;
}

Graph insertEdge(Graph g, int u, int v, int cost) {
	Pair p;
	p.v = v;
	p.cost = cost;
	g->adjLists[u] = addLast(g->adjLists[u], p);
	return g;
}

int isArc(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

int getCost(Graph g, int u, int v) {
	List tmp = g->adjLists[u];
	while (tmp != NULL) {
		if (tmp->data.v == v)
			return tmp->data.cost;
		tmp = tmp->next;
	}
	return INFINITY;
}

//Functie care va deseneaza graful
void drawGraph(Graph g, char *name)
{
	int i, j;
	FILE *stream;
	char *buffer, *aux;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	fprintf(stream, "digraph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->V; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			fprintf(stream, "    %d -> %d;\n", i, tmp->data.v);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	aux = (char*) malloc(SIZE*sizeof(char));
	strncpy(aux, name, strlen(name) - 4);
	sprintf(buffer, "dot %s.dot | neato -n -Tpng -o %s.png", aux, aux);
	system(buffer);
	free(buffer);
}

void Dijkstra(Graph g, int *parent, int *dist, int source) {
	Heap *h;
	int i;
	int *vizitat = malloc((g->V)*sizeof(int));
	int nod, u;

	h = new_heap(g->V, 0, NULL, MIN_h);
	//TODO 1
	printf("v = %d\n", g->V);
	vizitat[source] = 1;
	for (i = 1; i < g->V; i++) {
		dist[i] = INFINITY;
		parent[i] = -1;
		vizitat[i] = 0;
	}
	dist[source] = 0;
	vizitat[source] = 1;
	List tmp = g->adjLists[source];
	while (tmp != NULL) {
		nod = tmp->data.v;
		dist[nod] = tmp->data.cost;
		insert(h, nod, dist[nod]);
		printf("insert %d %d\n", nod, dist[nod]);
		parent[nod] = source;
		tmp = tmp->next;
	}
	while (h->size > 0) {
		u = h->keys[1];
		i = pop(h, 0);
		printf("%d %d\n", u, dist[u]);
		vizitat[u] = 1;
		tmp = g->adjLists[u];
		while (tmp != NULL) {
			nod = tmp->data.v;
			if (!vizitat[nod] && dist[nod] > dist[u] + tmp->data.cost) {
				dist[nod] = dist[u] + tmp->data.cost;
				parent[nod] = u;
				insert(h, nod, dist[nod]);
				printf("insert %d %d\n", nod, dist[nod]);
			}
			tmp = tmp->next;
		}
	}
}

int cmp(const void *a, const void *b) {
	Edge m1, m2;
	m1 = *(Edge *) a;
	m2 = *(Edge *) b;
	return m1.cost - m2.cost;
}

Graph Kruskal(Graph g) {
	Graph AMA;
	int *status, i, count, capacity, j, x;
	Edge *edges;
	List tmp;

	AMA = initGraph(g->V);
	//TODO 2
	capacity = sizeof(struct edge);
	edges = malloc(capacity);
	count = 0;
	int value;

	//creeaza un vector cu muchii
	for (i = 0; i < g->V; i++) {
        tmp = g->adjLists[i + 1];
        while (tmp != NULL) {
            edges[count].u = i + 1;
            edges[count].v = tmp->data.v;
            edges[count].cost = tmp->data.cost;
            tmp = tmp->next;
            count++;
            edges = realloc(edges, (count + 1) * capacity);
        }
	}
	qsort(edges, count - 1, sizeof(struct edge), cmp);
	status = malloc((g->V + 1) * sizeof(int));
	for (i = 1; i <= g->V; i++)
        status[i] = 'a' + i; //asociez fiecarei componente conexe o distinctie
	x = 0; //nr de muchii adaugate in AMA
    for (i = 0; i < count; i++)
            if (status[edges[i].u] != status[edges[i].v]) { //gaseste o muchie buna pt adaugat
                AMA = insertEdge(AMA, edges[i].u, edges[i].v, edges[i].cost);
                value = status[edges[i].u];
                for (j = 1; j < g->V; j++)
                	if (status[j] == value)
                		status[j] = status[edges[i].v];
            }
	return AMA;
}

/*Graph Prim(Graph g) {
	Heap *h;
	int i;
	int *vizitat = malloc((g->V)*sizeof(int));
	int nod, u;

	h = new_heap(g->V, 0, NULL, MIN_h);

	Graph AMA;
	AMA = initGraph(g->V);
}*/