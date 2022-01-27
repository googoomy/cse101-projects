/******************************************************************
 *James Gu
 *jjgu
 *pa2
 *
 *
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main (){
	int n = 5;
	Graph G = newGraph(n);

	int order = getOrder(G);
	int size = getSize(G);
	int source = getSource(G);
	int parent = getParent(G, 2);
	int distance = getDist(G, 2);
       	printf("order: %d\nsize: %d\nsource: %d\nparent: %d\ndistance: %d\n", order, size, source, parent, distance);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	BFS(G, 1);	
	order = getOrder(G);
	size = getSize(G);
	source = getSource(G);
	parent = getParent(G, 2);
	distance = getDist(G, 2);
       	printf("order: %d\nsize: %d\nsource: %d\nparent: %d\ndistance: %d\n", order, size, source, parent, distance);
	List L = newList();
	getPath(L, G, 4);
	printf("path 1 to 4: ");
	printList(stdout, L);
	freeList(&L);
	printf("\n");
	printGraph(stdout, G);
	makeNull(G);
	freeGraph(&G);


}
