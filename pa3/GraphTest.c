/******************************************************************
 *James Gu
 *jjgu
 *pa3
 *
 *
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"


int main (){
	Graph G = newGraph(8);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 7);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 7, 8);
	addArc(G, 8, 8);
	printGraph(stdout, G);
	Graph GT = transpose(G);
	printGraph(stdout, GT);
	Graph CPY = copyGraph(G);
	printGraph(stdout, CPY);	
	List S = newList();
	for(int i = 1; i <= getOrder(G); i++){
		append(S, i);
	}
	printList(stdout, S);
	fprintf(stdout, "\n");
	DFS(G, S);
	printList(stdout, S);
	fprintf(stdout, "\n");
	DFS(GT, S);
	printList(stdout, S);
	fprintf(stdout, "\n");
	moveBack(S);
	for(int i = 1; i <= length(S); i++){
		printf("curr in stack: %d\n", get(S));
		if(getParent(GT, get(S)) == NIL){
			printf("no parent\n");
		}else{
			printf("curr parent %d\n", getParent(GT, get(S)));
		}
		movePrev(S);
	}
	for(int i = 1; i < getOrder(G); i++){
		
	}
	freeGraph(&G);
	freeGraph(&GT);
	freeList(&S);










}
