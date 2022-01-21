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
		addEdge(G, u, v);
	}
	//print the contructed graph to the outfile
	printGraph(out, G);
	
	//name all the shortest paths
	//intialize the source and destination
	int source, destination = 1;
	while(!feof(in)){
		//scan in the source and destination pairs
		fscanf(in, "%d %d", &source, &destination);
		//terminate the loop if the pair is (0,0)
		if(source == 0 && destination == 0){
			break;
		}
		//preform bfs
		BFS(G, source);
		//if distance is infinite i.e. no connection
		if(getDist(G, destination) == INF){
			fprintf(out, "\nThe distance from %d to %d is infinity\n", source, destination);
			fprintf(out, "No %d-%d path exists\n", source, destination);
		//if the distance is attainable
		}else{
			List L = newList();
			getPath(L, G, destination);
			fprintf(out, "\nThe distance from %d to %d is %d\n", source, destination, getDist(G, destination));
			fprintf(out, "A shortest %d-%d path is: ", source, destination);
			printList(out, L);
			fprintf(out, "\n");
			freeList(&L);
		}
	}
}	

