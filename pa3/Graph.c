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

//constants to mean white gray and black for DFS
#define WHITE 0
#define GRAY 1
#define BLACK 2


//structs
typedef struct GraphObj{
	List *neighbors;
	//an array of ints whose ith element is the color of vertex i
	int *color;
	//an array of ints whose ith element is the parent of vertex i
	int *parent;
	//an array of ints whose ith element is the discover time for vertex i
	int *discover;
	//the number of vertices
	int order;
	//the number of edges
	int size;
	//an array of ints whose ith element is the finish time for vertex i
	int *finish;
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
	G->discover = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));
	//initialize every list in neighbors[]
	for(int i = 1; i <= n; i++){
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	G->order = n;
	G->size = 0;
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
		free((*pG)->discover);
		free((*pG)->finish);
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

//Function getParent() will return the parent of vertex u in the DFS tree created by DFS()
//Precondition: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getParent() with invalid index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];

}

//Function getDiscover() will return the discover time for vertex u
//Precondition: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getDiscover() with invald index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return G->discover[u];
}

//Function getFinish() will return the finish time for vertex u
//Precondition: 1<= u<=getOrder(G)
int getFinish(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		fprintf(stderr, "Graph Error: calling getFinish() with invald index. The range of index should be 1 <= u <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	return G->finish[u];
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

//helper function for DFS that runs recursively
//Credit: Pseudocode given in GraphAlgorithms.pdf
void visit(Graph G, List S, int i, int* time){
	//discover the vertex
	*time += 1;
	G->discover[i] = *time;
	G->color[i] = GRAY;
	//traverse neighbors[i] from front
	moveFront(G->neighbors[i]);
	for(int y = 1; y <= length(G->neighbors[i]); y++){
		int curr_ele = get(G->neighbors[i]);
		if(G->color[curr_ele] == WHITE){
			G->parent[curr_ele] = i;
			visit(G, S, curr_ele, time);
		}
		moveNext(G->neighbors[i]);
	}	
	//vertex is finished so add it to finish[] and make it black
	G->color[i] = BLACK;
	prepend(S, i);
	*time += 1;
	G->finish[i] = *time;
}

//Function DFS() will perform the depth first search algorithm on G. 
//Credit: Pseudocode given in GraphAlgorithms.pdf
//Precondition: length of S must be same as the order of G
void DFS(Graph G, List S){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(S) !=  getOrder(G)){
		fprintf(stderr, "Graph Error: calling DFS() with invald sized Stack. The stack's length should be equal to getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	//initialize every color and parent
	moveFront(S);
	for(int i = 1; i <= getOrder(G); i++){
		int curr;
		if(index(S) != -1){
			curr = get(S);
		}
		G->color[curr] = WHITE;
		G->parent[curr] = NIL;
		moveNext(S);
	}
	//traverse the graph from front
	moveFront(S);
	int time = 0;
	for(int i = 1; i <= getOrder(G); i++){
		int curr;
		if(index(S) != -1){
			curr = get(S);
			moveNext(S);
		}
		//if the vertex is undiscovered then visit it
		if(G->color[curr] == WHITE){
			visit(G, S, curr, &time);
		}
	}
	//need to remove the 1 2 3 4 5 ... from the stack
	for(int i = 1; i <= getOrder(G); i++){
		deleteBack(S);
	}
	
}

/*** Other operations ***/
//transpose() returns a Graph that is the transpose of G. transpose is where the directions are reversed
Graph transpose(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling transpose() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	//make a new graph
	Graph GT = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		for(int j = 1; j <= length(G->neighbors[i]); j++){
			int curr_ele = get(G->neighbors[i]);
			//swap curr_ele and i to change direction
			addArc(GT, curr_ele, i);
			moveNext(G->neighbors[i]);
		}
	}
	return GT;

}

//copyGraph() returns a Graph that is a copy of G
Graph copyGraph(Graph G){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	//make a new graph
	Graph CPY = newGraph(getOrder(G));
	for(int i = 1; i <= getOrder(G); i++){
		moveFront(G->neighbors[i]);
		for(int j = 1; j <= length(G->neighbors[i]); j++){
			int curr_ele = get(G->neighbors[i]);
			//leave it unchanged to copy the direction
			addArc(CPY, i, curr_ele);
			moveNext(G->neighbors[i]);
		}
	}
	return CPY;


}

//outputs the adjacency list of graph G to outfile
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
