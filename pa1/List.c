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
	int index;
} ListObj;

typedef ListObj* List;

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
	L->index = 0;
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
	return (L->index);
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
	return (L->front);
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
	return (L->back);
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
	return (L->cursor);
}

bool equals(List A, List B){ // Returns true iff Lists A and B are in same
 // state, and returns false otherwise.
	if(length(A) == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(B) == NULL){
		fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(A) != length(B) || front(A) != front(B) || back(A) != front(B)){
		return false;
	}
	for(int i = 0; i < length(A); i++){
		if(get(A)
	}
}

 // Manipulation procedures ----------------------------------------------------
void clear(List L){ // Resets L to its original empty state.
	
}

void set(List L, int x){ // Overwrites the cursor element’s data with x. 
 // Pre: length()>0, index()>=0
	if(L == NULL){
		fpritnf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		fprintf(stderr, "List Error: calling set() on an empty List\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(x);
	L->cursor = N;
}

void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
	if(L == NULL){
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		
	}
}

void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.

}		

void movePrev(List L){ // If cursor is defined and not at front, move cursor one 
 // step toward the front of L; if cursor is defined and at 
 // front, cursor becomes undefined; if cursor is undefined 
 // do nothing
 
}
	
void moveNext(List L); // If cursor is defined and not at back, move cursor one 
 // step toward the back of L; if cursor is defined and at 
 // back, cursor becomes undefined; if cursor is undefined 
 // do nothing
3
void prepend(List L, int x); // Insert new element into L. If L is non-empty, 
 // insertion takes place before front element.
void append(List L, int x); // Insert new element into L. If L is non-empty, 
 // insertion takes place after back element.
void insertBefore(List L, int x); // Insert new element before cursor. 
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x); // Insert new element after cursor. 
 // Pre: length()>0, index()>=0
void deleteFront(List L); // Delete the front element. Pre: length()>0
void deleteBack(List L); // Delete the back element. Pre: length()>0
void delete(List L); // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints to the file pointed to by out, a 
 // string representation of L consisting 
 // of a space separated sequence of integers,
// with front on left.
List copyList(List L); // Returns a new List representing the same integer 
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state 
// of L is unchanged.
