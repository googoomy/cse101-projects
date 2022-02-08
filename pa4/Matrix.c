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
	M->rows = calloc(n+1, sizeof(List));
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
	//if different sizes, not equal
	if(size(A) != size(B)){
		return 0;
	}
	//if they have different amount of nonzeros
	if(NNZ(A) != NNZ(B)){
		return 0;
	}
	//if both matrices are empty
	if(size(A) == 0 && size(B) == 0){
		return 1;
	}
	//if both matrices are null
	if(A == NULL && B == NULL){
		return 1;
	}
	//loop through both matrices and see if all entries are the same
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
	
	Entry E = NULL;
	if(x != 0.0){
		E = newEntry(j, x);
	}
	
	List L = M->rows[i];
	//if the List is empty eppend the entry	
	if(length(L) == 0){
		if(x != 0.0){
			append(L, E);
			M->nnz++;
			return;
		}
	}

	
	Entry curr_entry = NULL;
	moveFront(L);
	for(int k = 1; k <= length(L); k++){
		if(length(L) != 0){
			curr_entry = get(L);
		}else{
			curr_entry = NULL;
		}
		if(curr_entry->col == j){
			//remove the entry if the replacement is zero
			if(x == 0){
				delete(L);
				freeList(&L);
				M->nnz--;
				return;
			}
			else{
			//if a value is already there, replace it
				curr_entry->value = x;
				return;
			}
		//if there were zeros insert before
		}else if(curr_entry->col > j){
			if(x != 0){
				insertBefore(L, E);
				M->nnz++;
			}
			return;
		//ifthe traverssal reaches the end of the list insert the new entry at the end
		}else if(k == length(L)){
			if(x != 0){
				insertAfter(L, E);
				M->nnz++;
			}
			return;
		}
		moveNext(L);
	}

}

