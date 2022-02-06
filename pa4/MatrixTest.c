#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

int main(){
	Matrix M = newMatrix(3);
	Matrix N = newMatrix(3);
	changeEntry(M, 1, 1, 1.0);
	changeEntry(M, 1, 2, 2.0);
	changeEntry(M, 1, 3, 3.0);	
	changeEntry(M, 2, 1, 4.0);
	changeEntry(M, 2, 2, 5.0);
	changeEntry(M, 2, 3, 6.0);
	changeEntry(M, 3, 1, 7.0);
	changeEntry(M, 3, 2, 8.0);
	changeEntry(M, 3, 3, 9.0);

	changeEntry(N, 1, 1, 1.0);
	changeEntry(N, 1, 3, 1.0);
	changeEntry(N, 3, 1, 1.0);
	changeEntry(N, 3, 2, 1.0);
	changeEntry(N, 3, 3, 1.0);
	
	printMatrix(stdout, M);
	int nnz_M = NNZ(M);
	int nnz_N = NNZ(N);
	printf("\n%d\n", nnz_M);
	printMatrix(stdout, N);
	printf("\n%d\n",nnz_N);
	
	Matrix sumM = sum(M, M);
	printMatrix(stdout, sumM);
	
	Matrix sumN = sum(M, N);
	printMatrix(stdout, sumN);

	Matrix diffM = diff(N, M);
	printMatrix(stdout, diffM);
}
