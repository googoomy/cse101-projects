#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300

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
	int count = 0;

	//count how many lines in the file there are
	while (fgets(line, MAX_LEN, in) != NULL){
		n++;
	}
	//reset the pointer in the infile to the start
	fseek(in, 0, SEEK_SET);
	//make the string array using malloc
	char *arr = (char *)malloc(n * (sizeof(char)));
	//add each line to the infile, line by line
	while(fgets(line, MAX_LEN, in) != NULL){
		char * str;
		fscanf(in, "%s", str);
		arr[count] = str;
		count++;
	}
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
	
	//print the array in alphabetical order to the output file
	for(int i = 0; i < n; i++){
		fprintf(out, "%s\n", arr[list[i]]); 
	}

	//close files
	fclose(in);
	fclose(out);
	//free the string array
	free(arr);
	return(0);
}
