#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//structs
typedef struct GraphObj{
	List *neighbors;
	int *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
}

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

void freeGraph(Graph* pG){
	if(pG != NULL && * pG != NULL){
		for(int i = 1; i <= getOrder(pG); i++){
			freeList(&(pG->neighbors[i]));
		}
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free(*pG);
		*pG = NULL;
	}	
}

/*** Access functions ***/
int getOrder(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getSource(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(G->source == NIL){
		return NIL;
	}
	return G->source;

}

int getParent(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getParent() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		return NIL;
	}
	return G->parent[u];

}

int getDist(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getDist() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	return G->distance[u];

}

void getPath(List L, Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getPath() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		fprintf(stderr, "Graph Error: calling getPath() on NIL Source. BFS() must be called before getPath()\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == u){
		append(L, u);
	}else if(G->parent[u] == NIL){
		append(L, NIL);
	}else{
		getPath(L, G, getParent(G, u);
		append(L, u);
	}

}

/*** Manipulation procedures ***/
void makeNull(Graph G){

}

void addEdge(Graph G, int u, int v){

}

void addArc(Graph G, int u, int v){

}

void BFS(Graph G, int s){

}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){

}
