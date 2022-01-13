#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//structs
typedef struct NodeObj{
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int n;
	int idx;
} ListObj;

// Constructors-Destructors ---------------------------------------------------
Node newNode(int node_data){
	Node N = malloc(sizeof(NodeObj));
	N->data = node_data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->cursor = NULL;
	L->n = 0;
	L->idx = -1;
	L->back = NULL;
	return(L);
}	// Creates and returns a new empty List.

void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
	// *pL to NULL.
	if(pL != NULL && * pL != NULL){
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------
int length(List L){ // Returns the number of elements in L.
	if(L == NULL){
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->n);
}

int index(List L){ // Returns index of cursor element if defined, -1 otherwise.
	if(L == NULL){
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		return -1;
	}
	return (L->idx);
}

int front(List L){ // Returns front element of L. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		fprintf(stderr, "List Error: calling front() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}

int back(List L){ // Returns back element of L. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);	
	}
	if(length(L) <= 0){
		fprintf(stderr, "List Error: calling back() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

int get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling get() on an empty List\n");
		exit(EXIT_FAILURE); 
	}
	return (L->cursor->data);
}

bool equals(List A, List B){ // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
	if(A == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(B == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(A) != length(B) || front(A) != front(B) || back(A) != back(B)){
		return false;
	}
	Node NodA = A->front;
	Node NodB = B->front;
	bool isEqual = true;
	for(int i = 0; i < length(A); i++){
		if(NodA->data != NodB->data){
			isEqual = false;
			break;
		}
		NodA = NodA->next;
		NodB = NodB->next;
	}
	return isEqual;
}

 // Manipulation procedures ----------------------------------------------------
void clear(List L){ // Resets L to its original empty state.
	
	while(length(L) > 0){
		deleteFront(L);
	}
	
	/*
	Node Nod = L->front;
	while(true){
		
	}
	*/
	L->idx = -1;
}

void set(List L, int x){ // Overwrites the cursor element’s data with x. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling set() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = newNode(x);
	if(L->idx == 0){
		Nod->next = L->front->next;
		L->front->next->prev = Nod;
		freeNode(&L->front);
		L->front = Nod;
		L->cursor = Nod;
	}else if(L->idx == (L->n)-1){
		Nod->prev = L->back->prev;
		L->back->prev->next = Nod;
		freeNode(&L->back);
		L->back = Nod;
		L->cursor = Nod;
	}else if(length(L) == 1){
		L->idx = 0;
		freeNode(&L->front);
		L->front = L->back = Nod;
		L->cursor = Nod;
	}else{
		L->cursor->next->prev = Nod;
		L->cursor->prev->next = Nod;
		Nod->next = L->cursor->next;
		Nod->prev = L->cursor->prev;
		freeNode(&L->cursor);
		L->cursor = Nod;
	}
}

void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		L->cursor = L->front;
		L->idx = 0;
	}
}

void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 0){
		L->cursor = L->back;
		L->idx = (L->n)-1;
	}
}		

void movePrev(List L){ // If cursor is defined and not at front, move cursor one 
 // step toward the front of L; if cursor is defined and at 
 // front, cursor becomes undefined; if cursor is undefined 
 // do nothing
 	if(L == NULL){
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
		if(L->idx != 0){
			L->idx--;
			L->cursor = L->cursor->prev;
		}	
		else{
			L->cursor = NULL;
			L->idx = -1;
		}
	}
}
	
void moveNext(List L){ // If cursor is defined and not at back, move cursor one 
 // step toward the back of L; if cursor is defined and at 
 // back, cursor becomes undefined; if cursor is undefined 
 // do nothing
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor != NULL){
	       	if(L->idx != (L->n)-1){
			L->idx++;
			L->cursor = L->cursor->next;
		}
		else{
			L->cursor = NULL;
			L->idx = -1;
		}
	}
}

void prepend(List L, int x){ // Insert new element into L. If L is non-empty, 
 // insertion takes place before front element.
	if(L == NULL){
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = newNode(x);
	if(length(L) == 0){
		L->front = L->back = Nod;
	}else{
		Nod->next = L->front;
		L->front->prev = Nod;
		L->front = Nod;
		if(L->idx != -1){
			L->idx++;
		}
	}
	L->n++;
}

void append(List L, int x){ // Insert new element into L. If L is non-empty, 
 // insertion takes place after back element.
	if(L == NULL){
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = newNode(x);
	if(length(L) == 0){
		L->front = L->back = Nod;
	}else{
		//Nod->prev = L->back;
		L->back->next = Nod;
		Nod->prev = L->back;
		L->back = Nod;
	}
	L->n++;
}

void insertBefore(List L, int x){ // Insert new element before cursor. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || L->idx < 0){
		fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->idx == 0){
		prepend(L, x);
	}else{
		Node Nod = newNode(x);
		L->idx++;
		L->n++;
		Nod->next= L->cursor;
		Nod->prev = L->cursor->prev;
		L->cursor->prev->next = Nod;
		L->cursor->prev = Nod;
	}
}

void insertAfter(List L, int x){ // Insert new element after cursor. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || L->idx < 0){
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(L->idx >= L->n - 1){
		append(L, x);
	}else{
		Node Nod = newNode(x);
		L->n++;
		Nod->next = L->cursor->next;
		Nod->prev = L->cursor;
		L->cursor->next->prev = Nod;
		L->cursor->next = Nod;
	}
}
void deleteFront(List L){ // Delete the front element. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 0){
		fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(L->idx != -1){
		L->idx--;
		if(L->idx <= -1){
			L->cursor = NULL;
		}
	}
	if(length(L) == 1){
		freeNode(&L->front);
	}else{
		Node Nod = L->front;
		L->front->next->prev = NULL;
		L->front = L->front->next;
		freeNode(&Nod);
	}
	L->n--;
	
}

void deleteBack(List L){ // Delete the back element. Pre: length()>0
	if(L == NULL){
		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 0){
		fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) == 1){
		//freeNode(&L->front);
		freeNode(&L->back);
	}else{
		Node Nod = L->back;
		L->back = L->back->prev;
		freeNode(&Nod);
		L->n--;
	}
}	
	
void delete(List L){ // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling delete() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = L->cursor;
	L->cursor->prev->next = L->cursor->next;
	L->cursor->next->prev = L->cursor->prev;
	freeNode(&Nod);
	L->n--;
	L->idx = -1;
}	
	
// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){ // Prints to the file pointed to by out, a 
 // string representation of L consisting 
 // of a space separated sequence of integers,
// with front on left.
	if(L == NULL){
		fprintf(stderr, "List Error calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = NULL;
	for(Nod = L->front; Nod != NULL; Nod = Nod->next){
		fprintf(out, "%d ", Nod->data);
	}
}

List copyList(List L){ // Returns a new List representing the same integer 
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
	if(L == NULL){
		fprintf(stderr, "List Error calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node Nod = NULL;
	List R = newList();
	for(Nod = L->front; Nod != NULL; Nod = Nod->next){
		append(R, Nod->data);
	}
	return R;
}
