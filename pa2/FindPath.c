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
	int n = 0;
	fscanf(in, "%d", &n);
	
	Graph G = newGraph(n);
	
	int u, v = 1;
	while(!feof(in)){
		fscanf(in, "%d %d", &u, &v);
		if(u == 0 && v == 0){
			break;
		}
		addEdge(G, u, v);
	}
	printGraph(out, G);
	
	int source, destination = 1;
	while(!feof(in)){
		fscanf(in, "%d %d", &source, &destination);
		if(source == 0 && destination == 0){
			break;
		}
		BFS(G, source);
		if(getDist(G, destination) == INF){
			fprintf(out, "\nThe distance from %d to %d is infinity\n", source, destination);
			fprintf(out, "No %d-%d path exists\n", source, destination);
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

