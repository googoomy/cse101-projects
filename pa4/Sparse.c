/********************************************
 * James Gu
 * jjgu
 * pa4
 *
 *
 * 
 *******************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

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
	int nnz_A = 0;
	int nnz_B = 0;
	//grab the size and non zero values from the first line
	fscanf(in, "%d %d %d", &n, &nnz_A, &nnz_B);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	int row = 0;
	int col = 0;
	double val = 0;
	//grab the rest of the mtrices
	for(int i = 1; i <= nnz_A; i++){
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
	}
	for(int i = 1; i <= nnz_B; i++){
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(B, row, col, val);
	}
	//all operations
	Matrix ScaleA = scalarMult(1.5, A);
	Matrix SumAB = sum(A, B);
	Matrix DoubleA = sum(A, A);
	Matrix DiffBA = diff(B, A);
	Matrix DiffAA = diff(A, A);
	Matrix TransA = transpose(A);
	Matrix MultAB = product(A, B);
	Matrix MultBB = product(B, B);

	//print all operations
	fprintf(out, "A has %d non-zero entries:\n", nnz_A);
	printMatrix(out, A);

	fprintf(out, "B has %d non-zero entries:\n", nnz_B);
	printMatrix(out, B);

	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, ScaleA);

	fprintf(out, "A+B =\n");
	printMatrix(out, SumAB);
	
	fprintf(out, "A+A =\n");
	printMatrix(out, DoubleA);

	fprintf(out, "B-A =\n");
	printMatrix(out, DiffBA);

	fprintf(out, "A-A =\n");
	printMatrix(out, DiffAA);

	fprintf(out, "Transpose(A) =\n");
	printMatrix(out, TransA);

	fprintf(out, "A*B =\n");
	printMatrix(out, MultAB);

	fprintf(out, "B*B =\n");
	printMatrix(out, MultBB);

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&ScaleA);
	freeMatrix(&SumAB);
	freeMatrix(&DoubleA);
	freeMatrix(&DiffBA);
	freeMatrix(&DiffAA);
	freeMatrix(&TransA);
	freeMatrix(&MultAB);
	freeMatrix(&MultBB);
	fclose(in);
	fclose(out);
}
