/******************************************************************
 *James Gu
 *jjgu
 *pa2
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

//Function getSource returns the source vertex most recently used in BFS() or NIL if BFS() hasn't been called yet
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

//Function getDist() returns the distance from the most recent BFS source to vertex u or INF if BFS() hasn't been called yet
//Precondition:1<=u<=getOrder(G)
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

//Function getPath() append to the List L the vertices of the shortest path in G from source to u, or appends to L the value of NIL if no such path exists.
//Precondition: getSource(G) != NIL, 1<=u<=getOrder(G)
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
		//recursively call getPath
		getPath(L, G, getParent(G, u));
		append(L, u);
	}

}

/*** Manipulation procedures ***/
//makeNull() restores G to its original (no edge) state
void makeNull(Graph G){
	int graph_order = getOrder(G);
	freeGraph(&G);
	G = newGraph(graph_order);
}

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

//Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly. 
//Credit: BFS pseudocode from the handouts
void BFS(Graph G, int s){
	if(G == NULL){
		fprintf(stderr, "Graph Error: calling BFS() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(s < 1 || s > getOrder(G)){
		fprintf(stderr, "Graph Error: calling BFS() with invalid index. The range of index should be 1 <= s <= getOrder(G)\n");
		exit(EXIT_FAILURE);
	}
	//set the source to s
	G->source = s;
	//intialize every array with default values
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	//set source vertex to gray (discover it)
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	//equivalent of the queue in the example
	List L = newList();
	append(L, s);
	
	//while the queue has vertices
	while(length(L) != 0){
		//dequeue()
		moveFront(L);
		int x = get(L);
		deleteFront(L);
		//if the current neighbors[x] isnt empty then start at beginning
		if(length(G->neighbors[x]) != 0){
			moveFront(G->neighbors[x]);
		}
		//loop through neighbrs[x]
		while(index(G->neighbors[x]) != -1){
			//y = curr_ele
			int y = get(G->neighbors[x]);
			//if the current element is undiscovered
			if(G->color[y] == WHITE){
				//then discover it
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(L, y);
			}
			//go to next element	
			moveNext(G->neighbors[x]);
		}
		//the vertex has no other ways to go so it is done now
		//so make it black
		G->color[x] = BLACK;	
	}
	//free the queue because it is temporary
	freeList(&L);

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
