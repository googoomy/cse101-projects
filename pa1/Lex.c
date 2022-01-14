/****************************************
 * James Gu
 * jjgu
 * pa1
 *
 *
 *
****************************************/


#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300
 //
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


	char line[MAX_LEN];
	int n = 0;

	//count how many lines in the file there are
	while (fgets(line, MAX_LEN, in) != NULL){
		n++;
	}
	//reset the pointer in the infile to the start
	fseek(in, 0, SEEK_SET);
	//make the string array using malloc
	
	char **arr;
	arr = malloc(n * (sizeof(char*)));
	
	//add every string in the lines to the arr
	for(int i = 0; i < n; i++){
		arr[i] = malloc(sizeof(char)*MAX_LEN);
		fgets(arr[i], MAX_LEN, in);		
	}
	
	//create an empty list
	List L = newList();
	int curr_ele;
	//use insertion sort to add the elements into the list
	for(int i = 0; i < n; i++){
		if(i == 0){
			append(L, 0);
		}else{
			moveFront(L);
			for(int j = 0; j < length(L); j++){
				curr_ele = get(L);
				if((strcmp(arr[i], arr[curr_ele]) <= 0)){
					insertBefore(L, i);
					break;
				}
				if(j == length(L)-1){
					append(L, i);
					break;
				}
				moveNext(L);
			}
		}
	}

	moveFront(L);
	
	for(int i = 0; i < n; i++){
		fprintf(out, "%s", arr[get(L)]);
		moveNext(L);
	}
	
	//close files
	fclose(in);
	fclose(out);
	
	//free the string array	
	for(int i = 0; i < length(L); i++){
		free(arr[i]);
	}
	free(arr);

	//free the list	
	freeList(&L);
	L = NULL;
	return(0);
}
