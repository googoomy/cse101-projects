#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2


//structs
typedef struct GraphObj{
	List *neighbors;
	int *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	for(int i = 1; i <= n; i++){
		G->neighbors[i] = newList();
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

void freeGraph(Graph* pG){
	if(pG != NULL && * pG != NULL){
		for(int i = 1; i <= getOrder(*pG); i++){
			freeList(&((*pG)->neighbors[i]));
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
		getPath(L, G, getParent(G, u));
		append(L, u);
	}

}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	int graph_order = getOrder(G);
	freeGraph(&G);
	G = newGraph(graph_order);
}

void addVertex(List L, int v){
	if(length(L) == 0){
		append(L,v);
		return;
	}
	moveFront(L);
	for(int i = 0; i < length(L); i++){
		int curr_ele = get(L);
		if(curr_ele >= v){
			insertBefore(L, v);
			break;
		}
		moveNext(L);
		if(i == length(L)-1){
			append(L, v);
			break;		
		}
	}
}


void addEdge(Graph G, int u, int v){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() with invalid index. The range of index should be 1 <= v <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	addVertex(G->neighbors[u], v);
	addVertex(G->neighbors[v], u);
	G->size++;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	if(v < 1 || v > getOrder(G)){
		fprintf(stderr, "Graph Error: calling addEdge() with invalid index. The range of index should be 1 <= v <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	addVertex(G->neighbors[u], v);
	G->size++;
}

void BFS(Graph G, int s){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(s < 1 || s > getOrder(G)){
		fprintf(stderr, "Graph Error: calling BFS() with invalid index. The range of index should be 1 <= s <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	G->source = s;
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List L = newList();
	append(L, s);
	while(length(L) > 0){
		int x = front(L);
		deleteFront(L);
		for(int y = 1; y <= length(G->neighbors[x]); y++){
			if(G->color[y] == WHITE){
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(L, y);
			}	
		}
		G->color[x] = BLACK;	
	}
	freeList(&L);

}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		moveFront(G->neighbors[i]);
		for(int j = 1; j <= length(G->neighbors[i]); j++){
			int curr_ele = get(G->neighbors[i]);
			if(curr_ele > 0){
				fprintf(out, "%d ", curr_ele);
			}
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
	}
	fprintf(out, "\n");
}
