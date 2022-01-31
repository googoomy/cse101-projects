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
	//make the stack the same size as the order of G
	List S = newList();
	for(int i = 1; i <= getOrder(G); i++){
		append(S, i);
	}
	//Run DFS on G and GT
	DFS(G, S);
	Graph GT = transpose(G);
	DFS(GT, S);
	//find the strong components
	int strong_comps = 0;
	//loop through to find out how many strong components there are
	moveBack(S);
	for(int i = 1; i <=getOrder(G); i++){
		int curr_par = getParent(GT, get(S));
		if(curr_par == NIL){
			strong_comps++;
		}
		movePrev(S);
	}
	//print the strong components to the outfile
	fprintf(out, "G contains %d strongly connected components: \n", strong_comps);
	//loop through and print the list for each component
	moveBack(S);
	//temporary list of components to print out
	List comps = newList();
	for(int i = 1; i <= strong_comps; i++){
		fprintf(out, "Component %d: ", i);
		while(true){
			prepend(comps, get(S));
			int curr_par = getParent(GT, get(S));
			//if parent is nil, then it is a strong comp
			if(curr_par == NIL){
				printList(out, comps);
				fprintf(out, "\n");
				break;
			}

			movePrev(S);
		}
		movePrev(S);
		//reset the temporary list
		clear(comps);
	}
	
	//frees and closing infile and outfile
	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&GT);
	clear(comps);
	freeList(&comps);
	clear(S);
	freeList(&S);
}
