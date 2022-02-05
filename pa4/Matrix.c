#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj{
	int col;
	double value;
}EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{
	List *rows;
	int size;
	int nnz;
}MatrixObj;

Entry newEntry(int col_num, double val){
	Entry E = malloc(sizeof(EntryObj));
	E->col = col_num;
	E->value = val;
	return(E);
}


void freeEntry(Entry *pE){
	if(pE != NULL && *pE != NULL){
		free(*pE);
		*pE = NULL;
	}
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->rows = malloc(sizeof(List) * n);
	for(int i = 1; i <= n; i++){
		M->rows[i] = newList();
	}
	M->size = n;
	M->nnz = 0;
	return(M);	
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		/*
		makeZero(*pM);
		for(int i = 0; i < size(*pM); i++){
			freeList(&((*pM)->rows[i]));
		}
		free((*pM)->rows);
		*/
		free(*pM);
		*pM = NULL;
	}
	
}

// Access functions 
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if(M == NULL){
		fprintf(stderr, "Matrix Error: calling size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if(M == NULL){
		fprintf(stderr, "Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(size(A) != size(B)){
		return 0;
	}
	if(NNZ(A) != NNZ(B)){
		return 0;
	}
	if(size(A) == 0 && size(B) == 0){
		return 1;
	}
	if(A == NULL && B == NULL){
		return 1;
	}
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		moveFront(B->rows[i]);
		if(length(A->rows[i]) != length(B->rows[i])){
			return 0;
		}
		while(index(A->rows[i]) != -1 && index(B->rows[i]) != -1){
			Entry EA = get(A->rows[i]);
			Entry EB = get(B->rows[i]);
			if(EA->value != EB->value && EA->col == EB->col){
				return 0;
			}
			if(EA->col != EB->col){
				return 0;
			}
			moveNext(A->rows[i]);
			moveNext(B->rows[i]);
		}
	}
	return 1;
}

// Manipulation procedures 
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	for(int i = 1; i <= size(M); i++){
		clear(M->rows[i]);
	}
	M->size = 0;
	M->nnz = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if(M == NULL){
		fprintf(stderr, "Matrix Error: calling changeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(i < 1 || i > size(M)){
		fprintf(stderr, "Matrix Error: calling changeEntry() with invalid row. Row must be 1<=i<=size(M)\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1 || j > size(M)){
		fprintf(stderr, "Matrix Error: calling changeEntry() with invalid column. Comlumn must be 1<=j<=size(M)\n");
		exit(EXIT_FAILURE);
	}
	Entry E = newEntry(j, x);
	List L = M->rows[i];
	
	if(length(L) == 0){
		if(x != 0.0){
			append(L, E);
			M->nnz++;
			return;
		}
	}

	moveFront(L);
	while(index(L) != -1){
		Entry curr_entry = get(M->rows[i]);
		if(curr_entry->col == j && x == 0.0){
			freeEntry(&E);
			delete(L);
			M->nnx--;
			return;
		}	
		if(curr_entry->col == j && x != 0.0){
			insertBefore(L, E);
			M->nnz++;
			return;
		}
		if(curr_entry->col < j){
			insertBefore(L, E);
			M->nnz++;
			return;	
		}	

		moveNext(L);
	}
	
}

// Matrix Arithmetic operations 
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero row is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs "(col, val)" giving the column numbers and non-zero values 
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);
