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
	//int count = 0;

	//count how many lines in the file there are
	while (fgets(line, MAX_LEN, in) != NULL){
		n++;
	}
	//reset the pointer in the infile to the start
	fseek(in, 0, SEEK_SET);
	//make the string array using malloc
	
	char **arr;
	arr = malloc(n * (sizeof(char*)));
	
	//char* arr[n];
	
	/*
	char *curr_str;
	//add each line to the infile, line by line
	while(fgets(line, MAX_LEN, in) != NULL){
		line[strlen(line)-1] = '\0';
		//strcpy(curr_str, line);
		curr_str = line;
		arr[count] = *curr_str;
		count++;
	}
	*/
	/*
	while(!feof(in)){
		fgets(arr[count], MAX_LEN, in);
		count++;	
	}
	*/
	
	for(int i = 0; i < n; i++){
		arr[i] = malloc(sizeof(char)*MAX_LEN);
		fgets(arr[i], MAX_LEN, in);		
	}
	
	/*
	int i = 0;
	while(fgets(line, MAX_LEN, in)){
		arr[i] = malloc(MAX_LEN);
		strcpy(arr[i], line);
		i++;
	}
	*/
	List L = newList();
	int curr_ele;
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

	/*
	//create the list of integers
	int list[n];
	//add numbers 0-n to the list
	for(int i = 0; i < n; i++){
		list[i] = i;
	}
	//use insertion sort algorithm to sort the list based on the string array
	//Credit for the insertion sort algorithm: Assignment 3 pdf from CSE 13s 
	for(int i = 1; i < n; i++){
		int j = i;
		char * temp = arr[i];
		while(j > 0 && (strcmp(temp, arr[j-1]) < 0 || strcmp(temp, arr[j-1]) == 0)){
			list[j] = list[j-1];
			j--;
		}
		list[j] = i;
	}
	*/

	
	//print the array in alphabetical order to the output file
	//fprintf(out, "hi");
	//printList(out, L);
	
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
	freeList(&L);
	L = NULL;
	return(0);
}
