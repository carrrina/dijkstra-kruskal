#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "heap.h"

#define SIZE 200
#define INFINITY 999999

typedef struct graph {
	int V;
	List *adjLists;
	int *visited;
	int *start, *end;
}*Graph;

typedef struct edge {
	int u, v, cost;
} Edge;

Graph initGraph(int V);
Graph insertEdge(Graph g, int u, int v, int cost);
Graph deleteVertex(Graph g, int v);
int getInDegree(Graph g, int v);
void printGraph(Graph g);
void drawGraph(Graph g, char *name);
int isArc(Graph g, int u, int v);
int getCost(Graph g, int u, int v);
void Dijkstra(Graph g, int *parent, int *dist, int source);
Graph Kruskal(Graph g);

#endif