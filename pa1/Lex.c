#include "Lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300

int main(int argc, char * argv[]){
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

	out = fopen(arg[2], "w");
	if(out == NULL){
		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}


	char line[MAX_LEN];
	chr tokenBuffer[MAX_LEN];
	int n = 0;
	int token_count = 0;
	char* token;
	int count = 0;

	while (fgets(line, MAX_LEN, in) != NULL){
		n++;
	}

	fseek(in, 0, SEEK_SET);
	char *arr = (char *)malloc(n * (sizeof(char)));
	while(fgets(line, MAX_LEN, in) != NULL){
		char * str;
		fscanf(in, "%s", str);
		char *str[count];
		count++;
	}
	
	int list[n];
	for(int i = 0; i < n; i++){
		list[i] = i;
	}
	for(int i = 1; i < n; i++){
		int j = i;
		char * temp = arr[i];
		while(j > 0 && strcmp(temp, arr[j-1]) < 0){
			list[j] = list[j-1];
			j--;
		}
		list[j] = i;
	}
	/*
	while (fgets(line, MAX_LEN, in) != NULL){
		line_count++;

		//get tokens in this line
		token_count = 0;
		tokenBuffer[0] = '\0';
		
		//get first token
		token = strok(line, " \n");
		while(token != NULL){ //we have a token
			//update token buffer
			strcat(tokenBuffer, "   ");
			strcat(tokenBuffer, token);
			strcat(tokenBuffer, "\n");
			token_count++;

			//ger next token
			token = strtok(NULL, " n");
		}

	}
*/



}
