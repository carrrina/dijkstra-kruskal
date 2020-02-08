build: graph

graph: list.c graph.c test.c heap.c
	gcc test.c graph.c list.c heap.c -o graph -g
