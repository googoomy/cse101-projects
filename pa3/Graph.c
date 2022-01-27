/******************************************************************
 *James Gu
 *jjgu
 *pa3
 *
 *
 *
 *****************************************************************/


#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//constants to mean white gray and black for BFS
#define WHITE 0
#define GRAY 1
#define BLACK 2


//structs
typedef struct GraphObj{
	//an array of Lists whose ith element contains the neighbors of vertex i
	List *neighbors;
	//an array of ints whose ith element is the color of vertex i
	int *color;
	//an array of ints whose ith element is the parent of vertex i
	int *parent;
	//an array of ints whose ith element is the distance from the source to vertex i
	int *distance;
	//the number of vertices
	int order;
	//the number of edges
	int size;
	//the label of the vertex that was most recently used as source for BFS
	int source;
} GraphObj;

/*** Constructors-Destructors ***/
//Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n){
	//all arrays should be length n + 1
	//allocate memory for every array
	Graph G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List));
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	//initialize every list in neighbors[]
	for(int i = 1; i <= n; i++){
		G->neighbors[i] = newList();
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

//Function freeGraph() frees all heap memory associated with Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
	if(pG != NULL && * pG != NULL){
		//free every list in neighbors[]
		for(int i = 1; i <= getOrder(*pG); i++){
			freeList(&((*pG)->neighbors[i]));
		}
		//free every other array
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free(*pG);
		*pG = NULL;
	}	
}

/*** Access functions ***/
//Function getOrder() returns the number of vertices
int getOrder(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

//Function getSize() returns the number of edges
int getSize(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

//Function getParent() will return the parent of vertex u in the BFS tree created by BFS()
//Precondition: 1<=u<=getORder(G)
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


/*** Manipulation procedures ***/
//helper function that maintains the lists in sorted order by increasing labels
void addVertex(List L, int v){
	//similar to the insertion sort in Lex.c in pa1
	if(length(L) <= 0){
		append(L,v);
		return;
	}
	moveFront(L);
	for(int i = 0; i < length(L); i++){
		int curr_ele = get(L);
		//if the element is greater, then v belongs before it
		if(curr_ele >= v){
			insertBefore(L, v);
			break;
		}
		moveNext(L);
		//if v is the greatest then it goes at the end
		if(i == length(L)-1){
			append(L, v);
			break;		
		}
	}
}

//addEdge() inserts a new edge joining u to v.
//precondition both u and v lie between 1 and getOrder(G)
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

//addArc inserts a new directed edge from u to v
//precondition both u and v lie between 1 and getOrder(G)
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

/*** Other operations ***/
//printGraph prints the adjacency list representation of G to file out
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	//loop through each vertex
	for(int i = 1; i <= getOrder(G); i++){
		//this is the 1:, 2:, or 3:, etc. part
		fprintf(out, "%d: ", i);
		//loop through neighbors
		//start at beginning
		moveFront(G->neighbors[i]);
		for(int j = 1; j <= length(G->neighbors[i]); j++){
			//get the current element
			int curr_ele = get(G->neighbors[i]);
			//if the element is valid
			if(curr_ele > 0){
				//add it to the output
				fprintf(out, "%d ", curr_ele);
			}
			//move a step froward
			moveNext(G->neighbors[i]);
		}
		//move on to next vertex
		fprintf(out, "\n");
	}
	fprintf(out, "\n");
}