// Matrix Arithmetic operations 
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if(A == NULL){
		return NULL;
	}
	//traverse matrix A and add each entry to copy
	Matrix CPY = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1){
			Entry curr_entry = get(A->rows[i]);
			changeEntry(CPY, i, curr_entry->col, curr_entry->value);
			moveNext(A->rows[i]);
		}	
	}
	return(CPY);
	
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if(A == NULL){
		return NULL;
	}
	//traverse matrix A and add each entry to transpose but with flipped indices
	Matrix TP = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1){
			Entry curr_entry = get(A->rows[i]);
			changeEntry(TP, curr_entry->col, i, curr_entry->value);
			moveNext(A->rows[i]);
		}	
	}
	return(TP);
	
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		return NULL;
	}
	Matrix SM = newMatrix(size(A));
	//if x is 0.0 then it is a zero matrix
	if(x == 0.0){
		makeZero(SM);
		return SM;
	}
	//traverse matrix A and multiply each entry by the scalar
	for(int i = 1; i <= size(A); i++){
		moveFront(A->rows[i]);
		while(index(A->rows[i]) != -1){
			Entry curr_entry = get(A->rows[i]);
			changeEntry(SM, i, curr_entry->col, (x*(curr_entry->value)));
			moveNext(A->rows[i]);
		}	
	}
	return(SM);
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		fprintf(stderr, "Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		fprintf(stderr, "Matrix Error: calling sum() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	//if the two matrices are the same then the sum is double
	if(equals(A,B) == 1){
		return scalarMult(2.0, A);		
	}
	Matrix SumM = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		List LA = A->rows[i];
		List LB = B->rows[i];
		moveFront(LA);
		moveFront(LB);
		Entry curr_A;
		Entry curr_B;
		while(index(LA) != -1 || index(LB) != -1){
			if(index(LA) != -1 && index(LB) != -1){
				curr_A = get(LA);
				curr_B = get(LB);
				if(curr_A->col == curr_B->col){
					//if cols are alligned
					changeEntry(SumM, i, curr_A->col, curr_A->value + curr_B->value);
					moveNext(LA);
					moveNext(LB);
				}else if(curr_A->col > curr_B->col){
					//if A is 0.0
					changeEntry(SumM, i, curr_B->col, curr_B->value);
					moveNext(LB);	
				}else{
					//if B is 0.0
					changeEntry(SumM, i, curr_A->col, curr_A->value);
					moveNext(LA);
				}
			//if A reached the end first
			}else if(index(LB) == -1 && index(LA) != -1){
					changeEntry(SumM, i, curr_A->col, curr_A->value);
					moveNext(LA);
			//if B reached the end first
			}else{
					changeEntry(SumM,i, curr_B->col, curr_B->value);
					moveNext(LB);	
			}
		}
	}
	return(SumM);	

}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		fprintf(stderr, "Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		fprintf(stderr, "Matrix Error: calling diff() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix DiffM = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		List LA = A->rows[i];
		List LB = B->rows[i];
		moveFront(LA);
		moveFront(LB);
		Entry curr_A;
		Entry curr_B;
		while(index(LA) != -1 || index(LB) != -1){
			if(index(LA) != -1 && index(LB) != -1){
				curr_A = get(LA);
				curr_B = get(LB);

				if(curr_A->col == curr_B->col){
					//if cols are alligned
					changeEntry(DiffM, i, curr_A->col, curr_A->value - curr_B->value);
					moveNext(LA);
					moveNext(LB);
				}else if(curr_A->col > curr_B->col){
					//when A is 0
					changeEntry(DiffM, i, curr_B->col, 0.0-curr_B->value);
					moveNext(LB);	
				}else{
					//when B is 0
					changeEntry(DiffM, i, curr_A->col, curr_A->value);
					moveNext(LA);
				}
			//if A reached the end first
			}else if(index(LB) == -1 && index(LA) != -1){
				changeEntry(DiffM, i, curr_A->col, curr_A->value);
				moveNext(LA);
			//if B reached the end first
			}else{
				changeEntry(DiffM,i, curr_B->col, 0.0-curr_B->value);
				moveNext(LB);	
			}
			
		}
	}
	return(DiffM);	
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		fprintf(stderr, "Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		fprintf(stderr, "Matrix Error: calling product() with matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	
	//prep the matrices one for the product one for transpose of B
	Matrix PD = newMatrix(size(A));
	Matrix TP = transpose(B);
	double dot_sum = 0;
	List LA;
	List LB;
	Entry curr_A;
	Entry curr_B;
	//loop trhough each row and multiply the row by the transpose's row
	for(int i = 1; i <= size(A); i++){
		LA = A->rows[i];
		moveFront(LA);
		for(int j = 1; j <= size(A); j++){
			LB = TP->rows[j];
			moveFront(LB);
			//dot product
			while(index(LA) != -1 && index(LB) != -1){
				curr_A = get(LA);
				curr_B = get(LB);
			
				if(curr_A->col == curr_B->col){
					dot_sum += (curr_A->value * curr_B->value);
					moveNext(LA);
					moveNext(LB);
				}else if(curr_A->col > curr_B->col){
					moveNext(LB);
				}else{
					moveNext(LA);
				}

			}
			//add the dot product
			if(dot_sum != 0){
				changeEntry(PD, i, j, dot_sum);
			}
			//reset the sum
			dot_sum = 0;
			moveFront(LA);
		}
	}
	freeMatrix(&TP);
	return(PD);

}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero row is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs "(col, val)" giving the column numbers and non-zero values 
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if(M == NULL){
		fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	
	List L;
	for(int i = 1; i <= size(M); i++){
		L = M->rows[i];
		moveFront(L);
		//Entry curr_entry = get(L);
		for(int j = 1; j <= length(L); j++){
			Entry curr_entry = get(L);
			if (j == 1){
				fprintf(out, "%d: ", i);
			}
			fprintf(out, "(%d, %.1f)", curr_entry->col, curr_entry->value);
			if(j == length(L)){
				fprintf(out, "\n");
			}else{
				fprintf(out, " ");
			}
			moveNext(L);
		}
	}
	fprintf(out, "\n");
	
}


