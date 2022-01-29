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
#include <string.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
	//The beginning part of this program is based on the FileIO.c in the Examples from the class website
	FILE *in, *out;
	
	//check command line for correct number of arguments
	if(argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//open files for reading and writing
	in = fopen(argv[1], "r");
	if(in == NULL){
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");
	if(out == NULL){
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	//get the order of the graph
	int n = 0;
	fscanf(in, "%d", &n);
	//make the graph
	Graph G = newGraph(n);
	//make the entire graph with the infile
	//initialize the pairs of vertices
	int u, v = 1;
	while(!feof(in)){
		//get from the file the vertices pair
		fscanf(in, "%d %d", &u, &v);
		// pair (0,0) terminates loop
		if(u == 0 && v == 0){
			break;
		}
		//add the pair to the graph
		addArc(G, u, v);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	//print the contructed graph to the outfile
	printGraph(out, G);
	
	List S = newList();
	for(int i = 1; i <= getOrder(G); i++){
		append(S, i);
	}
	DFS(G, S);
	Graph GT = transpose(G);
	DFS(GT, S);
	int strong_comps = 0;
	moveBack(S);
	for(int i = 1; i <=getOrder(G); i++){
		int curr_par = getParent(GT, get(S));
		if(curr_par == NIL){
			strong_comps++;
		}
		movePrev(S);
	}

	fprintf(out, "G contains %d strongly connected components: \n", strong_comps);
	moveBack(S);
	List comps = newList();
	for(int i = 1; i <= strong_comps; i++){
		fprintf(out, "Component %d: ", i);
		while(true){
			prepend(comps, get(S));
			int curr_par = getParent(GT, get(S));
			if(curr_par == NIL){
				printList(out, comps);
				break;
			}

			movePrev(S);
		}
		movePrev(S);
		clear(comps);
	}

	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&GT);
	clear(comps);
	freeList(&comps);
	clear(S);
	freeList(&S);
}
